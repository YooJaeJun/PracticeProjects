#include "stdafx.h"

namespace Gungeon
{
    Scene02::Scene02()
    {
        Init();
    }

    Scene02::~Scene02()
    {
        Release();
    }

    void Scene02::Init()
    {
        fadeOut = false;
        timeFade = 0.0f;

        if (mapGen) mapGen->useGui = false;
        curRoom = nullptr;
        curRoomIdx = 0;
        afterRoomIdx = -2;

        if (!player) player = new Player();

        spawnEffect.resize(enemyMax + bossMax);
        int idx = 0;
        for (auto& elem : spawnEffect)
        {
            if (!elem)
            {
                elem = new Effect;
                elem->idle = new ObImage(L"EnterTheGungeon/Enemy_0/Spawn.png");
                elem->state = State::die;
                elem->idle->maxFrame.x = 18;
                elem->idle->scale = Vector2(663.0f / 18.0f, 39.0f) * 2.0f;
                elem->idle->isVisible = false;
                elem->intervalDie = 1.8f;

                if (idx == spawnEffect.size() - 1)
                {
                    spawnEffect[spawnEffect.size() - 1]->idle->scale *= 2.5f;
                }
            }
            idx++;
        }

        for (auto& elem : enemy)
        {
            if (!elem)
            {
                elem = new Enemy1();
            }
        }

        if (!boss)
        {
            boss = new Boss();
        }

        if (!mapObj) mapObj = new MapObject();

        SOUND->Stop("SCENE01");
        // SOUND->AddSound("15051562_MotionElements_8-bit-arcade-swordsman.wav", "SCENE02", true);
        SOUND->Play("SCENE02");
    }

    void Scene02::Release()
    {
        for (auto& elem : mapGen->selectedRooms) elem->cleared = false;
        SafeRelease(mapObj);
        for (auto& elem : enemy) SafeRelease(elem);
        SafeRelease(player);
        SafeRelease(boss);
    }

    void Scene02::Update()
    {
        if (INPUT->KeyDown('2'))
        {
            gameState = GameState::start;
            Release();
            Init();
        }

        if (INPUT->KeyDown('H'))
        {
            ColOnOff();
        }

        switch (gameState)
        {
        case Gungeon::GameState::start:
            Start();
            break;
        case Gungeon::GameState::waitingRoom:
            WaitingRoom();
            break;
        case Gungeon::GameState::enteringRoom:
            EnteringRoom();
            break;
        case Gungeon::GameState::waitingSpawn:
            WaitingSpawn();
            break;
        case Gungeon::GameState::fight:
            Fight();
            break;
        }


        if (mapGen) mapGen->Update();
        if (player) player->Update();
        for (auto& elem : spawnEffect) if (elem) elem->Update();
        for (auto& elem : enemy) if (elem) elem->Update();
        if (boss) boss->Update();
        if (mapObj) mapObj->Update();


        if (INPUT->KeyDown('1'))
        {
            gameState = GameState::start;
            fadeOut = true;
            SCENE->ChangeScene("Scene01", 1.0f);
        }

        ChangeUpdateScene();
    }

    void Scene02::LateUpdate()
    {
        if (mapGen)
        {
            mapGen->LateUpdate();
        }

        switch (gameState)
        {
        case Gungeon::GameState::start:
        case Gungeon::GameState::waitingRoom:
            break;
        case Gungeon::GameState::enteringRoom:
        case Gungeon::GameState::waitingSpawn:
        case Gungeon::GameState::fight:
            IntersectPlayer();
            IntersectEnemy();
            IntersectBoss();
            IntersectMapObj();
            break;
        }
    }

