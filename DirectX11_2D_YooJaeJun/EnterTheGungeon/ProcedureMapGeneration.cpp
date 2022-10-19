#include "stdafx.h"

namespace Gungeon
{
    ProcedureMapGeneration::ProcedureMapGeneration()
    {
        Init();
    }

    void ProcedureMapGeneration::Init()
    {
        MAP->useGui = true;

        LIGHT->light.radius = 4000.0f;

        state = MapGenState::spray;

        // room
        candidateRooms = vector<Room*>(roomMax);
        int idx = 0;
        for (auto& room : candidateRooms)
        {
            room = new Room();

            // 일부 방 선택할 만한 크기 보장
            if (idx < 5)
            {
                room->col->scale.x = 100.0f * RANDOM->Int(11, 14);
                room->col->scale.y = 100.0f * RANDOM->Int(11, 14);
            }
            else
            {
                room->col->scale.x = 100.0f * RANDOM->Int(9, 13);
                room->col->scale.y = 100.0f * RANDOM->Int(9, 13);
            }

            map<Int2, bool> dic;
            int xRand = 0, yRand = 0;
            do {
                xRand = RANDOM->Int(-10, 10);
                yRand = RANDOM->Int(-10, 10);
            } while (dic[Int2(xRand, yRand)]);

            dic[Int2(xRand, yRand)]++;

            room->SetPosX(100.0f * xRand);
            room->SetPosY(100.0f * yRand);
            room->col->isFilled = false;
            room->col->color = Color(1.0f, 0.6f, 0.6f);
            room->col->collider = Collider::rect;

            idx++;
        }
        roomScaleForSelect = 1000.0f;
    }

    void ProcedureMapGeneration::Release()
    {
        for (auto& elem : candidateRooms) elem->Release();
        candidateRooms.clear();
        for (auto& elem : selectedRooms) elem->Release();
        selectedRooms.clear();
        roomNode.clear();
        triangulation.nodesLinked.clear();
        triangulation.edges.clear();
        triangulation.triangles.clear();
        triangulation.nodesForIndex.clear();
        visited.clear();
        linesTriangulated.clear();
        linesMST.clear();
    }

