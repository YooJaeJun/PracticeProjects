#include "stdafx.h"
#include "Main.h"
using namespace std;

void Main::Init()
{
    rooms = vector<Room*>(roomMax);
    for (auto& room : rooms)
    {
        room = new Room();
        room->col->scale.x = RANDOM->Float(400.0f, 2000.0f);
        room->col->scale.y = RANDOM->Float(400.0f, 2000.0f);
        room->col->SetWorldPosX(RANDOM->Float(-200.0f, 200.0f));
        room->col->SetWorldPosY(RANDOM->Float(-200.0f, 200.0f));
        room->col->isFilled = false;
        // room->col->color = Color(RANDOM->Float(0.0f, 1.0f), RANDOM->Float(0.0f, 1.0f), RANDOM->Float(0.0f, 1.0f));
        room->col->color = Color(1.0f, 0.6f, 0.6f);
        room->col->collider = Collider::rect;
    }

    map = new ObTileMap();
    map->scale = Vector2(50.0f, 50.0f);
    map->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight()));
    LIGHT->light.radius = 3000.0f;
    imgIdx = 0;
    tileSize = Int2(250, 250);
    map->ResizeTile(tileSize);
    tileColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
    tileState = 0;
    map->SetWorldPos(Vector2(-5000.0f, -5000.0f));

    state = GameState::spray;
}

void Main::Release()
{
    for (auto& elem : rooms) SafeDelete(elem);
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
    SafeDelete(map);
}

void Main::Update()
{
    if (INPUT->KeyDown('R'))
    {
        Release();
        Init();
        state = GameState::spread;
    }

    ImGui::Text("FPS : %d", TIMER->GetFramePerSecond());
    
    switch (state)
    {
    case GameState::spray:
    {
        Spray();
        break;
    }
    case GameState::spread:
    {
        Spread();
        break;
    }
    case GameState::select:
    {
        Select();
        break;
    }
    case GameState::triangulate:
    {
        Triangulate();
        break;
    }
    case GameState::span:
    {
        Spanning();
        break;
    }
    case GameState::loop:
    {
        Loop();
        break;
    }
    case GameState::dig:
    {
        Dig();
        break;
    }
    case GameState::widen:
    {
        Widen();
        break;
    }
    case GameState::tile:
    {
        Tile();
        break;
    }
    case GameState::wall:
    {
        Wall();
        break;
    }
    default:
    {
        break;
    }//case
    }//switch

    for (auto& elem : rooms) elem->Update();
    for (auto& elem : linesTriangulated) elem.Update();
    for (auto& elem : linesMST) elem.Update();
    for (auto& elem : passagesLine) elem.Update();
    for (auto& elem : passages) elem.Update();
    map->Update();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
    for (auto& elem : rooms) elem->Render();
    for (auto& elem : linesTriangulated) elem.Render();
    for (auto& elem : linesMST) elem.Render();
    for (auto& elem : passagesLine) elem.Render();
    for (auto& elem : passages) elem.Render();
    map->Render();
}

void Main::ResizeScreen()
{
}

void Main::Spray()
{
    state = GameState::spread;
}

void Main::Spread()
{
    bool flag = false;
    for (auto& room : rooms)
    {
        for (auto& room2 : rooms)
        {
            if (room == room2) continue;

            if (room->col->Intersect(room2->col))
            {
                Vector2 velocity = room->col->GetWorldPos() - room2->col->GetWorldPos();
                room->col->MoveWorldPos(velocity * DELTA);
                flag = true;
            }
        }
    }
    if (false == flag)
    {
        state = GameState::select;
    }
}

void Main::Select()
{
    for (int i = 0; i < rooms.size(); i++)
    {
        if (rooms[i]->col->scale.x * rooms[i]->col->scale.y > 1'500'000.0f)
        {
            rooms[i]->col->isFilled = true;
            rooms[i]->selected = true;
            nodes.push_back(ObNode(i, rooms[i]->col->GetWorldPos()));
        }
    }

    state = GameState::triangulate;
}

void Main::Triangulate()
{
    Sleep(1000);
    triangulation.triangulate(nodes);
    linesTriangulated = triangulation.edges;
    for (auto& elem : linesTriangulated)
    {
        elem.color = Color(1.0f, 1.0f, 1.0f);
        elem.collider = Collider::line;
    }
    
    state = GameState::span;
}

void Main::Spanning()
{
    Sleep(1000);
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
    
    state = GameState::loop;
}

void Main::Loop()
{
    Sleep(1000);
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

    state = GameState::dig;
}

void Main::Dig()
{
    Sleep(1000);
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

    state = GameState::widen;
}

void Main::Widen()
{
    Sleep(1000);

    for (auto& elem : passagesLine)
    {
        float scale = 100.0f;
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

    state = GameState::tile;
}

void Main::Tile()
{
    if (INPUT->KeyPress(VK_LEFT))
    {
        CAM->position.x -= 300.0f * DELTA;
    }
    if (INPUT->KeyPress(VK_RIGHT))
    {
        CAM->position.x += 300.0f * DELTA;
    }
    if (INPUT->KeyPress(VK_UP))
    {
        CAM->position.y += 300.0f * DELTA;
    }
    if (INPUT->KeyPress(VK_DOWN))
    {
        CAM->position.y -= 300.0f * DELTA;
    }
    /*
    //Gui
    if (ImGui::Button("ErrorFileSystem?->Click me"))
    {
        ImGuiFileDialog::Instance()->Close();
    }

    //TileScale
    ImGui::SliderFloat2("Scale", (float*)&map->scale, 0.0f, 100.0f);

    //TileSize
    if (ImGui::SliderInt2("TileSize", (int*)&tileSize, 1, 100))
    {
        map->ResizeTile(tileSize);
    }

    //TilePos
    Vector2 pos = map->GetWorldPos();
    if (ImGui::SliderFloat2("TilePos", (float*)&pos, -5000.0f, 5000.0f))
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

    imgIdx = 1;

    Int2 on;
    static int flag = 1;
    if (flag)
    {
        for (auto& elem : passages)
        {
            int startY = elem.lb().y;
            int endY   = elem.lt().y;
            int startX = elem.lt().x;
            int endX   = elem.rt().x;

            for (int y = startY; y <= endY; y++)
            {
                for (int x = startX; x <= endX; x++)
                {
                    if (map->WorldPosToTileIdx(elem.GetWorldPos(), on))
                    {
                        map->SetTile(on, pickingIdx, imgIdx, tileState, tileColor);
                    }
                }
            }
        }

        for (auto& elem : rooms)
        {
            if (elem->selected)
            {
                int startY = elem->col->lb().y;
                int endY   = elem->col->lt().y;
                int startX = elem->col->lt().x;
                int endX   = elem->col->rt().x;

                for (int y = startY; y <= endY; y++)
                {
                    for (int x = startX; x <= endX; x++)
                    {
                        if (map->WorldPosToTileIdx(elem->col->GetWorldPos(), on))
                        {
                            map->SetTile(on, pickingIdx, imgIdx, tileState, tileColor);
                        }
                    }
                }
            }
        }

        flag = 0;
    }
    */
    //state = GameState::wall;
}

void Main::Wall()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"유재준 Game");
    app.SetInstance(instance);
    app.background = Color(0.0f, 0.0f, 0.0f, 1.0f);
    app.InitWidthHeight(1000.0f, 1000.0f);
    Main* main = new Main();
    int wParam = (int)WIN->Run(main);
    WIN->DeleteSingleton();     // 창이 없어지고 난 후 
    SafeDelete(main);           // 메모리 해제
    return wParam;
}