#include "stdafx.h"

namespace Gungeon
{
    ProcedureMapGeneration::ProcedureMapGeneration()
    {
        Init();
    }

    void ProcedureMapGeneration::Init()
    {
        timer = 0.0f;

        state = GameState::spray;

        LIGHT->light.radius = 3000.0f;

        flagSpread = false;

        // tilemap
        tilemap = new ObTileMap;
        tilemap->scale = Vector2(100.0f, 100.0f);
        tilemap->SetWorldPos(Vector2(-app.GetHalfWidth() - 4000.0f, -app.GetHalfHeight() - 4000.0f));
        imgIdx = 1;
        tileSize = Int2(100, 100);
        tilemap->ResizeTile(tileSize);
        tileColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
        tileState = 0;
        tilemap->CreateTileCost();

        // room
        rooms = vector<Room*>(roomMax);
        for (auto& room : rooms)
        {
            room = new Room();
            room->col->scale.x = 100.0f * RANDOM->Int(4, 12);
            room->col->scale.y = 100.0f * RANDOM->Int(4, 12);

            map<Int2, bool> dic;
            int xRand = 0, yRand = 0;
            do {
                xRand = RANDOM->Int(-10, 10);
                yRand = RANDOM->Int(-10, 10);
            } while (dic[Int2(xRand, yRand)]);

            dic[Int2(xRand, yRand)]++;

            room->col->SetWorldPosX(100.0f * xRand);
            room->col->SetWorldPosY(100.0f * yRand);
            room->col->isFilled = false;
            room->col->color = Color(1.0f, 0.6f, 0.6f);
            room->col->collider = Collider::rect;
        }
        roomScaleForSelect = 450'000.0f;
    }

