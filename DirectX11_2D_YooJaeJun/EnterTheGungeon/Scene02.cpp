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
        //SOUND->AddSound("15051562_MotionElements_8-bit-arcade-swordsman.wav", "SCENE02", true);
        SOUND->Play("SCENE02");

        // 맵 오브젝트
        mapObj = new MapObject;

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
        float doorOpenScaleCoef = 2.5f;

        int idx = 0;
        for (auto& elem : mapObj->doorOpenUp)
        {
            elem = new Obstacle;
            elem->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
            elem->col->scale.x = 88.0f / 4.0f * doorOpenScaleCoef;
            elem->col->scale.y = 50.0f * doorOpenScaleCoef;
            elem->SetPosX(200.0f + idx * elem->col->scale.x);
            elem->SetPosY(0.0f);
            elem->col->collider = Collider::rect;
            elem->col->zOrder = ZOrder::object;

            elem->idle = new ObImage(L"EnterTheGungeon/Level/Door_Open_Up.png");
            elem->idle->maxFrame.x = 4;
            elem->idle->scale.x = 88.0f / 4.0f * doorOpenScaleCoef;
            elem->idle->scale.y = 50.0f * doorOpenScaleCoef;
            elem->idle->SetParentRT(*elem->col);
            elem->idle->ChangeAnim(ANIMSTATE::STOP, 0.1f);
            elem->idle->zOrder = ZOrder::object;

            if (idx & 1)
            {
                elem->idle->reverseLR = true;
            }

            elem->col->Update();

            idx++;
        }

        idx = 0;
        for (auto& elem : mapObj->doorOpenDown)
        {
            elem = new Obstacle;
            elem->col->isVisible = false;   //
            elem->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
            elem->col->scale.x = 88.0f / 4.0f * doorOpenScaleCoef;
            elem->col->scale.y = 50.0f * doorOpenScaleCoef;
            elem->SetPosX(200.0f + idx * elem->col->scale.x);
            elem->SetPosY(0.0f);
            elem->col->collider = Collider::rect;
            elem->col->zOrder = ZOrder::object;

            elem->idle = new ObImage(L"EnterTheGungeon/Level/Door_Open_Down.png");
            elem->idle->maxFrame.x = 4;
            elem->idle->scale.x = 88.0f / 4.0f * doorOpenScaleCoef;
            elem->idle->scale.y = 50.0f * doorOpenScaleCoef;
            elem->idle->SetParentRT(*elem->col);
            elem->idle->ChangeAnim(ANIMSTATE::STOP, 0.1f);
            elem->idle->zOrder = ZOrder::object;

            if (idx & 1)
            {
                elem->idle->reverseLR = true;
            }

            elem->col->Update();

            idx++;
        }

        float doorClosedScaleCoef = 2.5f;

        idx = 0;
        for (auto& elem : mapObj->doorClosed)
        {
            elem = new Obstacle;
            elem->col->isVisible = true;
            elem->col->isFilled = false;
            elem->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
            elem->col->scale.x = 68.0f / 2.0f * doorClosedScaleCoef;
            elem->col->scale.y = 41.0f * doorClosedScaleCoef;
            elem->SetPosX(200.0f + idx * elem->col->scale.x);
            elem->SetPosY(200.0f);
            elem->col->collider = Collider::rect;
            elem->col->zOrder = ZOrder::object;

            elem->idle = new ObImage(L"EnterTheGungeon/Level/Door_Closed.png");
            elem->idle->maxFrame.x = 2;
            elem->idle->scale.x = 68.0f / 2.0f * doorClosedScaleCoef;
            elem->idle->scale.y = 41.0f * doorClosedScaleCoef;
            elem->idle->SetParentRT(*elem->col);
            elem->idle->ChangeAnim(ANIMSTATE::LOOP, 2.0f);
            elem->idle->zOrder = ZOrder::object;

            if (idx & 1)
            {
                elem->idle->reverseLR = true;
            }

            elem->col->Update();

            idx++;
        }
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
            boss->weapon[boss->curWeaponIdx]->col->rotation = Utility::DirToRadian(player->Pos());

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
                boss->Hit(bulletElem->damage);
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

        Weapon* bossWeapon = boss->weapon[boss->curWeaponIdx];
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
}