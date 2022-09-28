#include "stdafx.h"

ProcedureMapGeneration::ProcedureMapGeneration()
{
    Init();
}

void ProcedureMapGeneration::Init()
{
    flagSpread = false;

    timer = 0.0f;

    rooms = vector<Room*>(roomMax);
    for (auto& room : rooms)
    {
        room = new Room();
        room->col->scale.x = RANDOM->Float(300.0f, 1200.0f);
        room->col->scale.y = RANDOM->Float(300.0f, 1200.0f);
        room->col->SetWorldPosX(RANDOM->Float(-200.0f, 200.0f));
        room->col->SetWorldPosY(RANDOM->Float(-200.0f, 200.0f));
        room->col->isFilled = false;
        room->col->color = Color(1.0f, 0.6f, 0.6f);
        room->col->collider = Collider::rect;
    }
    roomScaleForSelect = 500'000.0f;

    map = new ObTileMap();
    map->scale = Vector2(50.0f, 50.0f);
    map->SetWorldPosX(-app.GetHalfWidth() - 5000.0f);
    map->SetWorldPosY(-app.GetHalfHeight() - 5000.0f);
    LIGHT->light.radius = 3000.0f;
    imgIdx = 0;
    tileSize = Int2(350, 350);
    map->ResizeTile(tileSize);
    tileColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
    tileState = 0;

    state = GameState::spray;
}

void ProcedureMapGeneration::Release()
{
    for (auto& elem : rooms) SafeDelete(elem);
    for (auto& elem : roomsSelected) SafeDelete(elem);
    rooms.clear();
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
    for (auto& elem : tileImgs) SafeDelete(elem);
    for (auto& elem : wallImgs) SafeDelete(elem);
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
        if (TIMER->GetTick(timer, 1.0f))
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
        if (TIMER->GetTick(timer, 1.0f))
        {
            Select();
            state = GameState::triangulate;
        }
        break;
    }
    case GameState::triangulate:
    {
        if (TIMER->GetTick(timer, 1.0f))
        {
            Triangulate();
            state = GameState::span;
        }
        break;
    }
    case GameState::span:
    {
        if (TIMER->GetTick(timer, 1.0f))
        {
            Spanning();
            state = GameState::loop;
        }
        break;
    }
    case GameState::loop:
    {
        if (TIMER->GetTick(timer, 1.0f))
        {
            Loop();
            state = GameState::dig;
        }
        break;
    }
    case GameState::dig:
    {
        if (TIMER->GetTick(timer, 1.0f))
        {
            Dig();
            state = GameState::widen;
        }
        break;
    }
    case GameState::widen:
    {
        if (TIMER->GetTick(timer, 1.0f))
        {
            Widen();
            state = GameState::clean;
        }
        break;
    }
    case GameState::clean:
    {
        if (TIMER->GetTick(timer, 1.0f))
        {
            Clean();
            state = GameState::tile;
        }
        break;
    }
    case GameState::tile:
    {
        Tile();
        // state = GameState::set;
        break;
    }
    case GameState::set:
    {
        if (TIMER->GetTick(timer, 1.0f))
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

    for (auto& elem : rooms) if (elem) elem->Update();
    for (auto& elem : roomsSelected) if (elem) elem->Update();
    for (auto& elem : linesTriangulated) elem.Update();
    for (auto& elem : linesMST) elem.Update();
    for (auto& elem : passagesLine) elem.Update();
    for (auto& elem : passages) elem.Update();
    for (auto& elem : tileImgs) if (elem) elem->Update();
    for (auto& elem : wallImgs) if (elem) elem->Update();
}

void ProcedureMapGeneration::LateUpdate()
{
}

void ProcedureMapGeneration::Render()
{
    for (auto& elem : passagesLine) elem.Render();
    for (auto& elem : passages) elem.Render();
    for (auto& elem : rooms) if (elem) elem->Render();
    for (auto& elem : roomsSelected) if (elem) elem->Render();
    for (auto& elem : linesTriangulated) elem.Render();
    for (auto& elem : linesMST) elem.Render();
    for (auto& elem : wallImgs) if (elem) elem->Render();
    for (auto& elem : tileImgs) if (elem) elem->Render();
}

