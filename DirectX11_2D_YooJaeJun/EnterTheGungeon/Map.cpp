#include "stdafx.h"

Map::Map()
{
    int idx = 0;

    bg = new UI;
    bg->img = new ObImage(L"EnterTheGungeon/Background.jpg");
    bg->img->scale.x = 700.0f * 2.0f;
    bg->img->scale.y = 370.0f * 2.0f;

    idx = 0;
    for (auto& elem : tile)
    {
        elem = new Obstacle;
        elem->col = new ObRect;
        elem->col->scale.x = 60.0f;
        elem->col->scale.y = 44.0f;
        elem->col->SetWorldPosX(idx % 10 + elem->col->scale.x);
        elem->col->SetWorldPosY(idx / 10);
        elem->idle = new ObImage(L"EnterTheGungeon/Level/tile.png");
        elem->idle->maxFrame.x = 2;
        elem->idle->scale.x = 60.0f;
        elem->idle->scale.y = 44.0f;
        elem->idle->SetParentRT(*elem->col);
        elem->idle->SetWorldPosX(idx % 10 + elem->idle->scale.x);
        elem->idle->SetWorldPosY(idx / 10);
        idx++;
    }


    idx = 0;
    for (auto& elem : wallFront)
    {
        elem = new Obstacle;
        elem->col = new ObRect;
        elem->col->scale.x = 16.0f;
        elem->col->scale.y = 8.0f;
        elem->col->SetWorldPosX(200.0f + idx * elem->col->scale.x / 2.0f);
        elem->idle = new ObImage(L"EnterTheGungeon/Level/Wall_Front.png");
        elem->idle->maxFrame.x = 2;
        elem->idle->scale.x = 16.0f;
        elem->idle->scale.y = 8.0f;
        elem->idle->SetWorldPosX(200.0f + idx * elem->idle->scale.x / 2.0f);
        elem->idle->SetParentRT(*elem->col);
        elem->idle->SetWorldPosX(300.0f);
        idx++;
    }

    idx = 0;
    for (auto& elem : wallSide)
    {
        elem = new Obstacle;
        elem->col = new ObRect;
        elem->col->scale.x = 16.0f;
        elem->col->scale.y = 16.0f;
        elem->col->SetWorldPosX(200.0f + idx * elem->col->scale.x / 2.0f);
        elem->idle = new ObImage(L"EnterTheGungeon/Level/Wall_Side.png");
        elem->idle->maxFrame.x = 2;
        elem->idle->scale.x = 16.0f;
        elem->idle->scale.y = 8.0f;
        elem->idle->SetWorldPosX(200.0f + idx * elem->idle->scale.x / 2.0f);
        elem->idle->SetParentRT(*elem->col);
        elem->idle->SetWorldPosX(300.0f);
        idx++;
    }

    idx = 0;
    for (auto& elem : wallBack)
    {
        elem = new Obstacle;
        elem->col = new ObRect;
        elem->col->scale.x = 16.0f;
        elem->col->scale.y = 16.0f;
        elem->col->SetWorldPosX(200.0f + idx * elem->col->scale.x / 2.0f);
        elem->idle = new ObImage(L"EnterTheGungeon/Level/Wall_Back.png");
        elem->idle->maxFrame.x = 2;
        elem->idle->scale.x = 16.0f;
        elem->idle->scale.y = 8.0f;
        elem->idle->SetWorldPosX(200.0f + idx * elem->idle->scale.x / 2.0f);
        elem->idle->SetParentRT(*elem->col);
        elem->idle->SetWorldPosX(300.0f);
        idx++;
    }


    float doorOpenScaleCoef = 2.0f;

    idx = 0;
    for (auto& elem : doorOpen)
    {
        elem = new Obstacle;
        elem->col = new ObRect;
        elem->col->scale.x = 22.0f * doorOpenScaleCoef;
        elem->col->scale.y = 37.0f * doorOpenScaleCoef;
        elem->col->SetWorldPosX(200.0f + idx * elem->col->scale.x);
        elem->idle = new ObImage(L"EnterTheGungeon/Level/Door_Open.png");
        elem->idle->scale.x = 22.0f * doorOpenScaleCoef;
        elem->idle->scale.y = 37.0f * doorOpenScaleCoef;
        elem->idle->SetWorldPosX(200.0f + idx * elem->idle->scale.x);
        elem->idle->SetParentRT(*elem->col);

        if (idx & 1)
        {
            elem->col->rotationY = PI;
            elem->idle->rotationY = PI;
        }
        idx++;
    }

    idx = 0;
    for (auto& elem : doorClosed)
    {
        elem = new Obstacle;
        elem->col = new ObRect;
        elem->col->scale.x = 68.0f / 2.0f * doorOpenScaleCoef;
        elem->col->scale.y = 41.0f * doorOpenScaleCoef;
        elem->col->SetWorldPosX(200.0f + idx * elem->col->scale.x / 2.0f);
        elem->idle = new ObImage(L"EnterTheGungeon/Level/Door_Closed.png");
        elem->idle->maxFrame.x = 2;
        elem->idle->scale.x = 68.0f / 2.0f * doorOpenScaleCoef;
        elem->idle->scale.y = 41.0f * doorOpenScaleCoef;
        elem->idle->SetWorldPosX(200.0f + idx * elem->idle->scale.x / 2.0f);
        elem->idle->SetParentRT(*elem->col);
        elem->idle->ChangeAnim(ANIMSTATE::LOOP, 2.0f);
        idx++;
    }
}

void Map::Release()
{
    bg->Release();
    SafeDelete(idle);
    for (auto& elem : tile) elem->Release();
    for (auto& elem : wallFront) elem->Release();
    for (auto& elem : wallSide) elem->Release();
    for (auto& elem : wallBack) elem->Release();
    for (auto& elem : doorOpen) elem->Release();
    for (auto& elem : doorClosed) elem->Release();
}

void Map::Update()
{
    bg->Update();
    idle->Update();
    for (auto& elem : tile) elem->Update();
    for (auto& elem : wallFront) elem->Update();
    for (auto& elem : wallSide) elem->Update();
    for (auto& elem : wallBack) elem->Update();
    for (auto& elem : doorOpen) elem->Update();
    for (auto& elem : doorClosed) elem->Update();
}

void Map::LateUpdate()
{
}

void Map::Render()
{
    bg->Render();
    idle->Render();
    for (auto& elem : tile) elem->Render();
    for (auto& elem : wallFront) elem->Render();
    for (auto& elem : wallSide) elem->Render();
    for (auto& elem : wallBack) elem->Render();
    for (auto& elem : doorOpen) elem->Render();
    for (auto& elem : doorClosed) elem->Render();
}
