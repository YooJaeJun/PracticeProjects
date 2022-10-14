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
                int r = RANDOM->Int(0, 1);
                if (r) elem = new Enemy1();
                else elem = new Enemy2();
            }
        }

        gate = new Gate;

        door.resize(doorMax);
        for (auto& elem : door)
        {
            elem = new Door;
            elem->col->isVisible = false;
            elem->col->scale = Vector2(16.0f, 128.0f / 8.0f) * 6.0f;
            elem->col->pivot = OFFSET_LB;
            elem->SetPos(DEFAULTSPAWN);
            elem->idle = new ObImage(L"EnterTheGungeon/Level/Door.png");
            elem->idle->isVisible = false;
            elem->idle->maxFrame.y = 8;
            elem->idle->scale = Vector2(16.0f, 128.0f / 8.0f) * 6.0f;
            elem->idle->SetParentRT(*elem->col);
            elem->idle->pivot = OFFSET_LB;
        }
        

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
            ColToggle();
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
        gate->Update();
        for (auto& elem : door) elem->Update();
        if (player) player->Update();
        for (auto& elem : spawnEffect) if (elem) elem->Update();
        for (auto& elem : enemy) if (elem) elem->Update();
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

        gate->Render();
        for (auto& elem : door) elem->Render();

        if (player) player->shadow->Render();
        for (auto& elem : enemy) if (elem) elem->shadow->Render();

        for (auto& elem : enemy) if (elem) elem->Render();
        if (player) player->Render();

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

            int idx = 0;
            for (auto& on : curRoom->doorTileIdxs)
            {
                mapGen->tilemap->SetTileState(on, TileState::wall);
                door[idx]->idle->frame.y = mapGen->tilemap->GetTileDoorDir(on);
                door[idx]->SetPos(mapGen->tilemap->TileIdxToWorldPos(on));
                door[idx]->col->isVisible = true;
                door[idx]->idle->isVisible = true;
                idx++;
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

            int idx = 0;
            for (auto& elem : curRoom->doorTileIdxs)
            {
                mapGen->tilemap->SetTileState(elem, TileState::door);
                door[idx]->col->isVisible = false;
                door[idx]->idle->isVisible = false;
                idx++;
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
            if (TIMER->GetTick(gate->timeGateOpen, 1.5f))
            {
                gate->flagGateOpen = true;
            }

            if (gate->col->Intersect(player->col))
            {
                player->StepBack();
            }

            if (gate->flagGateOpen)
            {
                gate->col->isVisible = true;
                gate->colTile->isVisible = true;
                if (gate->colTile->Intersect(player->col))
                {
                    roomClearCount = 0;
                    gate->col->isVisible = false;
                    gate->colTile->isVisible = false;
                    gate->idle->ChangeAnim(AnimState::reverseOnce, 0.1f);
                    gate->flagGateClosed = true;
                }
            }
        }

        if (gate->flagGateClosed)
        {
            gate->flagGateClosed = false;
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
    void Scene02::ColToggle()
    {
        player->ColToggle();

        for (auto& elem : enemy)
        {
            elem->ColToggle();
        }
    }
}
