#include "stdafx.h"

namespace Gungeon
{
    ProcedureMapGeneration::ProcedureMapGeneration()
    {
        Init();
    }

    void ProcedureMapGeneration::Init()
    {
        state = GameState::spray;

        LIGHT->light.radius = 3000.0f;

        flagSpread = false;

        timer = 0.0f;

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
            room->col->scale.x = 100.0f * RANDOM->Int(2, 10);
            room->col->scale.y = 100.0f * RANDOM->Int(2, 10);

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
        roomScaleForSelect = 300'000.0f;
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
        passagesLine.clear();
        passages.clear();
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
                state = GameState::dig;
            }
            break;
        }
        case GameState::dig:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                Dig();
                state = GameState::widen;
            }
            break;
        }
        case GameState::widen:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                Widen();
                state = GameState::tile;
            }
            break;
        }
        case GameState::tile:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                Tile();
                state = GameState::set;
            }
            break;
        }
        case GameState::set:
        {
            if (TIMER->GetTick(timer, timeDefault))
            {
                Set();
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
        for (auto& elem : passagesLine) elem.Update();
        for (auto& elem : passages) elem->Update();

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
        for (auto& elem : passagesLine) elem.Render();
        for (auto& elem : passages) elem->Render();

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
                elem->col->scale.x -= 100.0f;
                elem->col->scale.y -= 100.0f;
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

        int idx = 0;
        for (auto& elem : roomsSelected)
        {
            nodes.push_back(ObNode(idx, elem->col->GetWorldPos()));
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
        int count = 3;

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

    void ProcedureMapGeneration::Dig()
    {
        for (auto& elem : linesMST)
        {
            const ObNode& v = elem.v;
            const ObNode& w = elem.w;

            ObLine l1(ObNode(v.x, v.y), ObNode(w.x, v.y));
            ObLine l2(ObNode(w.x, w.y), ObNode(w.x, v.y));
            l1.color = l2.color = Color(1.0f, 0.8f, 0.6f);

            passagesLine.push_back(l1);
            passagesLine.push_back(l2);
        }

        linesMST.clear();
    }

    void ProcedureMapGeneration::Widen()
    {
        for (auto& elem : passagesLine)
        {
            float scale = 100.0f;
            const ObNode& v = elem.v;
            const ObNode& w = elem.w;

            Room* room = new Room;
            room->col = new ObRect;
            // 수평
            if (almostEqualFloat(v.x, w.x))
            {
                int coef = static_cast<int>(abs(v.y - w.y)) % static_cast<int>(scale);
                room->col->scale.x = scale;
                room->col->scale.y = abs(v.y - w.y) - static_cast<float>(coef);
                room->col->SetWorldPosX(v.x);
                room->col->SetWorldPosY((v.y + w.y) / 2.0f);
            }
            // 수직
            else if (almostEqualFloat(v.y, w.y))
            {
                int coef = static_cast<int>(abs(v.x - w.x)) % static_cast<int>(scale);
                room->col->scale.x = abs(v.x - w.x) - static_cast<float>(coef);
                room->col->scale.y = scale;
                room->col->SetWorldPosX((v.x + w.x) / 2.0f);
                room->col->SetWorldPosY(v.y);
            }
            room->col->color = Color(1.0f, 0.8f, 0.6f);
            passages.push_back(room);
        }
    }

    void ProcedureMapGeneration::Tile()
    {
        float tileScale = tilemap->scale.x;
        int startY = 0;
        int endY = 0;
        int startX = 0;
        int endX = 0;

        auto SetWall2 = [&](Vector2 coord)
        {
            Int2 pos;
            if (tilemap->WorldPosToTileIdx(coord, pos))
            {
                tilemap->SetTile(pos, 
                    Int2(RANDOM->Int(1, 4), 0),
                    imgIdx, 
                    (int)TileState::wall);
            }
        };

        auto SetWall1 = [&](Room* elem)
        {
            ObRect* r = dynamic_cast<ObRect*>(elem->col);

            startX = r->lt().x - tileScale;
            endX   = r->rt().x + tileScale;
            startY = r->lt().y - tileScale;
            endY   = r->lt().y + tileScale;
            for (int x = startX; x <= endX; x += tileScale)
            {
                SetWall2(Vector2(x, endY));
            }

            startX = r->lb().x - tileScale;
            endX   = r->rb().x + tileScale;
            startY = r->lb().y - tileScale;
            endY   = r->rb().y + tileScale;
            for (int x = startX; x <= endX; x += tileScale)
            {
                SetWall2(Vector2(x, startY));
            }

            startX = r->lt().x - tileScale;
            endX   = r->lt().x + tileScale;
            startY = r->lb().y - tileScale;
            endY   = r->lt().y + tileScale;
            for (int y = startY; y <= endY; y += tileScale)
            {
                SetWall2(Vector2(startX, y));
            }

            startX = r->rb().x - tileScale;
            endX   = r->rt().x + tileScale;
            startY = r->rb().y - tileScale;
            endY   = r->rt().y + tileScale;
            for (int y = startY; y <= endY; y += tileScale)
            {
                SetWall2(Vector2(endX, y));
            }
        };

        // 복도 벽
        for (auto& elem : passages)
        {
            SetWall1(elem);
        }
        // 방 벽
        for (auto& elem : roomsSelected)
        {
            SetWall1(elem);
        }


        auto SetTile2 = [&](Vector2 coord)
        {
            Int2 pos;
            if (tilemap->WorldPosToTileIdx(coord, pos))
            {
                tilemap->SetTile(pos, 
                    Int2(RANDOM->Int(1, 4), 
                        RANDOM->Int(1, 3)), 
                    imgIdx, 
                    (int)TileState::none);
            }
        };

        auto SetTile1 = [&](Room* elem)
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
                    SetTile2(Vector2(x, y));
                }
            }
        };

        // 복도 타일
        for (auto& elem : passages)
        {
            SetTile1(elem);
        }
        // 방 타일
        for (auto& elem : roomsSelected)
        {
            SetTile1(elem);
        }

        tilemap->CreateTileCost();
    }

    void ProcedureMapGeneration::Set()
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
        if (ImGui::SliderInt2("TileSize", (int*)&tileSize, 1, 400))
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
        tilemap->WorldPosToTileIdx(INPUT->GetWorldMousePosForZoom(), mouseIdx);
        ImGui::Text("mouseIdx : %d , %d", mouseIdx.x, mouseIdx.y);

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
                Vector2 a = INPUT->GetWorldMousePosForZoom();
                if (tilemap->WorldPosToTileIdx(INPUT->GetWorldMousePosForZoom(), mouseIdx))
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
                return tilemap->GetTileState(on) != TileState::none;
            }
            return false;
        };

        Vector2 pos;
        bool flag = false;

        pos = elem->foot->lt();
        flag |= GetTileState(pos);
        pos = elem->foot->lb();
        flag |= GetTileState(pos);
        pos = elem->foot->rt();
        flag |= GetTileState(pos);
        pos = elem->foot->rb();
        flag |= GetTileState(pos);

        return flag;
    }

    bool ProcedureMapGeneration::IntersectTilePos(Vector2 wpos)
    {
        Int2 on;
        if (tilemap->WorldPosToTileIdx(wpos, on))
        {
            return tilemap->GetTileState(on) != TileState::none;
        }
        return false;
    }
}