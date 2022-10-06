#include "stdafx.h"

namespace Gungeon
{
    Scene02::Scene02()
    {
        Init();
    }

    Scene02::~Scene02()
    {
        mapObj->Release();
        player->Release();
        for (auto& elem : enemy) elem->Release();
        boss->Release();
    }

    void Scene02::Init()
    {
        if (mapGen) mapGen->useGui = false;

        LIGHT->light.radius = 2000.0f;

        SOUND->Stop("SCENE01");
        // SOUND->AddSound("15051562_MotionElements_8-bit-arcade-swordsman.wav", "SCENE02", true);
        SOUND->Play("SCENE02");

        // 플레이어
        player = new Player;

        InitEnemy();
        InitBoss();
        InitMapObject();

        Spawn();
    }

    void Scene02::InitEnemy()
    {
        for (auto& elem : enemy)
        {
            elem = new Enemy;
        }
    }

    void Scene02::InitBoss()
    {
        boss = new Boss;
    }

    void Scene02::InitMapObject()
    {
        mapObj = new MapObject;
        mapObj->Init();
    }

    void Scene02::Spawn()
    {
        if (!mapGen) return;
        if (mapGen->roomsSelected.empty() == false)
        {
            room0Pos = mapGen->roomsSelected[0]->col->GetWorldPos();
        }

        CAM->position = room0Pos;
        CAM->coefScale = Vector3(1.0f, 1.0f, 1.0f);

        player->SetPosX(room0Pos.x - 10.0f);
        player->SetPosY(room0Pos.y + 0.0f);

        for (auto& elem : enemy)
        {
            elem->SetPosX(room0Pos.x + RANDOM->Float(-200.0f, 200.0f));
            elem->SetPosY(room0Pos.y + RANDOM->Float(-200.0f, 200.0f));
        }

        boss->SetPosX(room0Pos.x + 0.0f);
        boss->SetPosY(room0Pos.y + 200.0f);
    }

    void Scene02::Release()
    {
        mapObj->Release();
        for (auto& elem : enemy) elem->Release();
        player->Release();
        boss->Release();
    }

    void Scene02::Update()
    {
        if (INPUT->KeyDown('R'))
        {
            Release();
            Init();
        }

        if (INPUT->KeyDown('H'))
        {
            ColOnOff();
        }

        if (mapGen)
        {
            mapGen->Update();
        }

        mapObj->Update();

        player->Update();

        for (auto& elem : enemy)
        {
            if (elem->state != State::die)
            {
                elem->targetPos = player->Pos();
                elem->FindPath(mapGen->tilemap);
            }
            elem->Update();
        }

        if (boss->state != State::die)
        {
            boss->targetPos = player->Pos();
            boss->w->col->rotation = Utility::DirToRadian(player->Pos());

            if (boss->pattern == BossPattern::shield)
            {
                boss->FindPath(mapGen->tilemap);
            }
        }
        boss->Update();

        if (INPUT->KeyDown('1'))
        {
            SCENE->ChangeScene("Scene01");
        }
    }