void ProcedureMapGeneration::ResizeScreen()
{
}

void ProcedureMapGeneration::Spray()
{
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
                Vector2 velocity = room->col->GetWorldPos() - room2->col->GetWorldPos();
                room->col->MoveWorldPos(velocity * DELTA);
                flagSpread = false;
            }
        }
    }
}

void ProcedureMapGeneration::Select()
{
    for (auto& elem : rooms)
    {
        if (elem->col->scale.x * elem->col->scale.y > roomScaleForSelect)
        {
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

void ProcedureMapGeneration::Dig()
{
    for (auto& elem : linesMST)
    {
        {
            ObLine l(ObNode(elem.v.x, elem.v.y), ObNode(elem.w.x, elem.v.y));
            l.color = Color(1.0f, 0.0f, 1.0f);
            passagesLine.push_back(l);
        }
        {
            ObLine l(ObNode(elem.w.x, elem.w.y), ObNode(elem.w.x, elem.v.y));
            l.color = Color(1.0f, 0.0f, 1.0f);
            passagesLine.push_back(l);
        }
    }

    linesMST.clear();
}

void ProcedureMapGeneration::Widen()
{
    for (auto& elem : passagesLine)
    {
        float scale = 200.0f;
        ObRect r;
        if (almostEqualFloat(elem.v.x, elem.w.x))
        {
            r.scale.x = scale;
            r.scale.y = abs(elem.v.y - elem.w.y);
            r.SetWorldPosX(elem.v.x);
            r.SetWorldPosY((elem.v.y + elem.w.y) / 2.0f);
        }
        else if (almostEqualFloat(elem.v.y, elem.w.y))
        {
            r.scale.x = abs(elem.v.x - elem.w.x);
            r.scale.y = scale;
            r.SetWorldPosX((elem.v.x + elem.w.x) / 2.0f);
            r.SetWorldPosY(elem.v.y);
        }
        r.color = Color(1.0f, 0.8f, 0.6f);

        passages.push_back(r);
    }
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

void ProcedureMapGeneration::Tile()
{
    /*
    //Gui
    if (ImGui::Button("ErrorFileSystem?->Click me"))
    {
        ImGuiFileDialog::Instance()->Close();
    }

    //TileScale
    ImGui::SliderFloat2("Scale", (float*)&map->scale, 0.0f, 100.0f);

    //TileSize
    if (ImGui::SliderInt2("TileSize", (int*)&tileSize, 1, 400))
    {
        map->ResizeTile(tileSize);
    }

    //TilePos
    Vector2 pos = map->GetWorldPos();
    if (ImGui::SliderFloat2("TilePos", (float*)&pos, -4000.0f, 4000.0f))
    {
        map->SetWorldPos(pos);
    }

    //TileState
    ImGui::SliderInt("TileState", &tileState, int(TileState::none), int(TileState::tileSize));

    //TileColor
    ImGui::ColorEdit4("TileColor", (float*)&tileColor, ImGuiColorEditFlags_PickerHueWheel);

    //Texture
    for (int i = 0; i < 4; i++)
    {
        string str = "Texture" + to_string(i);
        if (GUI->FileImGui(str.c_str(), str.c_str(),
            ".jpg,.png,.bmp,.dds,.tga", "../Contents/Images/EnterTheGungeon"))
        {
            string path = ImGuiFileDialog::Instance()->GetCurrentFileName();
            SafeDelete(map->tileImages[i]);
            wstring wImgFile = L"";
            wImgFile.assign(path.begin(), path.end());
            map->tileImages[i] = new ObImage(wImgFile);
        }
        if (i < 3)
        {
            ImGui::SameLine();
        }
    }

    //Coord
    map->WorldPosToTileIdx(INPUT->GetWorldMousePos(), mouseIdx);
    ImGui::Text("mouseIdx : %d , %d", mouseIdx.x, mouseIdx.y);

    //ImageButton
    map->RenderGui(pickingIdx, imgIdx);
    ImGui::Text("pickingIdx : %d , %d", pickingIdx.x, pickingIdx.y);
    ImGui::Text("imgIdx : %d", imgIdx);

    //maxFrame
    ImGui::InputInt2("maxFrame", (int*)&map->tileImages[imgIdx]->maxFrame);

    //SaveLoad
    if (GUI->FileImGui("Save", "Save Map",
        ".txt", "../Contents/TileMap"))
    {
        string path = ImGuiFileDialog::Instance()->GetCurrentFileName();
        map->file = path;
        map->Save();
    }
    ImGui::SameLine();
    if (GUI->FileImGui("Load", "Load Map",
        ".txt", "../Contents/TileMap"))
    {
        string path = ImGuiFileDialog::Instance()->GetCurrentFileName();
        map->file = path;
        map->Load();
        tileSize = map->GetTileSize();
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
            if (map->WorldPosToTileIdx(INPUT->GetWorldMousePosForZoom(), mouseIdx))
            {
                map->SetTile(mouseIdx, pickingIdx, imgIdx, tileState, tileColor);
            }
        }
    }

    map->Update();
    //*/
    /*
    tileImgs.resize(passages.size() + roomsSelected.size());

    for (auto& elem : tileImgs)
    {
        elem = new ObImage(L"EnterTheGungeon/Level/Tile.png");
    }

    int tileIdx = 0;
    int wallIdx = 0;
    int startY = 0;
    int endY = 0;
    int startX = 0;
    int endX = 0;

    float wallScale = 50.0f;

    auto PushWall = [&](const float x, const float y)
    {
        ObImage* wallImg = new ObImage(L"EnterTheGungeon/Level/Wall.png");
        wallImg->scale = Vector2(wallScale, wallScale);
        wallImg->SetWorldPos(Vector2(x, y));
        wallImgs.push_back(wallImg);
    };

    auto SetWall = [&](ObRect& elem)
    {
        startX = elem.lt().x;
        endX = elem.rt().x;
        startY = elem.lt().y;
        endY = elem.lt().y;
        for (int x = startX; x <= endX; x += wallScale)
        {
            PushWall(x, startY);
            wallImgs.back()->pivot = OFFSET_LB;
        }
        startX = elem.lb().x;
        endX = elem.rb().x;
        startY = elem.lb().y;
        endY = elem.rb().y;
        for (int x = startX; x <= endX; x += wallScale)
        {
            PushWall(x, startY);
            wallImgs.back()->pivot = OFFSET_LT;
        }
        startX = elem.lt().x;
        endX = elem.lt().x;
        startY = elem.lb().y;
        endY = elem.lt().y;
        for (int y = startY; y <= endY; y += wallScale)
        {
            PushWall(startX, y);
            wallImgs.back()->pivot = OFFSET_RB;
        }
        startX = elem.rt().x;
        endX = elem.rt().x;
        startY = elem.rb().y;
        endY = elem.rt().y;
        for (int y = startY; y <= endY; y += wallScale)
        {
            PushWall(startX, y);
            wallImgs.back()->pivot = OFFSET_LT;
        }
    };
    

    for (auto& elem : passages)
    {
        tileImgs[tileIdx]->SetWorldPos(elem.GetWorldPos());
        tileImgs[tileIdx]->scale = Vector2(elem.scale.x, elem.scale.y);
        tileIdx++;

        SetWall(elem);
    }

    for (auto& elem : roomsSelected)
    {
        tileImgs[tileIdx]->SetWorldPos(elem->col->GetWorldPos());
        tileImgs[tileIdx]->scale = elem->col->scale;
        tileIdx++;

        SetWall(*elem->col);
    }
    */
}

void ProcedureMapGeneration::Set()
{

}