    void ProcedureMapGeneration::Release()
    {
        for (auto& elem : rooms) elem->Release();
        rooms.clear();
        for (auto& elem : roomsSelected) elem->Release();
        roomsSelected.clear();
        roomNode.clear();
        triangulation.nodesLinked.clear();
        triangulation.edges.clear();
        triangulation.triangles.clear();
        triangulation.nodesForIndex.clear();
        visited.clear();
        linesTriangulated.clear();
        linesMST.clear();
        SafeDelete(tilemap);
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
        case GameState::spray:
        {
            Spray();
            if (TIMER->GetTick(timer, timeDefault))
            {
                state = GameState::spread;
            }
            break;
        }
        case GameState::spread:
        {
            Spread();
            if (flagSpread)
            {
                state = GameState::select;
            }
            break;
        }
        case GameState::select:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                Select();
                state = GameState::triangulate;
            }
            break;
        }
        case GameState::triangulate:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                Triangulate();
                state = GameState::span;
            }
            break;
        }
        case GameState::span:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                Spanning();
                state = GameState::loop;
            }
            break;
        }
        case GameState::loop:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                Loop();
                state = GameState::clean;
            }
            break;
        }
        case GameState::clean:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                Clean();
                state = GameState::roomTile;
            }
            break;
        }
        case GameState::roomTile:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                RoomTile();
                state = GameState::passageTile;
            }
            break;
        }
        case GameState::passageTile:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                PassageTile();
                state = GameState::passageWallTile;
            }
            break;
        }
        case GameState::passageWallTile:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                PassageWallTile();
                state = GameState::prop;
            }
            break;
        }
        case GameState::prop:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                Prop();
            }
            break;
        }
        default:
        {
            break;
        }//case
        }//switch

        SetTilemapGUI();

        for (auto& elem : rooms) if (elem) elem->Update();
        for (auto& elem : roomsSelected) if (elem) elem->Update();
        for (auto& elem : linesTriangulated) elem.Update();
        for (auto& elem : linesMST) elem.Update();

        tilemap->Update();
    }

    void ProcedureMapGeneration::LateUpdate()
    {
    }

    void ProcedureMapGeneration::Render()
    {
        for (auto& elem : rooms) if (elem) elem->Render();
        for (auto& elem : roomsSelected) if (elem) elem->Render();
        for (auto& elem : linesTriangulated) elem.Render();
        for (auto& elem : linesMST) elem.Render();

        tilemap->Render();
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
        
        for (auto& room : rooms)
        {
            for (auto& room2 : rooms)
            {
                if (room == room2) continue;

                if (room->col->Intersect(room2->col))
                {
                    Vector2 dir = room->col->GetWorldPos() - room2->col->GetWorldPos();
                    
                    float x, y;
                    if (dir.x >= 0.0f) x = tilemap->scale.x / 2.0f;
                    else x = tilemap->scale.x * -1.0f / 2.0f;
                    if (dir.y >= 0.0f) y = tilemap->scale.y / 2.0f;
                    else y = tilemap->scale.y * -1.0f / 2.0f;

                    room->SetPos(Vector2(room->Pos().x + x, room->Pos().y + y));
                    flagSpread = false;
                }
            }
            room->Update();
        }
    }

    void ProcedureMapGeneration::Select()
    {
        for (auto& elem : rooms)
        {
            if (elem->col->scale.x * elem->col->scale.y > roomScaleForSelect)
            {
                elem->col->scale.x -= 200.0f;
                elem->col->scale.y -= 200.0f;
                Int2 on;
                if (tilemap->WorldPosToTileIdx(elem->Pos(), on))
                {
                    elem->SetPos(tilemap->TileIdxToWorldPos(on));
                }
                elem->col->isFilled = true;
                elem->selected = true;
                roomsSelected.push_back(elem);
            }
        }
    }

    void ProcedureMapGeneration::Triangulate()
    {
        int idx = 0;
        for (auto& elem : roomsSelected)
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
            elem.collider = Collider::line;
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
            curLine.v.index = triangulation.nodesForIndex[curLine.v];
            curLine.w.index = triangulation.nodesForIndex[curLine.w];

            edgePq.pop();

            if (visited[curLine.v.index] && visited[curLine.w.index]) continue;
            visited[curLine.v.index] = true;
            visited[curLine.w.index] = true;

            curLine.color = Color(0.5f, 1.0f, 0.5f);
            linesMST.push_back(curLine);

            auto push = [&](ObNode& node)
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
            push(curLine.v);
            push(curLine.w);
        }
    }

    void ProcedureMapGeneration::Loop()
    {
        int count = linesTriangulated.size() / 20;

        while (count--)
        {
            float rand = RANDOM->Int(0, linesTriangulated.size() - 1);
            bool flag = false;
            for (auto& elem : linesMST)
            {
                if ((elem.v == linesTriangulated[rand].v && elem.w == linesTriangulated[rand].w) ||
                    (elem.v == linesTriangulated[rand].w && elem.w == linesTriangulated[rand].v))
                {
                    count++;
                    flag = true;
                    break;
                }
            }
            if (false == flag)
            {
                linesTriangulated[rand].color = Color(0.5f, 0.5f, 1.0f);
                linesMST.push_back(linesTriangulated[rand]);
            }
        }

        linesTriangulated.clear();
    }

    void ProcedureMapGeneration::Clean()
    {
        for (auto& elem : rooms)
        {
            if (false == elem->selected)
            {
                elem = nullptr;
            }
        }
        rooms.clear();
    }

    void ProcedureMapGeneration::RoomTile()
    {
        float tileScale = tilemap->scale.x;

        Vector2 start;
        Vector2 end;
        Int2 sour;
        Int2 dest;

        auto SetTile2 = [&](Int2 on, int roomIdx)
        {
            tilemap->SetTile(on,
                Int2(RANDOM->Int(1, 4),
                    RANDOM->Int(1, 3)),
                imgIdx,
                (int)TileState::floor,
                Color(0.5f, 0.5f, 0.5f, 1.0f),
                roomIdx);
        };

        auto SetWall2 = [&](Int2 on, int roomIdx, Int2 frameIdx)
        {
            tilemap->SetTile(on,
                frameIdx,
                imgIdx,
                (int)TileState::wall);
        };

        auto SetTile1 = [&](Room* elem, int roomIdx)
        {
            ObRect* r = dynamic_cast<ObRect*>(elem->col);

            start.x = r->lb().x;
            start.y = r->lb().y;
            end.x = r->rt().x;
            end.y = r->rt().y;

            tilemap->WorldPosToTileIdx(start, sour);
            tilemap->WorldPosToTileIdx(end, dest);


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

        int idx = 0;
        for (auto& elem : roomsSelected)
        {
            SetTile1(elem, idx);
            idx++;
        }
    }

    void ProcedureMapGeneration::PassageTile()
    {
        // room index와 node index 연결정보
        for (auto& elem : linesMST)
        {
            for (int roomIndex = 0; roomIndex < roomsSelected.size(); roomIndex++)
            {
                Vector2 v = Vector2(elem.v.x, elem.v.y);
                if (almostEqualVector2(v, roomsSelected[roomIndex]->Pos()))
                {
                    nodesForRoomIndex[v] = roomIndex;
                }

                Vector2 w = Vector2(elem.w.x, elem.w.y);
                if (almostEqualVector2(w, roomsSelected[roomIndex]->Pos()))
                {
                    nodesForRoomIndex[w] = roomIndex;
                }
            }
        }

        // 1. 8방향 체크해 문의 방향을 정하고, 2. 좌우문 뒤집을지, 3. 모서리에 위치할 시 예외처리
        auto SetDoor = [&](Int2 on, Int2 dest)
        {
            deque<bool> dirWall(8);

            for (int i = 0; i < 8; i++)
            {
                int nx = on.x + dx[i];
                int ny = on.y + dy[i];

                if (tilemap->GetTileState(Int2(nx, ny)) == TileState::wall)
                {
                    dirWall[i] = true;
                }
            }

            Int2 doorFrameIdx = Int2(9, 0);
            Int2 doorTileIdx = on;
            Int2 floorTileIdx;

            // 가로, 세로
            if (dirWall[DirState::dirB] && dirWall[DirState::dirT])
            {
                if (dest.x < on.x)
                {
                    doorFrameIdx = Int2(7, 0);
                }
                else
                {
                    doorFrameIdx = Int2(6, 0);
                }
            }
            else if (dirWall[DirState::dirL] && dirWall[DirState::dirR])
            {
                doorFrameIdx = Int2(8, 0);
            }
            // 모서리에 위치 시 대각선. 그리고 이동 가능하게 옆에 평면타일로 예외처리
            else
            {
                if ((dirWall[DirState::dirL] && dirWall[DirState::dirB]))
                {
                    floorTileIdx.x = on.x;
                    floorTileIdx.y = on.y;
                    doorTileIdx.x = on.x + dx[DirState::dirL];
                    doorTileIdx.y = on.y + dy[DirState::dirL];
                    doorFrameIdx = Int2(9, 0);
                }
                else if ((dirWall[DirState::dirB] && dirWall[DirState::dirR]))
                {
                    floorTileIdx.x = on.x;
                    floorTileIdx.y = on.y;
                    doorTileIdx.x = on.x + dx[DirState::dirR];
                    doorTileIdx.y = on.y + dy[DirState::dirR];
                    doorFrameIdx = Int2(9, 0);
                }

                else if ((dirWall[DirState::dirR] && dirWall[DirState::dirT]))
                {
                    floorTileIdx.x = on.x;
                    floorTileIdx.y = on.y;
                    doorTileIdx.x = on.x + dx[DirState::dirR];
                    doorTileIdx.y = on.y + dy[DirState::dirR];
                    doorFrameIdx = Int2(9, 0);
                }
                else if (dirWall[DirState::dirT] && dirWall[DirState::dirL])
                {
                    floorTileIdx.x = on.x;
                    floorTileIdx.y = on.y;
                    doorTileIdx.x = on.x + dx[DirState::dirL];
                    doorTileIdx.y = on.y + dy[DirState::dirL];
                    doorFrameIdx = Int2(9, 0);
                }

                tilemap->SetTile(floorTileIdx,
                    Int2(RANDOM->Int(1, 4),
                        RANDOM->Int(1, 3)),
                    imgIdx,
                    (int)TileState::floor);
            }

            tilemap->SetTile(doorTileIdx,
                doorFrameIdx,
                imgIdx,
                (int)TileState::door);
        };

        // 복도 A* - 위치벡터 간 중점에서 각 방으로 연결
        auto AStar = [&](Vector2 start, Vector2 end)
        {
            Int2 sour, dest;
            tilemap->WorldPosToTileIdx(start, sour);
            tilemap->WorldPosToTileIdx(end, dest);

            if (tilemap->PathFinding(sour, dest, way, false))
            {
                tilemap->SetTile(way.back()->idx,
                    Int2(RANDOM->Int(1, 4),
                        RANDOM->Int(1, 3)),
                    imgIdx,
                    (int)TileState::floor);

                while (false == way.empty())
                {
                    TileState res = tilemap->GetTileState(way.back()->idx);

                    if (res == TileState::none)
                    {
                        tilemap->SetTile(way.back()->idx,
                            Int2(RANDOM->Int(1, 4),
                                RANDOM->Int(1, 3)),
                            imgIdx,
                            (int)TileState::floor);
                    }
                    else if (res == TileState::wall)
                    {
                        SetDoor(way.back()->idx, dest);

                        way.clear();
                        break;
                    }

                    way.pop_back();
                }
            }
        };

        // 본 함수
        for (auto& elem : linesMST)
        {
            const ObNode& v = elem.v;
            const ObNode& w = elem.w;

            ObNode mid = ObNode((w.x + v.x) / 2.0f, (w.y + v.y) / 2.0f);

            Vector2 vScaleHalf = roomsSelected[nodesForRoomIndex[v]]->col->scale / 2.0f;
            Vector2 wScaleHalf = roomsSelected[nodesForRoomIndex[w]]->col->scale / 2.0f;

            Vector2	start, end;
            
            start = Vector2(mid.x, mid.y);
            Vector2 end1 = Vector2(v.x, v.y);
            Vector2 end2 = Vector2(w.x, w.y);

            AStar(start, end1);
            AStar(start, end2);
        }

        linesMST.clear();

        // 다음 wall이 tilestate를 판단하기 때문에 한 번 갱신!!
        tilemap->CreateTileCost();
    }

    void ProcedureMapGeneration::PassageWallTile()
    {
        for (int x = 0; x < tileSize.y; x++)
        {
            for (int y = 0; y < tileSize.x; y++)
            {
                if (tilemap->Tiles[x][y].roomIndex == -1 &&
                    tilemap->Tiles[x][y].state == TileState::floor)
                {
                    for (int i = 0; i < 8; i++)
                    {
                        int nx = x + dx[i];
                        int ny = y + dy[i];
                        if (nx < 0 || nx >= tileSize.x || ny < 0 || ny >= tileSize.y) continue;

                        if (tilemap->Tiles[nx][ny].state == TileState::none)
                        {
                            tilemap->SetTile(Int2(nx, ny), Int2(8, 7), imgIdx, (int)TileState::wall);
                        }
                    }
                }
            }
        }

        tilemap->CreateTileCost();
    }

    void ProcedureMapGeneration::Prop()
    {

    }

    void ProcedureMapGeneration::SetTilemapGUI()
    {
        if (false == useGui) return;

        
        // Gui
        if (ImGui::Button("ErrorFileSystem?->Click me"))
        {
            ImGuiFileDialog::Instance()->Close();
        }

        // TileScale
        ImGui::SliderFloat2("Scale", (float*)&tilemap->scale, 0.0f, 100.0f);

        //TileSize
        if (ImGui::SliderInt2("TileSize", (int*)&tileSize, 1, 100))
        {
            tilemap->ResizeTile(tileSize);
        }

        //TilePos
        Vector2 pos = tilemap->GetWorldPos();
        if (ImGui::SliderFloat2("TilePos", (float*)&pos, -4000.0f, 4000.0f))
        {
            tilemap->SetWorldPos(pos);
        }

        //TileState
        ImGui::SliderInt("TileState", &tileState, int(TileState::none), int(TileState::tileSize));

        //TileColor
        ImGui::ColorEdit4("TileColor", (float*)&tileColor, ImGuiColorEditFlags_PickerHueWheel);

        //Texture
        for (int i = 0; i < imageCount; i++)
        {
            string str = "Texture" + to_string(i);
            if (GUI->FileImGui(str.c_str(), str.c_str(),
                ".jpg,.png,.bmp,.dds,.tga", "../Contents/Images/EnterTheGungeon"))
            {
                string path = ImGuiFileDialog::Instance()->GetCurrentFileName();
                SafeDelete(tilemap->tileImages[i]);
                wstring wImgFile = L"";
                wImgFile.assign(path.begin(), path.end());
                tilemap->tileImages[i] = new ObImage(wImgFile);
            }
            if (i < 3)
            {
                ImGui::SameLine();
            }
        }

        //Coord
        ImGui::Text("cam pos : %f , %f", CAM->position.x, CAM->position.y);

        ImGui::Text("mouse pos : %f , %f", INPUT->GetWorldMousePos().x, INPUT->GetWorldMousePos().y);

        tilemap->WorldPosToTileIdx(INPUT->GetWorldMousePos(), mouseIdx);
        ImGui::Text("mouseIdx : %d , %d", mouseIdx.x, mouseIdx.y);

        ImGui::Text("mouseOverTileState : %d", tilemap->Tiles[mouseIdx.x][mouseIdx.y].state);

        ImGui::Text("mouseOverRoomIndex : %d", tilemap->Tiles[mouseIdx.x][mouseIdx.y].roomIndex);

        //ImageButton
        tilemap->RenderGui(pickingIdx, imgIdx);
        ImGui::Text("pickingIdx : %d , %d", pickingIdx.x, pickingIdx.y);
        ImGui::Text("imgIdx : %d", imgIdx);

        //maxFrame
        ImGui::InputInt2("maxFrame", (int*)&tilemap->tileImages[imgIdx]->maxFrame);

        //SaveLoad
        if (GUI->FileImGui("Save", "Save Map",
            ".txt", "../Contents/TileMap"))
        {
            string path = ImGuiFileDialog::Instance()->GetCurrentFileName();
            tilemap->file = path;
            tilemap->Save();
        }
        ImGui::SameLine();
        if (GUI->FileImGui("Load", "Load Map",
            ".txt", "../Contents/TileMap"))
        {
            string path = ImGuiFileDialog::Instance()->GetCurrentFileName();
            tilemap->file = path;
            tilemap->Load();
            tileSize = tilemap->GetTileSize();
        }

        //Brush
        ImVec2 min = ImGui::GetWindowPos();
        ImVec2 max;
        max.x = min.x + ImGui::GetWindowSize().x;
        max.y = min.y + ImGui::GetWindowSize().y;

        if (!ImGui::IsMouseHoveringRect(min, max))
        {
            if (INPUT->KeyPress(VK_LBUTTON))
            {
                Vector2 a = INPUT->GetWorldMousePos();
                if (tilemap->WorldPosToTileIdx(INPUT->GetWorldMousePos(), mouseIdx))
                {
                    tilemap->SetTile(mouseIdx, pickingIdx, imgIdx, tileState, tileColor);
                }
            }
        }
        
    }

    bool ProcedureMapGeneration::IntersectTileUnit(Character* elem)
    {
        auto GetTileState = [&](Vector2 wpos) ->bool
        {
            Int2 on;
            if (tilemap->WorldPosToTileIdx(wpos, on))
            {
                return tilemap->GetTileState(on) == TileState::wall;
            }
            return false;
        };

        Vector2 pos;
        bool flag = false;

        pos = elem->colTile->lt();
        flag |= GetTileState(pos);
        pos = elem->colTile->lb();
        flag |= GetTileState(pos);
        pos = elem->colTile->rt();
        flag |= GetTileState(pos);
        pos = elem->colTile->rb();
        flag |= GetTileState(pos);

        return flag;
    }

    bool ProcedureMapGeneration::IntersectTilePos(Vector2 wpos)
    {
        Int2 on;
        if (tilemap->WorldPosToTileIdx(wpos, on))
        {
            return tilemap->GetTileState(on) == TileState::wall;
        }
        return false;
    }
}