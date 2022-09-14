#include "stdafx.h"
#include "Main.h"
using namespace std;

void Main::Init()
{
    rooms.resize(roomMax);
    edges.resize(roomMax);
    for (auto& room : rooms)
    {
        room = new Room();
        room->col->scale.x = RANDOM->Float(20.0f, 150.0f);
        room->col->scale.y = RANDOM->Float(20.0f, 150.0f);
        room->col->SetWorldPosX(RANDOM->Float(-50.0f, 50.0f));
        room->col->SetWorldPosY(RANDOM->Float(-50.0f, 50.0f));
        room->col->isFilled = false;
        room->col->color = Color(RANDOM->Float(0.0f, 1.0f), RANDOM->Float(0.0f, 1.0f), RANDOM->Float(0.0f, 1.0f));
        room->col->collider = COLLIDER::RECT;
    }

    visited.resize(400);

    state = State::move;
}

void Main::Release()
{
    for (auto& elem : rooms) SafeDelete(elem);
    for (auto& elem : lines) SafeDelete(elem);
    lines.clear();
    edges.clear();
    visited.clear();
    passages.clear();
}

void Main::Update()
{
    if (INPUT->KeyDown('R'))
    {
        Release();
        Init();
    }
    
    switch (state)
    {
    case Main::State::move:
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
            state = State::node;
        }
        break;
    }
    case Main::State::node:
    {
        for (int i = 0; i < rooms.size(); i++)
        {
            if (rooms[i]->col->scale.x * rooms[i]->col->scale.y >= 5000.0f)
            {
                rooms[i]->col->isFilled = true;
                rooms[i]->selected = true;
            }
        }
    }

    case Main::State::triangulate:
    {
        vector<Vector2> points;

        for (auto& elem : rooms)
        {
            if (elem->selected)
            {
                points.push_back(elem->col->GetWorldPos());
            }
        }

        triangles = triangulation.triangulate(points);
        edges = triangulation.edges;

        /*
        int lineIdx = 0;
        int size = rooms.size();
        for (int i = 0; i < size; i++)
        {
            for (int j = i + 1; j < size; j++)
            {
                if (rooms[i]->selected && rooms[j]->selected)
                {
                    // MST 위한 준비 
                    Vector2 velocity = rooms[j]->col->GetWorldPos() - rooms[i]->col->GetWorldPos();
                    float dist = velocity.x * velocity.x + velocity.y * velocity.y;
                    Vector2 dir1 = velocity;
                    Vector2 dir2 = -velocity;
                    float rotation1 = Utility::DirToRadian(dir1);
                    float rotation2 = Utility::DirToRadian(dir2);
                    edges[i].push_back({ j, dist, rotation1 });
                    edges[j].push_back({ i, dist, rotation2 });
                }
                lineIdx++;
            }
        }
        */

        state = State::spanning;
        break;
    }
    case Main::State::spanning:
    {
        // MST - Prim
        /*
        for (int i = 0; i < rooms.size(); i++)
        {
            if (rooms[i]->selected)
            {
                edgePq.push({ edges[i][0].node, edges[i][0].dist, edges[i][0].dir, edges[i][0].node });
                break;
            }
        }
        while (false == edgePq.empty())
        {
            int curNode = edgePq.top().node;
            float curDist = edgePq.top().dist;
            float curDir = edgePq.top().dir;
            int beforeNode = edgePq.top().beforeNode;

            edgePq.pop();

            if (visited[curNode]) continue;
            visited[curNode] = true;

            if (curNode != beforeNode)  // 첨엔 같게 세팅했기 때문
            {
                ObLine* line = new ObLine();
                line->SetWorldPos(rooms[beforeNode]->col->GetWorldPos());
                line->color = rooms[beforeNode]->col->color;
                line->scale.x = sqrt(curDist);
                line->rotation = curDir;
                line->collider = COLLIDER::LINE;
                lines.push_back(line);
            }

            for (int i = 0; i < edges[curNode].size(); i++)
            {
                int nextNode = edges[curNode][i].node;
                float nextDist = edges[curNode][i].dist;
                float nextDir = edges[curNode][i].dir;
                edgePq.push({ nextNode, nextDist, nextDir, curNode });
            }
        }
        Sleep(1000);
        */
        state = State::passage;
        break;
    }
    case Main::State::passage:
    {
        /*
        for (auto& line : lines)
        {
            for (auto& room : rooms)
            {
                if (room->selected == false &&
                    room->col->Intersect(line))
                {
                    room->col->isFilled = true;
                }
            }
        }

        for (auto& line : lines)
        {
        }
        */
        state = State::tile;
        break;
    }
    case Main::State::tile:
    {
        int a = 2;
        break;
    }
    default:
    {
        break;
    }//case
    }//switch


    for (auto& elem : rooms) elem->Update();
    for (auto& elem : lines) if (elem) elem->Update();
    for (auto& elem : passages) if (elem) elem->Update();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
    for (auto& elem : rooms) elem->Render();
    for (auto& elem : lines) if (elem) elem->Render();
    for (auto& elem : passages) if (elem) elem->Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"유재준 Game");
    app.SetInstance(instance);
    app.InitWidthHeight(1280.0f, 720.0f);
    Main* main = new Main();
    int wParam = (int)WIN->Run(main);
    WIN->DeleteSingleton();     // 창이 없어지고 난 후 
    SafeDelete(main);           // 메모리 해제
    return wParam;
}