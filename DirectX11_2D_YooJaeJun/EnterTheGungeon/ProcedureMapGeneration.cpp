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
        nodes.clear();
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
                state = GameState::tileRoomIndex;
            }
            break;
        }
        case GameState::tileRoomIndex:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                TileRoomIndex();
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
                state = GameState::floor;
            }
            break;
        }
        case GameState::floor:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                Floor();
                state = GameState::passage;
            }
            break;
        }
        case GameState::passage:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                Passage();
                state = GameState::tilePassageIndex;
            }
            break;
        }
        case GameState::tilePassageIndex:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                TilePassageIndex();
                state = GameState::wall;
            }
            break;
        }
        case GameState::wall:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                Wall();
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

    void ProcedureMapGeneration::TileRoomIndex()
    {
        int idx = 0;
        for (auto& elem : roomsSelected)
        {
            // 들로네 삼각분할 위한 노드
            nodes.push_back(ObNode(idx, elem->Pos()));
            idx++;
        }
    }

    void ProcedureMapGeneration::Triangulate()
    {
        triangulation.triangulate(nodes);
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

    void ProcedureMapGeneration::Floor()
    {
        float tileScale = tilemap->scale.x;
        int startY = 0;
        int endY = 0;
        int startX = 0;
        int endX = 0;

        auto SetTile2 = [&](Vector2 coord, int idx)
        {
            Int2 on;
            if (tilemap->WorldPosToTileIdx(coord, on))
            {
                tilemap->SetTile(on,
                    Int2(RANDOM->Int(1, 4),
                        RANDOM->Int(1, 3)),
                    imgIdx,
                    (int)TileState::floor,
                    Color(0.5f, 0.5f, 0.5f, 1.0f),
                    idx);
            }
        };

        auto SetTile1 = [&](Room* elem, int idx)
        {
            ObRect* r = dynamic_cast<ObRect*>(elem->col);

            startX = r->lb().x;
            endX = r->rt().x;
            startY = r->lb().y;
            endY = r->rt().y;
            for (int y = startY; y <= endY; y += tilemap->scale.y)
            {
                for (int x = startX; x <= endX; x += tilemap->scale.x)
                {
                    SetTile2(Vector2(x, y), idx);
                }
            }
        };

        // 방 타일
        int idx = 0;
        for (auto& elem : roomsSelected)
        {
            SetTile1(elem, idx);
            idx++;
        }
    }

    void ProcedureMapGeneration::Passage()
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
        
        for (auto& elem : linesMST)
        {
            // A*
            auto AStar = [&](Vector2 start, Vector2 end)
            {
                Int2 sour, dest;
                tilemap->WorldPosToTileIdx(start, sour);
                tilemap->WorldPosToTileIdx(end, dest);

                if (tilemap->PathFinding(sour, dest, way, false))
                {
                    Int2 door;

                    bool flag = false;

                    while (false == way.empty())
                    {
                        tilemap->SetTile(way.back()->idx, Int2(RANDOM->Float(1, 4), 1), imgIdx, (int)TileState::floor);
                        Tile* temp = way.back();
                        way.pop_back();

                        if (way.size() > 0)
                        {
                            if (tilemap->GetTileState(way.back()->idx) == TileState::none)
                            {
                                flag = true;
                            }

                            if (flag &&
                                tilemap->GetTileState(way.back()->idx) == TileState::floor)
                            {
                                door = temp->idx;
                                way.clear();
                                break;
                            }
                        }
                    }

                    if (door != Int2(0, 0)) tilemap->SetTile(door, Int2(6, 3), imgIdx, (int)TileState::door);
                }
            };


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

    void ProcedureMapGeneration::TilePassageIndex()
    {
    }

    void ProcedureMapGeneration::Wall()
    {
        // L R T B LB LT RB RT
        int dx[8] = { -1,1,0,0,-1,-1,1,1 };
        int dy[8] = { 0,0,1,-1,-1,1,-1,1 };

        // Int2 wallImgOn[8] = { {0, 1}, {5, 1}, {1, 0}, {1, 5}, {0, 5}, {0, 0}, {5, 5}, {5, 0} };

        for (int x = 0; x < tileSize.y; x++)
        {
            for (int y = 0; y < tileSize.x; y++)
            {
                if (tilemap->Tiles[x][y].state == TileState::floor)
                {
                    for (int i = 0; i < 8; i++)
                    {
                        int nx = x + dx[i];
                        int ny = y + dy[i];
                        if (nx < 0 || nx >= tileSize.x || ny < 0 || ny >= tileSize.y) continue;

                        if (tilemap->Tiles[nx][ny].state == TileState::none)
                        {
                            tilemap->SetTile(Int2(nx, ny), Int2(1, 0), imgIdx, (int)TileState::wall);
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