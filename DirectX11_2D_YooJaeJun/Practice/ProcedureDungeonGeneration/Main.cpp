#include "stdafx.h"
#include "Main.h"
using namespace std;

void Main::Init()
{
    rooms = vector<Room*>(roomMax);
    for (auto& room : rooms)
    {
        room = new Room();
        room->col->scale.x = RANDOM->Float(20.0f, 150.0f);
        room->col->scale.y = RANDOM->Float(20.0f, 150.0f);
        room->col->SetWorldPosX(RANDOM->Float(-50.0f, 50.0f));
        room->col->SetWorldPosY(RANDOM->Float(-50.0f, 50.0f));
        room->col->isFilled = false;
        // room->col->color = Color(RANDOM->Float(0.0f, 1.0f), RANDOM->Float(0.0f, 1.0f), RANDOM->Float(0.0f, 1.0f));
        room->col->color = Color(1.0f, 0.6f, 0.6f);
        room->col->collider = Collider::rect;
    }
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
    case GameState::tile:
    {
        Tile();
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
        if (rooms[i]->col->scale.x * rooms[i]->col->scale.y > 7777.0f)
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
    state = GameState::tile;
}

void Main::Tile()
{
    int a = 1;
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