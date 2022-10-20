#include "stdafx.h"

namespace Gungeon
{
    Scene03::Scene03()
    {
    }

    Scene03::~Scene03()
    {
    }

    void Scene03::Init()
    {
        // tilemap
        MAP->tilemap = new ObTileMap;
        MAP->tilemap->scale = Vector2(100.0f, 100.0f);
        MAP->tilemap->SetWorldPos(Vector2(-app.GetHalfWidth() - 1000.0f, -app.GetHalfHeight() - 1000.0f));
        MAP->imgIdx = 1;
        MAP->tileSize = Int2(30, 30);
        MAP->tilemap->ResizeTile(MAP->tileSize);
        MAP->tileColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
        MAP->tileState = 0;
        MAP->tilemap->CreateTileCost();

        InitRoom();

        CAM->position = curRoom->Pos();
        CAM->zoomFactor = Vector3(1.0f, 1.0f, 1.0f);

        if (!player)
        {
            player = new Player();
        }
        else
        {
            player->Spawn(Vector2(0.0f, 0.0f));
        }

        if (!boss)
        {
            boss = new Boss();
            boss->Spawn(Vector2(0.0f, 300.0f));
        }


        SOUND->Stop("SCENE01");
        SOUND->Stop("SCENE02");
        //SOUND->AddSound("Vaquero Perdido - The Mini Vandals.mp3", "Scene03", true);
        SOUND->Play("Scene03");
    }

    void Scene03::InitRoom()
    {
        MAP->imgIdx = 1;

        curRoom = new Room;
        curRoom->col->scale = Vector2(1500.0f, 1500.0f);
        curRoom->SetPos(Vector2(0.0f, 0.0f));
        curRoom->col->isVisible = false;

        float tileScale = MAP->tilemap->scale.x;

        Vector2 start;
        Vector2 end;
        Int2 sour;
        Int2 dest;

        auto SetTile2 = [&](Int2 on, int roomIdx)
        {
            MAP->tilemap->SetTile(on,
                Int2(RANDOM->Int(floorImgMin.x, floorImgMax.x),
                    RANDOM->Int(floorImgMin.y, floorImgMax.y)),
                MAP->imgIdx,
                (int)TileState::floor,
                Color(0.5f, 0.5f, 0.5f, 1.0f),
                roomIdx);
        };

        auto SetWall2 = [&](Int2 on, int roomIdx, Int2 frameIdx)
        {
            MAP->tilemap->SetTile(on,
                frameIdx,
                MAP->imgIdx,
                (int)TileState::wall,
                Color(0.5f, 0.5f, 0.5f, 1.0f),
                roomIdx);
        };

        auto SetTile1 = [&](Room* elem, int roomIdx)
        {
            ObRect* r = dynamic_cast<ObRect*>(elem->col);

            start.x = r->lb().x;
            start.y = r->lb().y;
            end.x = r->rt().x;
            end.y = r->rt().y;

            MAP->tilemap->WorldPosToTileIdx(start, sour);
            MAP->tilemap->WorldPosToTileIdx(end, dest);


            for (int y = sour.y + 1; y <= dest.y - 1; y++)
            {
                for (int x = sour.x + 1; x <= dest.x - 1; x++)
                {
                    SetTile2(Int2(x, y), roomIdx);
                }
            }

            // wall - top, bottom, left, right, edge

            for (int x = sour.x; x <= dest.x; x++)
            {
                SetWall2(Int2(x, dest.y), roomIdx, wallImgDir[DirState::dirT]);
                SetWall2(Int2(x, sour.y), roomIdx, wallImgDir[DirState::dirB]);
            }

            for (int y = sour.y; y <= dest.y; y++)
            {
                SetWall2(Int2(sour.x, y), roomIdx, wallImgDir[DirState::dirL]);
                SetWall2(Int2(dest.x, y), roomIdx, wallImgDir[DirState::dirR]);
            }

            SetWall2(Int2(sour.x, sour.y), roomIdx, wallImgDir[DirState::dirLB]);
            SetWall2(Int2(sour.x, dest.y), roomIdx, wallImgDir[DirState::dirLT]);
            SetWall2(Int2(dest.x, sour.y), roomIdx, wallImgDir[DirState::dirRB]);
            SetWall2(Int2(dest.x, dest.y), roomIdx, wallImgDir[DirState::dirRT]);
        };

        SetTile1(curRoom, 99);
    }

    void Scene03::Release()
    {
        SafeRelease(boss);
    }