    void Scene02::Render()
    {
        if (mapGen)
        {
            mapGen->Render();

            for (auto& elem : spawnEffect) if (elem) elem->Render();
        }

        if (player) player->shadow->Render();
        for (auto& elem : enemy) if (elem) elem->shadow->Render();
        if (boss) boss->shadow->Render();

        if (mapObj) mapObj->Render();
        for (auto& elem : enemy) if (elem) elem->Render();
        if (player) player->Render();
        if (boss) boss->Render();

        // ÃÖÀûÈ­ ÀÌ½´·Î zorder ÁÖ¼®
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

    void Scene02::Start()
    {
        if (!mapGen) return;

        mapGen->Update();

        if (mapGen->selectedRooms.size() > 0)
        {
            gameState = GameState::waitingRoom;
        }
    }

    void Scene02::WaitingRoom()
    {
        curRoomIdx = 0;
        curRoom = mapGen->selectedRooms[curRoomIdx];
        SpawnPlayer();

        gameState = GameState::enteringRoom;
    }

    void Scene02::EnteringRoom()
    {
        // °ñµå Èí¼ö
        for (auto& elem : enemy)
        {
            if (elem->dropItem->flagAbsorbed)
            {
                elem->dropItem->targetPos = player->Pos();
            }
        }
        if (boss->dropItem->flagAbsorbed)
        {
            boss->dropItem->targetPos = player->Pos();
        }

        // ´ÙÀ½ ¹æ ÀÔÀå ÆÇ´Ü
        Int2 playerOn;
        if (mapGen->tilemap->WorldPosToTileIdx(player->Pos(), playerOn))
        {
            afterRoomIdx = mapGen->tilemap->Tiles[playerOn.x][playerOn.y].roomIdx;

            if (afterRoomIdx > 0 &&
                false == mapGen->selectedRooms[afterRoomIdx]->cleared)
            {
                if (curRoomIdx != afterRoomIdx)
                {
                    curRoomIdx = afterRoomIdx;
                    if (curRoomIdx > 0)
                    {
                        curRoom = mapGen->selectedRooms[curRoomIdx];
                        SpawnEffect();

                        gameState = GameState::waitingSpawn;
                    }
                }
            }
        }
    }

    void Scene02::WaitingSpawn()
    {
        bool flag = true;

        for (auto& elem : spawnEffect)
        {
            if (elem->state != State::die)
            {
                flag = false;
            }
        }

        if (flag)
        {
            SpawnEnemy();
            gameState = GameState::fight;
        }
    }

    void Scene02::Fight()
    {
        bool flagCleared = true;

        for (auto& elem : enemy)
        {
            if (elem->state != State::die)
            {
                flagCleared = false;

                elem->targetPos = player->Pos();
                elem->FindPath(mapGen->tilemap);
            }
        }

        if (boss->state != State::die)
        {
            flagCleared = false;

            boss->targetPos = player->Pos();
            boss->weapon->col->rotation = Utility::DirToRadian(player->Pos());

            switch (boss->pattern)
            {
            case BossPattern::shield:
            case BossPattern::cluster:
                boss->FindPath(mapGen->tilemap);
                break;
            default:
                boss->DontFindPath();
                break;
            }
        }

        // °ñµå Èí¼ö ÇÃ·¡±×
        if (flagCleared)
        {
            curRoom->cleared = true;
            for (auto& elem : enemy)
            {
                elem->dropItem->flagAbsorbed = true;
            }
            boss->dropItem->flagAbsorbed = true;
        }

        if (curRoom->cleared)
        {
            gameState = GameState::enteringRoom;
        }
    }

    void Scene02::SpawnPlayer()
    {
        CAM->position = curRoom->Pos();
        CAM->zoomFactor = Vector3(1.0f, 1.0f, 1.0f);

        player->Spawn(Vector2(curRoom->Pos().x, curRoom->Pos().y));
        player->Update();
    }

    void Scene02::SpawnEffect()
    {
        int idx = 0;
        for (auto& elem : spawnEffect)
        {
            elem->Spawn(curRoom->enemySpawnPos[idx]);
            idx++;
        }
    }

    void Scene02::SpawnEnemy()
    {
        int idx = 0;
        for (auto& elem : enemy)
        {
            elem->Spawn(curRoom->enemySpawnPos[idx]);
            idx++;
        }

        boss->Spawn(curRoom->enemySpawnPos[idx]);
    }

    void Scene02::IntersectPlayer()
    {
        int idx = 0;

        if (mapGen->IntersectTileUnit(player))
        {
            player->StepBack();
        }

        // ÇÃ·¹ÀÌ¾î ÃÑ¾Ë
        for (auto& bulletElem : player->bullet)
        {
            if (bulletElem->isFired)
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
        }
    }

    void Scene02::IntersectEnemy()
    {
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

            // Àû ÃÑ¾Ë
            for (auto& bulletElem : enemyElem->bullet)
            {
                if (bulletElem->isFired)
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
            }

            if (enemyElem->dropItem->state == State::idle &&
                enemyElem->dropItem->col->Intersect(player->col))
            {
                enemyElem->dropItem->Hit();
                player->PlusMoney(1);
            }

            enemyElem->LateUpdate();
        }
    }

    void Scene02::IntersectBoss()
    {
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

        // º¸½º ÃÑ¾Ë
        for (auto& bulletElem : boss->bullet)
        {
            if (bulletElem->isFired)
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
        }

        if (boss->dropItem->state == State::idle &&
            boss->dropItem->col->Intersect(player->col))
        {
            boss->dropItem->Hit();
            player->PlusMoney(1);
        }

        Weapon* bossWeapon = boss->weapon;
        if (bossWeapon->state == State::idle &&
            bossWeapon->col->Intersect(player->col))
        {
            bossWeapon->Hit();
            player->EquipWeapon(bossWeapon);
        }

        boss->LateUpdate();
    }

    void Scene02::IntersectMapObj()
    {
        int idx = 0;
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
    }

    void Scene02::ChangeUpdateScene()
    {
        if (fadeOut)
        {
            LIGHT->light.radius -= 2000.0f * DELTA;
            LIGHT->light.lightColor.x += 0.5f * DELTA;
            LIGHT->light.lightColor.y += 0.5f * DELTA;
            LIGHT->light.lightColor.z += 0.5f * DELTA;

            if (TIMER->GetTick(timeFade, 1.0f))
            {
                fadeOut = false;
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
    void Scene02::ColOnOff()
    {
        player->col->isVisible = !player->col->isVisible;
        player->colTile->isVisible = !player->colTile->isVisible;
        player->weapons[player->curWeaponIdx]->firePos->isVisible = !player->weapons[player->curWeaponIdx]->firePos->isVisible;

        for (auto& bulletElem : player->bullet)
        {
            bulletElem->col->isVisible = !bulletElem->col->isVisible;
        }

        for (auto& elem : enemy)
        {
            elem->col->isVisible = !elem->col->isVisible;
            elem->colTile->isVisible = !elem->colTile->isVisible;
            elem->weapon->firePos->isVisible = !elem->weapon->firePos->isVisible;

            for (auto& bulletElem : elem->bullet)
            {
                bulletElem->col->isVisible = !bulletElem->col->isVisible;
            }
        }

        boss->col->isVisible = !boss->col->isVisible;
        boss->colTile->isVisible = !boss->colTile->isVisible;
        boss->weapon->firePos->isVisible = !boss->weapon->firePos->isVisible;

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
