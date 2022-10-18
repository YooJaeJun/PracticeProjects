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
        MAP->useGui = false;

        if (!player) player = new Player();

        spawnEffect.resize(enemyMax);
        for (auto& elem : spawnEffect)
        {
            if (!elem)
            {
                elem = new Effect;
                elem->idle = new ObImage(L"EnterTheGungeon/Level/Spawn.png");
                elem->state = State::die;
                elem->idle->maxFrame.x = 18;
                elem->idle->scale = Vector2(663.0f / 18.0f, 39.0f) * 3.5f;
                elem->idle->isVisible = false;
                elem->intervalDie = 1.8f;
            }
        }

        SpawnEnemy();

        gate = new Gate;

        door.resize(doorMax);
        for (auto& elem : door)
        {
            elem = new Door;
            elem->col->scale = Vector2(16.0f, 128.0f / 8.0f) * 6.0f;
            elem->col->pivot = OFFSET_LB;
            elem->SetPos(DEFAULTSPAWN);
            elem->idle = new ObImage(L"EnterTheGungeon/Level/Door.png");
            elem->idle->maxFrame.y = 8;
            elem->idle->scale = Vector2(24.0f, 192.0f / 8.0f) * 4.0f;
            elem->idle->SetParentRT(*elem->col);
            elem->idle->pivot = OFFSET_LB;
        }
        
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
            isChangingScene = true;
            SCENE->ChangeScene("Scene01", 1.0f);
        }
        else if (INPUT->KeyDown('2'))
        {
            gameState = GameState::start;
            if (curRoom)
            {
                for (auto& elem : curRoom->doorTileIdxs)
                {
                    MAP->tilemap->SetTileState(elem, TileState::door);
                }
            }
            Release();
            Init();
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

        GateProcess();

        if (mapGen) mapGen->Update();
        gate->Update();
        for (auto& elem : door) elem->Update();
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
            player->Update();
            IntersectEnemy();
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
        SetCamera();
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
        if (MAP->tilemap->WorldPosToTileIdx(player->Pos(), playerOn) &&
            MAP->tilemap->GetTileState(playerOn) == TileState::floor)
        {
            afterRoomIdx = MAP->tilemap->Tiles[playerOn.x][playerOn.y].roomIdx;

            if (afterRoomIdx > 0 &&
                curRoomIdx != afterRoomIdx &&
                false == mapGen->selectedRooms[afterRoomIdx]->cleared)
            {
                curRoomIdx = afterRoomIdx;
                curRoom = mapGen->selectedRooms[curRoomIdx];

                SpawnEffect();

                int idx = 0;
                for (auto& on : curRoom->doorTileIdxs)
                {
                    MAP->tilemap->SetTileState(on, TileState::wall);
                    door[idx]->idle->frame.y = MAP->tilemap->GetTileDoorDir(on);
                    door[idx]->SetPos(MAP->tilemap->TileIdxToWorldPos(on));
                    door[idx]->idle->isVisible = true;
                    idx++;
                }

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

                
                switch (elem->state)
                {
                case State::attack:
                case State::cinematic:
                    break;
                default:
                    elem->FindPath(MAP->tilemap);
                }
            }
        }

        if (flagCleared)
        {
            curRoom->cleared = true;

            int idx = 0;
            for (auto& elem : curRoom->doorTileIdxs)
            {
                MAP->tilemap->SetTileState(elem, TileState::door);

                door[idx]->SetPos(DEFAULTSPAWN);
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

            gameState = GameState::enteringRoom;
        }
    }

    void Scene02::SetCamera()
    {
        CAM->position = curRoom->Pos();
        CAM->zoomFactor = Vector3(1.0f, 1.0f, 1.0f);
    }

    void Scene02::SpawnPlayer()
    {
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
            SafeRelease(elem);
            int r = RANDOM->Int(0, 6);
            if (r < 2) elem = new Enemy3();
            else if (r < 4) elem = new Enemy1();
            else elem = new Enemy2();
            if (curRoom) elem->Spawn(curRoom->enemySpawnPos[idx]);
            idx++;
        }
    }

    void Scene02::IntersectPlayer()
    {
        if (MAP->tilemap->IntersectTileObj(player->colTile))
        {
            player->StepBack();
        }

        if (false == gate->flagIntersectPlayer &&
            player->col->Intersect(gate->col))
        {
            player->col->MoveWorldPos(Vector2(-150.0f, -100.0f) * DELTA);
        }

        if (curRoom)
        {
            for (auto& elem : door)
            {
                if (player->colTile->Intersect(elem->col))
                {
                    DirState doorDir = MAP->tilemap->GetTileDoorDir(elem->On());
                    float x, y;
                    switch (doorDir)
                    {
                    case dirB:
                        x = -dx[DirState::dirB];
                        y = -dy[DirState::dirB];
                        break;
                    case dirLB:
                        x = -dx[DirState::dirLB];
                        y = -dy[DirState::dirLB];
                        break;
                    case dirRB:
                        x = -dx[DirState::dirRB];
                        y = -dy[DirState::dirRB];
                        break;
                    case dirT:
                        x = -dx[DirState::dirT];
                        y = -dy[DirState::dirT];
                        break;
                    case dirLT:
                        x = -dx[DirState::dirLT];
                        y = -dy[DirState::dirLT];
                        break;
                    case dirRT:
                        x = -dx[DirState::dirRT];
                        y = -dy[DirState::dirRT];
                        break;
                    case dirL:
                        x = dx[DirState::dirL];
                        y = dy[DirState::dirL];
                        break;
                    case dirR:
                        x = dx[DirState::dirR];
                        y = dy[DirState::dirR];
                        break;
                    case dirNone:
                        x = dx[DirState::dirNone];
                        y = dy[DirState::dirNone];
                        break;
                    }
                    player->col->MoveWorldPos(Vector2(x, y));
                }
            }
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

                if (MAP->tilemap->IntersectTilePos(bulletElem->Pos()))
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

            if (MAP->tilemap->IntersectTileObj(enemyElem->colTile))
            {
                enemyElem->StepBack();
            }

            if (enemyElem->col->Intersect(gate->col))
            {
                Vector2 velocity = gate->Pos() - enemyElem->Pos();
                enemyElem->col->MoveWorldPos(-velocity * DELTA);
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

                    if (MAP->tilemap->IntersectTilePos(bulletElem->Pos()))
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
            roomClearCount = 0;
            gate->Spawn(curRoom->Pos());
        }

        switch (gate->gateState)
        {
        case Gungeon::GateState::none:
        case Gungeon::GateState::opening:
            break;

        case Gungeon::GateState::open:
            if (gate->colTile->Intersect(player->col))
            {
                gate->flagIntersectPlayer = true;
            }
            break;

        case Gungeon::GateState::cinematic:
            player->state = State::cinematic;
            break;

        case Gungeon::GateState::process:
            gate->playerDest = Vector2(gate->col->GetWorldPos().x, gate->col->GetWorldPos().y + 70.0f);

            if (abs(gate->playerDest.x - player->Pos().x) > 1.0f &&
                abs(gate->playerDest.y - player->Pos().y) > 1.0f)
            {
                player->idle->isVisible = false;
                player->walk->isVisible = true;
                Vector2 dir = gate->playerDest - player->Pos();
                dir.Normalize();
                player->col->MoveWorldPos(dir * 80.0f * DELTA);
            }
            else
            {
                gate->gateState = GateState::setting;
            }
            break;

        case Gungeon::GateState::setting:
            player->walk->isVisible = false;
            player->idle->isVisible = true;
            break;

        case Gungeon::GateState::set:
            break;

        case Gungeon::GateState::closing:
            if (gate->flagPlayerDisappear)
            {
                player->idle->isVisible = false;
                player->walk->isVisible = false;
                player->weapons[player->curWeaponIdx]->idle->isVisible = false;
                player->shadow->isVisible = false;
            }
            break;

        case Gungeon::GateState::closed:
            gate->gateState = GateState::none;
            isChangingScene = true;
            SCENE->ChangeScene("Scene03", 1.0f);
            break;
        }
    }

    void Scene02::ChangeUpdateScene()
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

    // 치트
    void Scene02::ColToggle()
    {
        player->ColToggle();

        for (auto& elem : enemy)
        {
            elem->ColToggle();
        }

        for (auto& elem : door) elem->ColToggle();
        gate->ColToggle();
    }
}