    void Scene03::Update()
    {
        if (INPUT->KeyDown('1'))
        {
            Release();
            SCENE->ChangeScene("Scene01", 1.0f);
        }
        else if (INPUT->KeyDown('2'))
        {
            Release();
            isChangingScene = true;
            SCENE->ChangeScene("Scene02", 1.0f);
        }
        else if (INPUT->KeyDown('3'))
        {
            isChangingScene = true;
            SCENE->ChangeScene("Scene03", 1.0f);
        }

        ChangeUpdateScene();

        if (INPUT->KeyDown('H'))
        {
            ColToggle();
        }

        if (!boss) return;
        
        bool flagCleared = true;

        if (boss->state != State::die)
        {
            flagCleared = false;

            boss->targetPos = player->Pos();
            boss->firePosTargeting->rotation2 = Utility::DirToRadian(player->Pos() - boss->firePosTargeting->GetWorldPos());

            switch (boss->state)
            {
            case State::walk:
                boss->FindPath(MAP->tilemap);
                break;
            case State::attack:
                switch (boss->pattern)
                {
                case BossPattern::shield:
                case BossPattern::trail:
                    boss->FindPath(MAP->tilemap);
                    break;
                }
            default:
                boss->Stop();
                break;
            }

            switch (boss->pattern)
            {
            case BossPattern::miro:
                if (boss->pushingPlayer)
                {
                    Vector2 dest = Vector2(0.0f, -500.0f);
                    boss->col->SetWorldPos(Vector2(0.0f, 500.0f));
                    boss->SpawnPlayerByForce(dest);
                    player->col->SetWorldPos(dest);
                    player->Update();
                }
            }
        }

        // °ñµå Èí¼ö ÇÃ·¡±×
        if (flagCleared)
        {
            curRoom->cleared = true;
            boss->dropItem->flagAbsorbed = true;
        }

        if (boss->dropItem->flagAbsorbed)
        {
            boss->dropItem->targetPos = player->Pos();
        }

        MAP->tilemap->Update();
        player->Update();
        boss->Update();
    }

    void Scene03::LateUpdate()
    {
        if (!boss) return;

        IntersectPlayer();
        IntersectBoss();
    }

    void Scene03::Render()
    {
        MAP->tilemap->Render();
        if (player) player->shadow->Render();
        if (boss) boss->shadow->Render();
        if (boss) boss->Render();
        if (player) player->Render();
    }

    void Scene03::ResizeScreen()
    {
        if (player) player->ResizeScreen();
        if (boss) boss->ResizeScreen();
    }

    void Scene03::IntersectPlayer()
    {
        if (MAP->tilemap->IntersectTileColTile(player->colTile))
        {
            player->StepBack();
        }

        // ÇÃ·¹ÀÌ¾î ÃÑ¾Ë
        for (auto& bulletElem : player->bullet)
        {
            if (bulletElem->isFired)
            {
                if (boss->state != State::die &&
                    bulletElem->col->Intersect(boss->col))
                {
                    Vector2 dir = boss->col->GetWorldPos() - bulletElem->col->GetWorldPos();
                    dir.Normalize();
                    boss->Hit(bulletElem->damage, dir);
                    bulletElem->Hit(1);
                }

                if (MAP->tilemap->IntersectTile(bulletElem->On()))
                {
                    bulletElem->Hit(1);
                }
            }
        }
    }

    void Scene03::IntersectBoss()
    {
        if (player->godMode == false &&
            player->state != State::die &&
            boss->state != State::die &&
            boss->col->Intersect(player->col))
        {
            player->Hit(1);
        }

        if (MAP->tilemap->IntersectTileColTile(boss->colTile))
        {
            boss->StepBack();
        }

        // º¸½º ÃÑ¾Ë
        for (auto& bulletElem : boss->bullet)
        {
            if (bulletElem->isFired)
            {
                if (player->godMode == false &&
                    player->state != State::die &&
                    boss->state != State::die &&
                    bulletElem->col->Intersect(player->col))
                {
                    player->Hit(bulletElem->damage);
                    bulletElem->Hit(1);
                }

                Int2 on = bulletElem->On();
                switch (boss->pattern)
                {
                case BossPattern::trail:
                    if (MAP->tilemap->IntersectTile(on))
                    {
                        // bulletElem->Hit(1);
                        if (on.y <= 6 || on.y >= 21)
                        {
                            bulletElem->moveDir.y *= -1.0f;
                        }
                        else
                        {
                            bulletElem->moveDir.x *= -1.0f;
                        }
                        bulletElem->col->rotation = Utility::DirToRadian(bulletElem->moveDir);
                        bulletElem->StepBack();
                        bulletElem->Update();
                    }
                    break;
                default:
                    if (MAP->tilemap->IntersectTilePos(bulletElem->Pos()))
                    {
                        bulletElem->Hit(1);
                    }
                break;
                }
            }
        }

        if (boss->dropItem->state == State::idle &&
            boss->dropItem->col->Intersect(player->col))
        {
            boss->dropItem->Hit();
            player->PlusMoney(1);
        }

        boss->LateUpdate();
    }


    void Scene03::ChangeUpdateScene()
    {
        if (isChangingScene)
        {
            LIGHT->light.radius -= 2000.0f * DELTA;
            LIGHT->light.lightColor.x += 0.5f * DELTA;
            LIGHT->light.lightColor.y += 0.5f * DELTA;
            LIGHT->light.lightColor.z += 0.5f * DELTA;

            if (TIMER->GetTick(timeFade, 1.0f))
            {
                isChangingScene = false;
            }
        }
        else
        {
            LIGHT->light.radius += 2000.0f * DELTA;
            LIGHT->light.radius = Utility::Saturate(LIGHT->light.radius, 0.0f, 2000.0f);
            LIGHT->light.lightColor.x = 0.5f;
            LIGHT->light.lightColor.y = 0.5f;
            LIGHT->light.lightColor.z = 0.5f;
        }
    }

    // Ä¡Æ®
    void Scene03::ColToggle()
    {
        player->ColToggle();
        boss->ColToggle();
    }
}