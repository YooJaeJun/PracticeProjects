#include "stdafx.h"

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

    rooms = vector<Room*>(roomMax);
    for (auto& room : rooms)
    {
        room = new Room();
        room->col->scale.x = RANDOM->Float(200.0f, 800.0f);
        room->col->scale.y = RANDOM->Float(200.0f, 800.0f);
        room->col->SetWorldPosX(RANDOM->Float(-200.0f, 200.0f));
        room->col->SetWorldPosY(RANDOM->Float(-200.0f, 200.0f));
        room->col->isFilled = false;
        room->col->color = Color(1.0f, 0.6f, 0.6f);
        room->col->collider = Collider::rect;
    }
    roomScaleForSelect = 200'000.0f;

    //grid.resize(gridMax);
    //for (int i = 0; i < gridMax; i++)
    //{
    //    grid[i].resize(gridMax);
    //}
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
    grid.clear();
    for (auto& elem : tiles) SafeDelete(elem);
    for (auto& elem : walls) SafeDelete(elem);
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
            state = GameState::clean;
        }
        break;
    }
    case GameState::clean:
    {
        if (TIMER->GetTick(timer, 1.0f))
        {
            Clean();
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

    for (auto& elem : rooms) if (elem) elem->Update();
    for (auto& elem : roomsSelected) if (elem) elem->Update();
    for (auto& elem : linesTriangulated) elem.Update();
    for (auto& elem : linesMST) elem.Update();
    for (auto& elem : passagesLine) elem.Update();
    for (auto& elem : passages) elem.Update();

    for (auto& elem : walls)
    {
        if (elem &&
            elem->col->GetWorldPos().x > CAM->position.x - 1000.0f &&
            elem->col->GetWorldPos().x < CAM->position.x + 1000.0f &&
            elem->col->GetWorldPos().y > CAM->position.y - 1000.0f &&
            elem->col->GetWorldPos().y < CAM->position.y + 1000.0f)
        {
            elem->Update();
        }
    }
    for (auto& elem : tiles)
    {
        if (elem &&
            elem->col->GetWorldPos().x > CAM->position.x - 1000.0f &&
            elem->col->GetWorldPos().x < CAM->position.x + 1000.0f &&
            elem->col->GetWorldPos().y > CAM->position.y - 1000.0f &&
            elem->col->GetWorldPos().y < CAM->position.y + 1000.0f)
        {
            elem->Update();
        }
    }
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
    for (auto& elem : passages) elem.Render();

    for (auto& elem : walls)
    {
        if (elem &&
            elem->col->GetWorldPos().x > CAM->position.x - 2000.0f &&
            elem->col->GetWorldPos().x < CAM->position.x + 2000.0f &&
            elem->col->GetWorldPos().y > CAM->position.y - 2000.0f &&
            elem->col->GetWorldPos().y < CAM->position.y + 2000.0f)
        {
            elem->Render();
        }
    }
    for (auto& elem : tiles)
    {
        if (elem &&
            elem->col->GetWorldPos().x > CAM->position.x - 2000.0f &&
            elem->col->GetWorldPos().x < CAM->position.x + 2000.0f &&
            elem->col->GetWorldPos().y > CAM->position.y - 2000.0f &&
            elem->col->GetWorldPos().y < CAM->position.y + 2000.0f)
        {
            elem->Render();
        }
    }

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
            elem->col->scale.x -= 100.0f;
            elem->col->scale.y -= 100.0f;
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
        //int vRoomIdx = 0, wRoomIdx = 0;

        //for (int i = 0; i < roomsSelected.size(); i++)
        //{
        //    Vector2 v = Vector2(elem.v.x, elem.v.y);
        //    if (roomsSelected[i]->col->Intersect(v))
        //    {
        //        vRoomIdx = i;
        //    }
        //    Vector2 w = Vector2(elem.w.x, elem.w.y);
        //    if (roomsSelected[i]->col->Intersect(w))
        //    {
        //        wRoomIdx = i;
        //    }
        //}

        //auto checkQuadrant = [&](ObNode v, ObNode w) ->int
        //{
        //    if (almostEqualFloat(v.x, w.x) && almostEqualFloat(v.y, w.y)) return 0;
        //    else if (v.x < w.x && v.y < w.y) return 1;
        //    else if (v.x > w.x && v.y < w.y) return 2;
        //    else if (v.x > w.x && v.y > w.y) return 3;
        //    else return 4;
        //};

        const ObNode& v = elem.v;
        const ObNode& w = elem.w;

        //Vector2 vScale = roomsSelected[vRoomIdx]->col->scale / 2.0f;
        //Vector2 wScale = roomsSelected[wRoomIdx]->col->scale / 2.0f;
        //ObLine l1(ObNode(v.x + vScale.x, v.y), ObNode(w.x, v.y));
        //ObLine l2(ObNode(w.x, v.y), ObNode(w.x, w.y - wScale.y));
        //ObLine l3(ObNode(w.x, v.y), ObNode(w.x, w.y + wScale.y));
        //ObLine l4(ObNode(v.x - vScale.x, v.y), ObNode(w.x, v.y));
        //ObLine l5(ObNode(w.x, v.y), ObNode(w.x, w.y - wScale.y));
        //ObLine l6(ObNode(w.x, v.y), ObNode(w.x, w.y + wScale.y));


        ObLine l1(ObNode(v.x, v.y), ObNode(w.x, v.y));
        ObLine l2(ObNode(w.x, w.y), ObNode(w.x, v.y));

        //l1.color = l2.color = l3.color = l4.color = l5.color = l6.color = Color(1.0f, 0.8f, 0.6f);
        l1.color = l2.color = Color(1.0f, 0.8f, 0.6f);

        //// 1사분면
        //if (checkQuadrant(v, w) == 1)
        //{
        //    passagesLine.push_back(l1);
        //    passagesLine.push_back(l2);
        //}
        //// 2사분면
        //else if (checkQuadrant(v, w) == 2)
        //{
        //    passagesLine.push_back(l4);
        //    passagesLine.push_back(l5);
        //}
        //// 3사분면
        //else if (checkQuadrant(v, w) == 3)
        //{
        //    passagesLine.push_back(l4);
        //    passagesLine.push_back(l6);
        //}
        //// 4사분면
        //else
        //{
        //    passagesLine.push_back(l1);
        //    passagesLine.push_back(l3);
        //}
        passagesLine.push_back(l1);
        passagesLine.push_back(l2);
    }

    linesMST.clear();
}

