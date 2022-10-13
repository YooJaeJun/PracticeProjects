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
        if (mapGen) mapGen->useGui = false;
        curRoom = nullptr;
        curRoomIdx = 0;
        afterRoomIdx = -2;
        roomClearCount = 0;
        roomClearCountForBossBattle = 1;
        timeGateOpen = 0.0f;
        timeGateClosed = 0.0f;
        flagGateOpen = false;
        flagGateClosed = false;

        if (!player) player = new Player();

        spawnEffect.resize(enemyMax);
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

        gate = new Gate;
        gate->col->isVisible = false;
        gate->col->scale = Vector2(40.0F, 20.0f) * 2.0f;
        gate->SetPos(DEFAULTSPAWN);
        gate->idle = new ObImage(L"EnterTheGungeon/Level/Gate.png");
        gate->idle->isVisible = false;
        gate->idle->maxFrame.x = 9;
        gate->idle->scale = Vector2(604.0f / 9.0f, 165.0f) * 2.0f;
        gate->idle->SetParentRT(*gate->col);
        gate->idle->pivot = OFFSET_B;
        

        fadeOut = false;
        timeFade = 0.0f;
        SOUND->Stop("SCENE01");
        // SOUND->AddSound("15051562_MotionElements_8-bit-arcade-swordsman.wav", "SCENE02", true);
        SOUND->Play("SCENE02");
        SOUND->AddSound("gun.wav", "GUN", false);
    }

    void Scene02::Release()
    {
        for (auto& elem : mapGen->selectedRooms) elem->cleared = false;
        for (auto& elem : enemy) SafeRelease(elem);
        SafeRelease(player);
    }

    void Scene02::Update()
    {
        if (INPUT->KeyDown('1'))
        {
            gameState = GameState::start;
            fadeOut = true;
            SCENE->ChangeScene("Scene01", 1.0f);
        }
        else if (INPUT->KeyDown('2'))
        {
            gameState = GameState::start;
            for (auto& elem : curRoom->doorTileIdxs)
            {
                mapGen->tilemap->SetTileState(elem, TileState::door);
            }
            Release();
            Init();
        }
        else if (INPUT->KeyDown('3'))
        {
            fadeOut = true;
            SCENE->ChangeScene("Scene03", 1.0f);
        }

        ChangeUpdateScene();

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
        gate->Update();
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
            break;
        }

        GateProcess();
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

        for (auto& elem : enemy) if (elem) elem->Render();
        if (player) player->Render();
        gate->Render();

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
        // 골드 흡수
        for (auto& elem : enemy)
        {
            if (elem->dropItem->flagAbsorbed)
            {
                elem->dropItem->targetPos = player->Pos();
            }
        }

        // 다음 방 입장 판단
        Int2 playerOn;
        if (mapGen->tilemap->WorldPosToTileIdx(player->Pos(), playerOn))
        {
            afterRoomIdx = mapGen->tilemap->Tiles[playerOn.x][playerOn.y].roomIdx;

            if (afterRoomIdx > 0 &&
                curRoomIdx != afterRoomIdx &&
                false == mapGen->selectedRooms[afterRoomIdx]->cleared)
            {
                curRoomIdx = afterRoomIdx;
                curRoom = mapGen->selectedRooms[curRoomIdx];

                SpawnEffect();

                gameState = GameState::waitingSpawn;
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

            for (auto& elem : curRoom->doorTileIdxs)
            {
                mapGen->tilemap->SetTileState(elem, TileState::wall);
            }

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

        if (flagCleared)
        {
            curRoom->cleared = true;

            for (auto& elem : curRoom->doorTileIdxs)
            {
                mapGen->tilemap->SetTileState(elem, TileState::door);
            }

            for (auto& elem : enemy)
            {
                elem->dropItem->flagAbsorbed = true;
            }
        }

        if (curRoom->cleared)
        {
            roomClearCount++;
            if (roomClearCount >= roomClearCountForBossBattle)
            {
                gate->SetPos(curRoom->Pos());
                gate->idle->ChangeAnim(AnimState::once, 0.1f);
                gate->idle->isVisible = true;
            }

            gameState = GameState::enteringRoom;
        }
    }

    void Scene02::SpawnPlayer()
    {
        CAM->position = curRoom->Pos();
        CAM->zoomFactor = Vector3(1.0f, 1.0f, 1.0f);

        player->Spawn(Vector2(curRoom->Pos().x, curRoom->Pos().y));
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
    }

    void Scene02::IntersectPlayer()
    {
        if (mapGen->tilemap->IntersectTileUnit(player->colTile))
        {
            player->StepBack();
        }

        // 플레이어 총알
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

                if (mapGen->tilemap->IntersectTilePos(bulletElem->Pos()))
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

            if (mapGen->tilemap->IntersectTileUnit(enemyElem->colTile))
            {
                enemyElem->StepBack();
            }

            // 적 총알
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

                    if (mapGen->tilemap->IntersectTilePos(bulletElem->Pos()))
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

    void Scene02::GateProcess()
    {
        if (roomClearCount >= roomClearCountForBossBattle)
        {
            if (TIMER->GetTick(timeGateOpen, 1.5f))
            {
                flagGateOpen = true;
            }

            if (flagGateOpen)
            {
                gate->col->isVisible = true;
                if (gate->col->Intersect(player->col))
                {
                    roomClearCount = 0;
                    gate->idle->ChangeAnim(AnimState::reverseOnce, 0.1f);
                    flagGateClosed = true;
                }
            }
        }

        if (flagGateClosed)
        {
            flagGateClosed = false;
            fadeOut = true;
            SCENE->ChangeScene("Scene03", 1.0f);
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

    // 치트
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
    }
}
