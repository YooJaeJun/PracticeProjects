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
        room->col->scale.x = RANDOM->Float(200.0f, 1000.0f);
        room->col->scale.y = RANDOM->Float(200.0f, 1000.0f);
        room->col->SetWorldPosX(RANDOM->Float(-200.0f, 200.0f));
        room->col->SetWorldPosY(RANDOM->Float(-200.0f, 200.0f));
        room->col->isFilled = false;
        // room->color = Color(RANDOM->Float(0.0f, 1.0f), RANDOM->Float(0.0f, 1.0f), RANDOM->Float(0.0f, 1.0f));
        room->col->color = Color(1.0f, 0.6f, 0.6f);
        room->col->collider = Collider::rect;
    }
    roomScaleForSelect = 400'000.0f;

    state = GameState::spray;
}

void ProcedureMapGeneration::Release()
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
    for (auto& elem : tileImgs) SafeDelete(elem);
    for (auto& elem : wallImgs) SafeDelete(elem);
}

void ProcedureMapGeneration::Update()
{
    //if (INPUT->KeyDown('R'))
    //{
    //    Release();
    //    Init();
    //    state = GameState::spread;
    //}

    if (INPUT->KeyPress(VK_LEFT))
    {
        CAM->position.x -= 1500.0f * DELTA;
    }
    if (INPUT->KeyPress(VK_RIGHT))
    {
        CAM->position.x += 1500.0f * DELTA;
    }
    if (INPUT->KeyPress(VK_UP))
    {
        CAM->position.y += 1500.0f * DELTA;
    }
    if (INPUT->KeyPress(VK_DOWN))
    {
        CAM->position.y -= 1500.0f * DELTA;
    }

    switch (state)
    {
    case GameState::spray:
    {
        Spray();
        state = GameState::spread;
        break;
    }
    case GameState::spread:
    {
        Spread();
        if (flagSpread) state = GameState::select;
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
            state = GameState::tile;
        }
        break;
    }
    case GameState::tile:
    {
        if (TIMER->GetTick(timer, 1.0f))
        {
            Tile();
            state = GameState::wall;
        }
        break;
    }
    case GameState::wall:
    {
        if (TIMER->GetTick(timer, 1.0f))
        {
            Wall();
            state = GameState::set;
        }
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

    for (auto& elem : rooms) elem->Update();
    for (auto& elem : linesTriangulated) elem.Update();
    for (auto& elem : linesMST) elem.Update();
    for (auto& elem : passagesLine) elem.Update();
    for (auto& elem : passages) elem.Update();
    for (auto& elem : tileImgs) if (elem) elem->Update();
    for (auto& elem : wallImgs) if (elem) elem->Update();
}

void ProcedureMapGeneration::LateUpdate()
{
    for (auto& elem : rooms) elem->Render();
    for (auto& elem : linesTriangulated) elem.Render();
    for (auto& elem : linesMST) elem.Render();
    for (auto& elem : passagesLine) elem.Render();
    for (auto& elem : passages) elem.Render();
    for (auto& elem : tileImgs) if (elem) elem->Render();
    for (auto& elem : wallImgs) if (elem) elem->Render();
}

void ProcedureMapGeneration::Render()
{
    for (auto& elem : rooms) elem->Render();
    for (auto& elem : linesTriangulated) elem.Render();
    for (auto& elem : linesMST) elem.Render();
    for (auto& elem : passagesLine) elem.Render();
    for (auto& elem : passages) elem.Render();
    for (auto& elem : tileImgs) if (elem) elem->Render();
    for (auto& elem : wallImgs) if (elem) elem->Render();
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
    for (int i = 0; i < rooms.size(); i++)
    {
        if (rooms[i]->col->scale.x * rooms[i]->col->scale.y > roomScaleForSelect)
        {
            rooms[i]->col->isFilled = true;
            rooms[i]->selected = true;
            nodes.push_back(ObNode(i, rooms[i]->col->GetWorldPos()));
        }
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
}

void ProcedureMapGeneration::Tile()
{
    tileImgs.resize(passages.size() + rooms.size());

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
        wallImg->pivot = OFFSET_LT;
        wallImgs.push_back(wallImg);
    };

    for (auto& elem : passages)
    {
        tileImgs[tileIdx]->SetWorldPos(elem.GetWorldPos());
        tileImgs[tileIdx]->scale = elem.scale;
        tileIdx++;

        startX = elem.lt().x;
        endX = elem.rt().x;
        startY = elem.lt().y;
        endY = elem.lt().y;
        for (int x = startX; x <= endX; x += wallScale)
        {
            PushWall(x, startY);
        }
        startX = elem.lb().x;
        endX = elem.rb().x;
        startY = elem.lb().y;
        endY = elem.rb().y;
        for (int x = startX; x <= endX; x += wallScale)
        {
            PushWall(x, startY);
        }
        startX = elem.lt().x;
        endX = elem.lt().x;
        startY = elem.lb().y;
        endY = elem.lt().y;
        for (int y = startY; y <= endY; y += wallScale)
        {
            PushWall(startX, y);
        }
        startX = elem.rt().x;
        endX = elem.rt().x;
        startY = elem.rb().y;
        endY = elem.rt().y;
        for (int y = startY; y <= endY; y += wallScale)
        {
            PushWall(startX, y);
        }
    }

    for (auto& elem : rooms)
    {
        if (elem->selected)
        {
            tileImgs[tileIdx]->SetWorldPos(elem->col->GetWorldPos());
            tileImgs[tileIdx]->scale = elem->col->scale;
            tileIdx++;

            startX = elem->col->lt().x;
            endX = elem->col->rt().x;
            startY = elem->col->lt().y;
            endY = elem->col->lt().y;
            for (int x = startX; x <= endX; x += wallScale)
            {
                PushWall(x, startY);
            }
            startX = elem->col->lb().x;
            endX = elem->col->rb().x;
            startY = elem->col->lb().y;
            endY = elem->col->rb().y;
            for (int x = startX; x <= endX; x += wallScale)
            {
                PushWall(x, startY);
            }
            startX = elem->col->lt().x;
            endX = elem->col->lt().x;
            startY = elem->col->lb().y;
            endY = elem->col->lt().y;
            for (int y = startY; y <= endY; y += wallScale)
            {
                PushWall(startX, y);
            }
            startX = elem->col->rt().x;
            endX = elem->col->rt().x;
            startY = elem->col->rb().y;
            endY = elem->col->rt().y;
            for (int y = startY; y <= endY; y += wallScale)
            {
                PushWall(startX, y);
            }
        }
    }
}

void ProcedureMapGeneration::Wall()
{
}

void ProcedureMapGeneration::Set()
{

}