void ProcedureMapGeneration::Widen()
{
    for (auto& elem : passagesLine)
    {
        float scale = 200.0f;
        const ObNode& v = elem.v;
        const ObNode& w = elem.w;

        ObRect r;
        // 수평
        if (almostEqualFloat(v.x, w.x))
        {
            r.scale.x = scale;
            r.scale.y = abs(v.y - w.y);
            r.SetWorldPosX(v.x);
            r.SetWorldPosY((v.y + w.y) / 2.0f);
        }
        // 수직
        else if (almostEqualFloat(v.y, w.y))
        {
            r.scale.x = abs(v.x - w.x);
            r.scale.y = scale;
            r.SetWorldPosX((v.x + w.x) / 2.0f);
            r.SetWorldPosY(v.y);
        }
        r.color = Color(1.0f, 0.8f, 0.6f);

        passages.push_back(r);
    }
}

void ProcedureMapGeneration::Tile()
{
    tiles.resize(passages.size() + roomsSelected.size());
    walls.resize(tiles.size() * 4);

    for (auto& elem : tiles)
    {
        elem = new Obstacle;
        elem->col = new ObRect;
        elem->col->isVisible = false;
        elem->idle = new ObImage(L"EnterTheGungeon/Level/Tile.png");
        elem->idle->SetParentRT(*elem->col);
        elem->idle->isVisible = true;
    }

    int tileIdx = 0;
    int wallIdx = 0;
    int startY = 0;
    int endY = 0;
    int startX = 0;
    int endX = 0;

    float wallScale = 50.0f;

    auto PushWall = [&](const float x, const float y, const float scaleX, const float scaleY)
    {
        walls[wallIdx] = new Obstacle;
        walls[wallIdx]->col = new ObRect;
        walls[wallIdx]->col->scale = Vector2(scaleX, scaleY);
        walls[wallIdx]->col->SetWorldPos(Vector2(x, y));
        walls[wallIdx]->col->isVisible = false;
        walls[wallIdx]->idle = new ObImage(L"EnterTheGungeon/Level/Wall.png");
        walls[wallIdx]->idle->SetParentRT(*walls[wallIdx]->col);
        walls[wallIdx]->idle->isVisible = true;
        walls[wallIdx]->idle->scale = walls[wallIdx]->col->scale;

        //int coef = gridMax / 2;
        //Vector2 start = Vector2(x + coef, y + coef);
        //Vector2 end = Vector2(x + coef + scaleX, y + coef + scaleY);
        //for (int i = start.y; i <= end.y; i++)
        //{
        //    for (int j = start.x; j <= end.x; j++)
        //    {
        //        grid[i][j] = false;
        //    }
        //}
    };

    auto SetWall = [&](ObRect& elem)
    {
        startX = elem.lt().x;
        endX = elem.rt().x;
        startY = elem.lt().y;
        endY = elem.lt().y;
        wallScale = abs(endX - startX);
        PushWall(startX, startY, wallScale, 50.0f);
        walls[wallIdx]->col->pivot = OFFSET_LB;
        walls[wallIdx]->idle->pivot = OFFSET_LB;
        wallIdx++;

        startX = elem.lb().x;
        endX = elem.rb().x;
        startY = elem.lb().y;
        endY = elem.rb().y;
        wallScale = abs(endX - startX);
        PushWall(startX, startY, wallScale, 50.0f);
        walls[wallIdx]->col->pivot = OFFSET_LT;
        walls[wallIdx]->idle->pivot = OFFSET_LT;
        wallIdx++;

        startX = elem.lt().x;
        endX = elem.lt().x;
        startY = elem.lb().y;
        endY = elem.lt().y;
        wallScale = abs(endY - startY);
        PushWall(startX, startY, 50.0f, wallScale);
        walls[wallIdx]->col->pivot = OFFSET_RB;
        walls[wallIdx]->idle->pivot = OFFSET_RB;
        wallIdx++;

        startX = elem.rt().x;
        endX = elem.rt().x;
        startY = elem.rt().y;
        endY = elem.rb().y;
        wallScale = abs(endY - startY);
        PushWall(startX, startY, 50.0f, wallScale);
        walls[wallIdx]->col->pivot = OFFSET_LT;
        walls[wallIdx]->idle->pivot = OFFSET_LT;
        wallIdx++;
    };

    auto SetTile = [&](Vector2 pos, Vector2 scale)
    {
        int coef = gridMax / 2;
        Vector2 start = pos - scale / 2.0f;
        Vector2 end = pos + scale / 2.0f;
        start.x += coef;
        start.y += coef;
        end.x += coef;
        end.y += coef;
        for (int i = start.y; i <= end.y; i++)
        {
            for (int j = start.x; j <= end.x; j++)
            {
                grid[i][j] = true;
            }
        }
    };

    // 복도 벽
    for (auto& elem : passages)
    {
        SetWall(elem);
    }
    // 방 벽
    for (auto& elem : roomsSelected)
    {
        SetWall(*elem->col);
    }

    // 복도 타일
    for (auto& elem : passages)
    {
        tiles[tileIdx]->col->SetWorldPos(elem.GetWorldPos());
        tiles[tileIdx]->col->scale = elem.scale;
        tiles[tileIdx]->idle->scale = elem.scale;

        //SetTile(elem.GetWorldPos(), elem.scale);

        tileIdx++;
    }
    // 방 타일
    for (auto& elem : roomsSelected)
    {
        tiles[tileIdx]->col->SetWorldPos(elem->col->GetWorldPos());
        tiles[tileIdx]->col->scale = elem->col->scale;
        tiles[tileIdx]->idle->scale = elem->col->scale;

        //SetTile(elem->col->GetWorldPos(), elem->col->scale);

        tileIdx++;
    }
}

void ProcedureMapGeneration::Set()
{

}