#include "stdafx.h"
#include "Main.h"
using namespace std;

void Main::Init()
{
    rooms.resize(20);
    roomsLinked.resize(20);
    for (auto& room : rooms)
    {
        room = new Room();
        room->col->scale.x = RANDOM->Float(50.0f, 150.0f);
        room->col->scale.y = RANDOM->Float(50.0f, 150.0f);
        room->col->SetWorldPosX(RANDOM->Float(-50.0f, 50.0f));
        room->col->SetWorldPosY(RANDOM->Float(-50.0f, 50.0f));
        room->col->isFilled = false;
        room->col->color = Color(RANDOM->Float(0.0f, 1.0f), RANDOM->Float(0.0f, 1.0f), RANDOM->Float(0.0f, 1.0f));
        room->col->collider = COLLIDER::RECT;
    }

    visited.resize(400);
    for (auto& elem : edges)
    {
        elem = new ObLine();
    }

    state = State::move;
}

void Main::Release()
{
    for (auto& elem : rooms) SafeDelete(elem);
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
            if (rooms[i]->col->scale.x > 80.0f && rooms[i]->col->scale.y > 80.0f)
            {
                rooms[i]->col->isFilled = true;
                rooms[i]->selected = true;
            }
        }
    }
    case Main::State::triangle:
    {
        int lineIdx = 0;
        int size = rooms.size();
        for (int i = 0; i < size; i++)
        {
            for (int j = i + 1; j < size; j++)
            {
                if (rooms[i]->selected && rooms[j]->selected)
                {
                    // MST 위함
                    Vector2 velocity = rooms[j]->col->GetWorldPos() - rooms[i]->col->GetWorldPos();
                    float dist = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
                    Vector2 dir1 = velocity;
                    Vector2 dir2 = -velocity;
                    float rotation1 = Utility::DirToRadian(dir1);
                    float rotation2 = Utility::DirToRadian(dir2);
                    roomsLinked[i].push_back({ j, dist, rotation1 });
                    roomsLinked[j].push_back({ i, dist, rotation2 });
                }
                lineIdx++;
            }
        }
        state = State::spanning;
        break;
    }
    case Main::State::spanning:
    {
        // MST - Prim
        int start = 0;
        for (int i = 0; i < rooms.size(); i++)
        {
            if (rooms[i]->selected)
            {
                edgePq.push({ roomsLinked[i][0].node, roomsLinked[i][0].dist, roomsLinked[i][0].dir });
                start = i;
                break;
            }
        }
        while (false == edgePq.empty())
        {
            int here = edgePq.top().node;
            float hereDist = edgePq.top().dist;
            float hereDir = edgePq.top().dir;

            edgePq.pop();

            if (visited[here]) continue;
            visited[here] = true;

            ObLine* edge = new ObLine();
            edge->SetWorldPos(rooms[start]->col->GetWorldPos());
            edge->color = rooms[start]->col->color;
            edge->scale.x = hereDist;
            edge->rotation = hereDir;
            edges.push_back(edge);

            start = here;

            for (int i = 0; i < roomsLinked[here].size(); i++)
            {
                int there = roomsLinked[here][i].node;
                float thereDist = roomsLinked[here][i].dist;
                float thereDir = roomsLinked[here][i].dir;
                edgePq.push({ there, thereDist, thereDir });
            }
        }
        state = State::passage;
        break;
    }
    case Main::State::passage:
    {
        int a = 1;
        break;
    }
    default:
    {
        break;
    }//case
    }//switch


    for (auto& elem : rooms) elem->Update();
    for (auto& elem : edges) elem->Update();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
    for (auto& elem : rooms) elem->Render();
    for (auto& elem : edges) elem->Render();
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