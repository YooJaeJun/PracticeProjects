#include "stdafx.h"
#include "Main.h"
using namespace std;

void Main::Init()
{
    rooms.resize(roomMax);
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
        room->col->collider = COLLIDER::RECT;
    }

    state = State::move;
}

void Main::Release()
{
    for (auto& elem : rooms) SafeDelete(elem);
    visited.clear();
    lines.clear();
    linesMST.clear();
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
            if (rooms[i]->col->scale.x * rooms[i]->col->scale.y > 6000.0f)
            {
                rooms[i]->col->isFilled = true;
                rooms[i]->selected = true;
                nodes.push_back(rooms[i]->col->GetWorldPos());
            }
        }
    }

    case Main::State::triangulate:
    {
        triangulation.triangulate(nodes);
        lines = triangulation.edges;
        for (auto& elem : lines)
        {
            elem.color = Color(1.0f, 1.0f, 1.0f, 1.0f);
            elem.collider = COLLIDER::LINE;
        }

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
        edgePq.push(lines[0]);

        while (false == edgePq.empty())
        {
            ObLine curLine = edgePq.top();

            edgePq.pop();

            if (visited[curLine.w]) continue;
            visited[curLine.w] = true;

            curLine.color = Color(0.5f, 1.0f, 0.5f);
            linesMST.push_back(curLine);

            int size = triangulation.nodes[Float2(curLine.v)].size();
            for (int i = 0; i < size; i++)
            {
                Float2 nextNodeTemp = triangulation.nodes[Float2(curLine.v)][i];
                Vector2 nextNode(nextNodeTemp.x, nextNodeTemp.y);
                ObLine nextLine(curLine.v, nextNode);
                edgePq.push(nextLine);
            }
        }


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
    for (auto& elem : lines) elem.Update();
    for (auto& elem : linesMST) elem.Update();
    for (auto& elem : passages) elem.Update();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
    for (auto& elem : rooms) elem->Render();
    for (auto& elem : lines) elem.Render();
    for (auto& elem : linesMST) elem.Render();
    for (auto& elem : passages) elem.Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"유재준 Game");
    app.SetInstance(instance);
    app.background = Color(0.0f, 0.0f, 0.0f, 1.0f);
    app.InitWidthHeight(1280.0f, 720.0f);
    Main* main = new Main();
    int wParam = (int)WIN->Run(main);
    WIN->DeleteSingleton();     // 창이 없어지고 난 후 
    SafeDelete(main);           // 메모리 해제
    return wParam;
}