    void ProcedureMapGeneration::Update()
    {
        if (INPUT->KeyPress(VK_LEFT) || INPUT->KeyPress('A'))
        {
            CAM->position.x -= 1500.0f * DELTA;
        }
        if (INPUT->KeyPress(VK_RIGHT) || INPUT->KeyPress('D'))
        {
            CAM->position.x += 1500.0f * DELTA;
        }
        if (INPUT->KeyPress(VK_UP) || INPUT->KeyPress('W'))
        {
            CAM->position.y += 1500.0f * DELTA;
        }
        if (INPUT->KeyPress(VK_DOWN) || INPUT->KeyPress('S'))
        {
            CAM->position.y -= 1500.0f * DELTA;
        }


        switch (state)
        {
        case MapGenState::spray:
        {
            Spray();
            if (TIMER->GetTick(timer, timeDefault))
            {
                state = MapGenState::spread;
            }
            break;
        }
        case MapGenState::spread:
        {
            Spread();
            if (flagSpread)
            {
                state = MapGenState::select;
            }
            break;
        }
        case MapGenState::select:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                Select();
                state = MapGenState::triangulate;
            }
            break;
        }
        case MapGenState::triangulate:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                Triangulate();
                state = MapGenState::span;
            }
            break;
        }
        case MapGenState::span:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                Spanning();
                state = MapGenState::loop;
            }
            break;
        }
        case MapGenState::loop:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                Loop();
                state = MapGenState::clean;
            }
            break;
        }
        case MapGenState::clean:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                Clean();
                state = MapGenState::roomTile;
            }
            break;
        }
        case MapGenState::roomTile:
        {
            RoomTile();
            state = MapGenState::passageTile;
            break;
        }
        case MapGenState::passageTile:
        {
            PassageTile();
            state = MapGenState::passageWallTile;
            break;
        }
        case MapGenState::passageWallTile:
        {
            PassageWallTile();
            state = MapGenState::prop;
            break;
        }
        case MapGenState::prop:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                Prop();
                state = MapGenState::spawner;
            }
            break;
        }
        case MapGenState::spawner:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                Spawner();
                state = MapGenState::finish;
            }
            break;
        }
        case MapGenState::finish:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                Finish();
            }
            break;
        }
        default:
        {
            break;
        }//case
        }//switch

        SetTilemapGUI();

        for (auto& elem : candidateRooms) if (elem) elem->Update();
        for (auto& elem : selectedRooms) if (elem) elem->Update();
        for (auto& elem : linesTriangulated) elem.Update();
        for (auto& elem : linesMST) elem.Update();
    }

    void ProcedureMapGeneration::LateUpdate()
    {
    }

    void ProcedureMapGeneration::Render()
    {
        for (auto& elem : candidateRooms) if (elem) elem->Render();
        for (auto& elem : selectedRooms) if (elem) elem->Render();
        for (auto& elem : linesTriangulated) elem.Render();
        for (auto& elem : linesMST) elem.Render();
    }

    void ProcedureMapGeneration::ResizeScreen()
    {
    }

    void ProcedureMapGeneration::Spray()
    {
        // Init이 대체하고, 지연시간만 대기
    }

    void ProcedureMapGeneration::Spread()
    {
        flagSpread = true;

        for (auto& room : candidateRooms)
        {
            for (auto& room2 : candidateRooms)
            {
                if (room == room2) continue;

                if (room->col->Intersect(room2->col))
                {
                    Vector2 dir = room->col->GetWorldPos() - room2->col->GetWorldPos();

                    float x, y;
                    if (dir.x >= 0.0f) x = MAP->tilemap->scale.x / 2.0f;
                    else x = MAP->tilemap->scale.x * -1.0f / 2.0f;
                    if (dir.y >= 0.0f) y = MAP->tilemap->scale.y / 2.0f;
                    else y = MAP->tilemap->scale.y * -1.0f / 2.0f;

                    room->SetPos(Vector2(room->Pos().x + x, room->Pos().y + y));
                    flagSpread = false;
                }
            }
            room->Update();
        }
    }

    void ProcedureMapGeneration::Select()
    {
        for (auto& elem : candidateRooms)
        {
            if (elem->col->scale.x > roomScaleForSelect &&
                elem->col->scale.y > roomScaleForSelect)
            {
                elem->col->scale.x -= 200.0f;
                elem->col->scale.y -= 200.0f;
                Int2 on;
                if (MAP->tilemap->WorldPosToTileIdx(elem->Pos(), on))
                {
                    elem->SetPos(MAP->tilemap->TileIdxToWorldPos(on));
                }
                elem->col->isFilled = true;
                elem->selected = true;

                selectedRooms.push_back(elem);
            }
        }

        selectedRooms[0]->roomType = RoomType::start;
        selectedRooms[0]->cleared = true;
        selectedRooms[1]->roomType = RoomType::treasure;
        selectedRooms[1]->treasureSpawnPos = Vector2(selectedRooms[1]->Pos().x, selectedRooms[1]->Pos().y + 250.0f);
        selectedRooms[1]->cleared = true;
    }

    void ProcedureMapGeneration::Triangulate()
    {
        int idx = 0;
        for (auto& elem : selectedRooms)
        {
            // 들로네 삼각분할 위한 노드
            roomNode.push_back(ObNode(idx, elem->Pos()));
            idx++;
        }

        triangulation.triangulate(roomNode);
        linesTriangulated = triangulation.edges;

        for (auto& elem : linesTriangulated)
        {
            elem.color = Color(1.0f, 1.0f, 1.0f);
        }
    }

    void ProcedureMapGeneration::Spanning()
    {
        // MST - Prim
        edgePq.push(linesTriangulated[0]);

        while (false == edgePq.empty())
        {
            ObLine curLine = edgePq.top();
            // 노드의 인덱스를 검사
            curLine.SetVIdx(triangulation.nodesForIndex[curLine.V()]);
            curLine.SetWIdx(triangulation.nodesForIndex[curLine.W()]);

            edgePq.pop();

            if (visited[curLine.V().index] && visited[curLine.W().index]) continue;
            visited[curLine.V().index] = true;
            visited[curLine.W().index] = true;

            curLine.color = Color(0.5f, 1.0f, 0.5f);
            linesMST.push_back(curLine);

            auto push = [&](const ObNode& node)
            {
                int size = triangulation.nodesLinked[node].size();
                ObNode nextNode;
                for (int i = 0; i < size; i++)
                {
                    nextNode = triangulation.nodesLinked[node][i];
                    nextNode.index = triangulation.nodesForIndex[nextNode];
                    edgePq.push(ObLine(node, nextNode));
                }
            };
            push(curLine.V());
            push(curLine.W());
        }
    }

    void ProcedureMapGeneration::Loop()
    {
        int count = max(1, linesTriangulated.size() / 15);

        while (count--)
        {
            float rand = RANDOM->Int(0, linesTriangulated.size() - 1);
            bool flag = false;
            for (auto& elem : linesMST)
            {
                if ((elem.V() == linesTriangulated[rand].V() && elem.W() == linesTriangulated[rand].W()) ||
                    (elem.V() == linesTriangulated[rand].W() && elem.W() == linesTriangulated[rand].V()))
                {
                    count++;
                    flag = true;
                    break;
                }
            }
            if (false == flag)
            {
                // 노드의 인덱스를 검사
                linesTriangulated[rand].SetVIdx(triangulation.nodesForIndex[linesTriangulated[rand].V()]);
                linesTriangulated[rand].SetWIdx(triangulation.nodesForIndex[linesTriangulated[rand].W()]);

                linesTriangulated[rand].color = Color(0.5f, 0.5f, 1.0f);
                linesMST.push_back(linesTriangulated[rand]);
            }
        }

        linesTriangulated.clear();
    }

    void ProcedureMapGeneration::Clean()
    {
        for (auto& elem : candidateRooms)
        {
            if (false == elem->selected)
            {
                elem = nullptr;
            }
        }
        candidateRooms.clear();
    }

    void ProcedureMapGeneration::RoomTile()
    {
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

        auto SetWall2 = [&](Int2 on, int roomIdx, DirState dir)
        {
            MAP->tilemap->SetTile(on,
                wallImgDir[(int)dir],
                MAP->imgIdx,
                (int)TileState::wall,
                Color(0.5f, 0.5f, 0.5f, 1.0f),
                roomIdx,
                dir);
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
                SetWall2(Int2(x, dest.y), roomIdx, DirState::dirT);
                SetWall2(Int2(x, sour.y), roomIdx, DirState::dirB);
            }

            for (int y = sour.y; y <= dest.y; y++)
            {
                SetWall2(Int2(sour.x, y), roomIdx, DirState::dirL);
                SetWall2(Int2(dest.x, y), roomIdx, DirState::dirR);
            }

            SetWall2(Int2(sour.x, sour.y), roomIdx, DirState::dirLB);
            SetWall2(Int2(sour.x, dest.y), roomIdx, DirState::dirLT);
            SetWall2(Int2(dest.x, sour.y), roomIdx, DirState::dirRB);
            SetWall2(Int2(dest.x, dest.y), roomIdx, DirState::dirRT);
        };

        int idx = 0;
        for (auto& elem : selectedRooms)
        {
            SetTile1(elem, idx);
            elem->col->isVisible = false;
            idx++;
        }
    }

    void ProcedureMapGeneration::PassageTile()
    {
        // room index와 node index 연결정보
        for (auto& elem : linesMST)
        {
            for (int roomIndex = 0; roomIndex < selectedRooms.size(); roomIndex++)
            {
                Vector2 v = Vector2(elem.V().x, elem.V().y);
                if (almostEqualVector2(v, selectedRooms[roomIndex]->Pos()))
                {
                    nodesForRoomIndex[v] = roomIndex;
                }

                Vector2 w = Vector2(elem.W().x, elem.W().y);
                if (almostEqualVector2(w, selectedRooms[roomIndex]->Pos()))
                {
                    nodesForRoomIndex[w] = roomIndex;
                }
            }
        }

        // 1. 8방향 체크해 문의 방향을 정하고, 2. 방향에 따라 다른 이미지, 3. 모서리에 위치할 시 예외처리
        auto SetDoor = [&](Int2 on, const int roomIdx, const DirState dir)
        {
            deque<bool> dirWall(8);

            for (int i = 0; i < 8; i++)
            {
                int nx = on.x + dx[i];
                int ny = on.y + dy[i];

                if (MAP->tilemap->GetTileState(Int2(nx, ny)) == TileState::wall ||
                    MAP->tilemap->GetTileState(Int2(nx, ny)) == TileState::door)
                {
                    dirWall[i] = true;
                }
            }

            Int2 doorTileIdx = on;
            Int2 floorTileIdx;

            // 가로, 세로
            if (dirWall[DirState::dirB] && dirWall[DirState::dirT]) 
            {}
            else if (dirWall[DirState::dirL] && dirWall[DirState::dirR]) 
            {}
            // 모서리에 위치 시 다른 이미지 출력. 그리고 이동 가능하게 옆에 평면타일로 예외처리
            else
            {
                if ((dirWall[DirState::dirL] && dirWall[DirState::dirB]))
                {
                    floorTileIdx.x = on.x;
                    floorTileIdx.y = on.y;
                    doorTileIdx.x = on.x + dx[DirState::dirL];
                    doorTileIdx.y = on.y + dy[DirState::dirL];
                }
                else if ((dirWall[DirState::dirB] && dirWall[DirState::dirR]))
                {
                    floorTileIdx.x = on.x;
                    floorTileIdx.y = on.y;
                    doorTileIdx.x = on.x + dx[DirState::dirR];
                    doorTileIdx.y = on.y + dy[DirState::dirR];
                }

                else if ((dirWall[DirState::dirR] && dirWall[DirState::dirT]))
                {
                    floorTileIdx.x = on.x;
                    floorTileIdx.y = on.y;
                    doorTileIdx.x = on.x + dx[DirState::dirR];
                    doorTileIdx.y = on.y + dy[DirState::dirR];
                }
                else if (dirWall[DirState::dirT] && dirWall[DirState::dirL])
                {
                    floorTileIdx.x = on.x;
                    floorTileIdx.y = on.y;
                    doorTileIdx.x = on.x + dx[DirState::dirL];
                    doorTileIdx.y = on.y + dy[DirState::dirL];
                }

                MAP->tilemap->SetTile(floorTileIdx,
                    Int2(RANDOM->Int(floorImgMin.x, floorImgMax.x),
                        RANDOM->Int(floorImgMin.y, floorImgMax.y)),
                    MAP->imgIdx,
                    (int)TileState::floor, 
                    Color(0.5f, 0.5f, 0.5f, 0.5f),
                    -1, 
                    dir);
            }

            MAP->tilemap->SetTile(doorTileIdx,
                Int2(RANDOM->Int(floorImgMin.x, floorImgMax.x),
                    RANDOM->Int(floorImgMin.y, floorImgMax.y)),
                MAP->imgIdx,
                (int)TileState::door,
                Color(0.5f, 0.5f, 0.5f, 0.5f),
                -1, 
                dir);

            selectedRooms[roomIdx]->doorTileIdxs.push_back(doorTileIdx);
        };


        // 복도 A* 2회 - 방 간 최단거리 위함
        // 1. 시작방 중점 -> 시작방 벽
        // 2. 시작방 벽 -> 끝방 벽

        auto AStar = [&](Int2 sour, Int2 dest, bool first) ->Int2
        {
            if (MAP->tilemap->PathFinding(sour, dest, way, false))
            {
                int sourRoomIdx = MAP->tilemap->GetTileRoomIndex(sour);
                int destRoomIdx = MAP->tilemap->GetTileRoomIndex(dest);

                Int2 beforeOn = way.back()->idx;
                int beforeRoomIdx = MAP->tilemap->GetTileRoomIndex(beforeOn);
                DirState beforeDir = MAP->tilemap->GetTileDir(beforeOn);

                for (int cur = way.size() - 2; cur >= 0; cur--)
                {
                    Int2 curOn = way[cur]->idx;
                    TileState curTileStateOn = MAP->tilemap->GetTileState(curOn);
                    int curRoomIdx = MAP->tilemap->GetTileRoomIndex(curOn);
                    DirState curDir = MAP->tilemap->GetTileDir(curOn);

                    if (curTileStateOn == TileState::none)
                    {
                        MAP->tilemap->SetTile(curOn,
                            Int2(RANDOM->Int(floorImgMin.x, floorImgMax.x),
                                RANDOM->Int(floorImgMin.y, floorImgMax.y)),
                            MAP->imgIdx,
                            (int)TileState::floor);
                    }

                    if (first && curRoomIdx != beforeRoomIdx)
                    {
                        SetDoor(beforeOn, beforeRoomIdx, beforeDir);
                        way.clear();
                        return curOn;
                    }
                    else if (!first && curRoomIdx == destRoomIdx)
                    {
                        SetDoor(curOn, curRoomIdx, curDir);
                        way.clear();
                        return curOn;
                    }

                    beforeOn = way[cur]->idx;
                    beforeRoomIdx = MAP->tilemap->GetTileRoomIndex(beforeOn);
                    beforeDir = MAP->tilemap->GetTileDir(beforeOn);
                }
            }
            assert(false);
        };

        // 시작
        for (auto& elem : linesMST)
        {
            const ObNode& v = elem.V();
            const ObNode& w = elem.W();

            ObNode mid = ObNode((w.x + v.x) / 2.0f, (w.y + v.y) / 2.0f);

            Vector2 vScaleHalf = selectedRooms[nodesForRoomIndex[v]]->col->scale / 2.0f;
            Vector2 wScaleHalf = selectedRooms[nodesForRoomIndex[w]]->col->scale / 2.0f;

            Vector2	start = Vector2(v.x, v.y);
            Vector2 end = Vector2(w.x, w.y);

            Int2 sour, dest;
            MAP->tilemap->WorldPosToTileIdx(start, sour);
            MAP->tilemap->WorldPosToTileIdx(end, dest);

            sour = AStar(sour, dest, true);
            AStar(sour, dest, false);
        }

        linesMST.clear();

        MAP->tilemap->CreateTileCost();
    }

    void ProcedureMapGeneration::PassageWallTile()
    {
        for (int x = 0; x < MAP->tileSize.y; x++)
        {
            for (int y = 0; y < MAP->tileSize.x; y++)
            {
                if (MAP->tilemap->Tiles[x][y].roomIdx == -1 &&
                    MAP->tilemap->Tiles[x][y].state == TileState::floor)
                {
                    for (int i = 0; i < 8; i++)
                    {
                        int nx = x + dx[i];
                        int ny = y + dy[i];
                        if (nx < 0 || nx >= MAP->tileSize.x || ny < 0 || ny >= MAP->tileSize.y) continue;

                        if (MAP->tilemap->Tiles[nx][ny].state == TileState::none)
                        {
                            MAP->tilemap->SetTile(Int2(nx, ny),
                                Int2(RANDOM->Int(passageWallImgMin.x, passageWallImgMax.x),
                                    RANDOM->Int(passageWallImgMin.y, passageWallImgMax.y)),
                                MAP->imgIdx,
                                (int)TileState::wall);
                        }
                    }
                }
            }
        }

        MAP->tilemap->CreateTileCost();
    }

    void ProcedureMapGeneration::Prop()
    {
        for (auto& elem : selectedRooms)
        {
            Int2 on;
            MAP->tilemap->WorldPosToTileIdx(elem->Pos(), on);
            Int2 scaleOn = Int2(elem->col->scale.x / 100, elem->col->scale.y / 100);
            Int2 halfScaleOn = scaleOn / 2;

            int t = 3;
            while (t--)
            {
                int rx = RANDOM->Int(on.x - halfScaleOn.x, on.x + halfScaleOn.x);
                int ry = RANDOM->Int(on.y - halfScaleOn.y, on.y + halfScaleOn.y);

                if (MAP->tilemap->Tiles[rx][ry].state == TileState::floor)
                {
                    MAP->tilemap->SetTile(Int2(rx, ry),
                        Int2(RANDOM->Int(propImgMin.x, propImgMax.x),
                            RANDOM->Int(propImgMin.y, propImgMax.y)),
                        MAP->imgIdx);
                }
            }
        }
    }

    void ProcedureMapGeneration::Spawner()
    {
        for (auto& elem : selectedRooms)
        {
            for (auto& spawnPosElem : elem->enemySpawnPos)
            {
                float xPos, yPos;
                xPos = elem->Pos().x + RANDOM->Float(-elem->col->scale.x * 0.35f, elem->col->scale.x * 0.35f);
                yPos = elem->Pos().y + RANDOM->Float(-elem->col->scale.y * 0.35f, elem->col->scale.y * 0.35f);
                spawnPosElem = Vector2(xPos, yPos);
            }
        }
    }

    void ProcedureMapGeneration::Finish()
    {
    }

    void ProcedureMapGeneration::SetTilemapGUI()
    {
    }
}