    void Scene02::LateUpdate()
    {
        if (mapGen)
        {
            mapGen->LateUpdate();
        }

        int idx = 0;

        // 플레이어
        if (mapGen->IntersectTileUnit(player))
        {
            player->StepBack();
        }

        // 플레이어 총알
        for (auto& bulletElem : player->bullet)
        {
            for (auto& enemyElem : enemy)
            {
                if (enemyElem->state != State::die &&
                    bulletElem->col->Intersect(enemyElem->col))
                {
                    Vector2 dir = enemyElem->col->GetWorldPos() - bulletElem->col->GetWorldPos();
                    dir.Normalize();
                    enemyElem->Hit(bulletElem->damage, dir);
                    bulletElem->Hit(1);
                }
            }

            if (boss->state != State::die &&
                bulletElem->col->Intersect(boss->col))
            {
                Vector2 dir = boss->col->GetWorldPos() - bulletElem->col->GetWorldPos();
                dir.Normalize();
                boss->Hit(bulletElem->damage, dir);
                bulletElem->Hit(1);
            }

            if (mapGen->IntersectTilePos(bulletElem->Pos()))
            {
                bulletElem->Hit(1);
            }
        }


        // 적
        for (auto& enemyElem : enemy)
        {
            if (false == player->godMode &&
                enemyElem->state != State::die &&
                enemyElem->col->Intersect(player->col))
            {
                player->Hit(1);
            }

            if (mapGen->IntersectTileUnit(enemyElem))
            {
                enemyElem->StepBack();
            }

            // 적 총알
            for (auto& bulletElem : enemyElem->bullet)
            {
                if (false == player->godMode &&
                    enemyElem->state != State::die &&
                    bulletElem->col->Intersect(player->col))
                {
                    player->Hit(bulletElem->damage);
                    bulletElem->Hit(1);
                }

                if (mapGen->IntersectTilePos(bulletElem->Pos()))
                {
                    bulletElem->Hit(1);
                }
            }

            if (enemyElem->dropItem->state == State::idle &&
                enemyElem->dropItem->col->Intersect(player->col))
            {
                enemyElem->dropItem->Hit();
                player->PlusMoney(1);
            }

            enemyElem->LateUpdate();
        }


        // 보스
        if (false == player->godMode &&
            boss->state != State::die &&
            boss->col->Intersect(player->col))
        {
            player->Hit(1);
        }

        if (mapGen->IntersectTileUnit(boss))
        {
            boss->StepBack();
        }

        // 보스 총알
        for (auto& bulletElem : boss->bullet)
        {
            if (false == player->godMode &&
                boss->state != State::die &&
                bulletElem->col->Intersect(player->col))
            {
                player->Hit(bulletElem->damage);
                bulletElem->Hit(1);
            }

            if (mapGen->IntersectTilePos(bulletElem->Pos()))
            {
                bulletElem->Hit(1);
            }
        }

        if (boss->dropItem->state == State::idle &&
            boss->dropItem->col->Intersect(player->col))
        {
            boss->dropItem->Hit();
            player->PlusMoney(1);
        }

        Weapon* bossWeapon = boss->w;
        if (bossWeapon->state == State::idle &&
            bossWeapon->col->Intersect(player->col))
        {
            bossWeapon->Hit();
            player->EquipWeapon(bossWeapon);
        }

        boss->LateUpdate();


        // 맵 오브젝트
        idx = 0;
        for (auto& elem : mapObj->doorOpenUp)
        {
            if (false == elem->isOpen)
            {
                if (elem->col->Intersect(player->col))
                {
                    Vector2 dir = elem->Pos() - player->Pos();
                    if (dir.y < 0.0f)
                    {
                        elem->idle->isVisible = false;
                        mapObj->doorOpenDown[idx]->idle->isVisible = true;
                        mapObj->doorOpenDown[idx]->idle->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
                    }
                    else
                    {
                        elem->idle->isVisible = true;
                        elem->idle->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
                    }

                    elem->col->isVisible = false;
                    elem->isOpen = true;
                    mapObj->doorOpenDown[idx]->col->isVisible = false;
                    mapObj->doorOpenDown[idx]->isOpen = true;
                }
            }
            idx++;
        }

        player->LateUpdate();
    }

    void Scene02::Render()
    {
        if (mapGen)
        {
            mapGen->Render();
        }

        player->shadow->Render();
        for (auto& elem : enemy) elem->shadow->Render();
        boss->shadow->Render();

        mapObj->Render();
        for (auto& elem : enemy) elem->Render();
        player->Render();
        boss->Render();

        // 최적화 이슈로 zorder 주석
        /*
        int size = RENDER->pq.size();
        while (false == RENDER->pq.empty())
        {
            RENDER->pq.top()->Render();
            RENDER->pq.pop();
        }
        */
    }

    void Scene02::ResizeScreen()
    {
        mapGen->ResizeScreen();

        player->ResizeScreen();

        boss->ResizeScreen();
    }

    void Scene02::ColOnOff()
    {
        player->col->isVisible = !player->col->isVisible;
        player->colTile->isVisible = !player->colTile->isVisible;
        player->w->firePos->isVisible = !player->w->firePos->isVisible;

        for (auto& bulletElem : player->bullet)
        {
            bulletElem->col->isVisible = !bulletElem->col->isVisible;
        }
        
        for (auto& elem : enemy)
        {
            elem->col->isVisible = !elem->col->isVisible;
            elem->colTile->isVisible = !elem->colTile->isVisible;
            elem->w->firePos->isVisible = !elem->w->firePos->isVisible;

            for (auto& bulletElem : elem->bullet)
            {
                bulletElem->col->isVisible = !bulletElem->col->isVisible;
            }
        }

        boss->col->isVisible = !boss->col->isVisible;
        boss->colTile->isVisible = !boss->colTile->isVisible;
        boss->w->firePos->isVisible = !boss->w->firePos->isVisible;

        for (auto& bulletElem : boss->bullet)
        {
            bulletElem->col->isVisible = !bulletElem->col->isVisible;
        }

        for (auto& elem : mapObj->doorClosed)
        {
            elem->col->isVisible = !elem->col->isVisible;
        }
        for (auto& elem : mapObj->doorOpenDown)
        {
            elem->col->isVisible = !elem->col->isVisible;
        }
        for (auto& elem : mapObj->doorOpenUp)
        {
            elem->col->isVisible = !elem->col->isVisible;
        }
    }
}