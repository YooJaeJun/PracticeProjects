#include "stdafx.h"

MapObject::MapObject()
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
        elem->idle = new ObImage(L"EnterTheGungeon/Level/tile.png");
        elem->idle->maxFrame.x = 2;
        elem->idle->scale.x = 100.0f;
        elem->idle->scale.y = 100.0f;
        elem->idle->SetWorldPosX(idx % 10 * elem->idle->scale.x);
        elem->idle->SetWorldPosY(idx / 10 * elem->idle->scale.y);
        idx++;
    }

    
    float wallScaleCoef = 3.0f;

    idx = 0;
    for (auto& elem : wallFront)
    {
        elem = new Obstacle;
        elem->col = new ObRect;
        elem->col->isVisible = true;
        elem->col->isFilled = false;
        elem->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        elem->col->scale.x = 16.0f * wallScaleCoef;
        elem->col->scale.y = 8.0f * wallScaleCoef;
        elem->col->SetWorldPosX(300.0f + idx * elem->col->scale.x / 2.0f);
        elem->col->SetWorldPosY(400.0f);
        elem->col->collider = COLLIDER::RECT;
        elem->idle = new ObImage(L"EnterTheGungeon/Level/Wall_Front.png");
        elem->idle->maxFrame.x = 2;
        elem->idle->scale.x = 16.0f * wallScaleCoef;
        elem->idle->scale.y = 8.0f * wallScaleCoef;
        elem->idle->SetParentRT(*elem->col);
        idx++;
    }

    idx = 0;
    for (auto& elem : wallSide)
    {
        elem = new Obstacle;
        elem->col = new ObRect;
        elem->col->isVisible = true;
        elem->col->isFilled = false;
        elem->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        elem->col->scale.x = 16.0f * wallScaleCoef;
        elem->col->scale.y = 16.0f * wallScaleCoef;
        elem->col->SetWorldPosX(300.0f + idx * elem->col->scale.x / 2.0f);
        elem->col->SetWorldPosY(500.0f);
        elem->col->collider = COLLIDER::RECT;
        elem->idle = new ObImage(L"EnterTheGungeon/Level/Wall_Side.png");
        elem->idle->maxFrame.x = 2;
        elem->idle->scale.x = 16.0f * wallScaleCoef;
        elem->idle->scale.y = 8.0f * wallScaleCoef;
        elem->idle->SetParentRT(*elem->col);
        idx++;
    }

    idx = 0;
    for (auto& elem : wallBack)
    {
        elem = new Obstacle;
        elem->col = new ObRect;
        elem->col->isVisible = true;
        elem->col->isFilled = false;
        elem->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        elem->col->scale.x = 16.0f * wallScaleCoef;
        elem->col->scale.y = 16.0f * wallScaleCoef;
        elem->col->SetWorldPosX(300.0f + idx * elem->col->scale.x / 2.0f);
        elem->col->SetWorldPosY(600.0f);
        elem->col->collider = COLLIDER::RECT;
        elem->idle = new ObImage(L"EnterTheGungeon/Level/Wall_Back.png");
        elem->idle->maxFrame.x = 2;
        elem->idle->scale.x = 16.0f * wallScaleCoef;
        elem->idle->scale.y = 8.0f * wallScaleCoef;
        elem->idle->SetParentRT(*elem->col);
        idx++;
    }


    float doorOpenScaleCoef = 2.5f;

    idx = 0;
    for (auto& elem : doorOpenUp)
    {
        elem = new Obstacle;
        elem->col = new ObRect;
        elem->col->isFilled = false;
        elem->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        elem->col->scale.x = 66.0f / 3.0f * doorOpenScaleCoef;
        elem->col->scale.y = 48.0f * doorOpenScaleCoef;
        elem->col->SetWorldPosX(200.0f + idx * elem->col->scale.x);
        elem->col->collider = COLLIDER::RECT;
        elem->idle = new ObImage(L"EnterTheGungeon/Level/Door_Open_Up.png");
        elem->idle->maxFrame.x = 3;
        elem->idle->scale.x = 66.0f / 3.0f * doorOpenScaleCoef;
        elem->idle->scale.y = 48.0f * doorOpenScaleCoef;
        elem->idle->SetParentRT(*elem->col);
        elem->idle->ChangeAnim(ANIMSTATE::STOP, 0.1f);

        if (idx & 1)
        {
            elem->col->rotationY = PI;
        }
        idx++;
    }

    idx = 0;
    for (auto& elem : doorOpenDown)
    {
        elem = new Obstacle;
        elem->col = new ObRect;
        elem->col->isVisible = false;   //
        elem->col->isFilled = false;
        elem->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        elem->col->scale.x = 66.0f / 3.0f * doorOpenScaleCoef;
        elem->col->scale.y = 48.0f * doorOpenScaleCoef;
        elem->col->SetWorldPosX(200.0f + idx * elem->col->scale.x);
        elem->col->collider = COLLIDER::RECT;
        elem->idle = new ObImage(L"EnterTheGungeon/Level/Door_Open_Down.png");
        elem->idle->isVisible = false;  //
        elem->idle->maxFrame.x = 3;
        elem->idle->scale.x = 66.0f / 3.0f * doorOpenScaleCoef;
        elem->idle->scale.y = 48.0f * doorOpenScaleCoef;
        elem->idle->SetParentRT(*elem->col);
        elem->idle->ChangeAnim(ANIMSTATE::STOP, 0.1f);

        if (idx & 1)
        {
            elem->col->rotationY = PI;
        }
        idx++;
    }

    float doorClosedScaleCoef = 2.5f;

    idx = 0;
    for (auto& elem : doorClosed)
    {
        elem = new Obstacle;
        elem->col = new ObRect;
        elem->col->isVisible = true;
        elem->col->isFilled = false;
        elem->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        elem->col->scale.x = 68.0f / 2.0f * doorClosedScaleCoef;
        elem->col->scale.y = 41.0f * doorClosedScaleCoef;
        elem->col->SetWorldPosX(200.0f + idx * elem->col->scale.x);
        elem->col->SetWorldPosY(200.0f);
        elem->col->collider = COLLIDER::RECT;
        elem->idle = new ObImage(L"EnterTheGungeon/Level/Door_Closed.png");
        elem->idle->maxFrame.x = 2;
        elem->idle->scale.x = 68.0f / 2.0f * doorClosedScaleCoef;
        elem->idle->scale.y = 41.0f * doorClosedScaleCoef;
        elem->idle->SetParentRT(*elem->col);
        elem->idle->ChangeAnim(ANIMSTATE::LOOP, 2.0f);
        idx++;
    }
}

void MapObject::Release()
{
    bg->Release();
    SafeDelete(idle);
    for (auto& elem : tile) elem->Release();
    for (auto& elem : wallFront) elem->Release();
    for (auto& elem : wallSide) elem->Release();
    for (auto& elem : wallBack) elem->Release();
    for (auto& elem : doorOpenUp) elem->Release();
    for (auto& elem : doorOpenDown) elem->Release();
    for (auto& elem : doorClosed) elem->Release();
}

void MapObject::Update()
{
    bg->Update();
    idle->Update();
    for (auto& elem : tile) elem->Update();
    for (auto& elem : wallFront) elem->Update();
    for (auto& elem : wallSide) elem->Update();
    for (auto& elem : wallBack) elem->Update();
    for (auto& elem : doorOpenUp) elem->Update();
    for (auto& elem : doorOpenDown) elem->Update();
    for (auto& elem : doorClosed) elem->Update();
}

void MapObject::LateUpdate()
{
}

void MapObject::Render()
{
    bg->Render();
    idle->Render();
    for (auto& elem : tile) elem->Render();
    for (auto& elem : wallFront) elem->Render();
    for (auto& elem : wallSide) elem->Render();
    for (auto& elem : wallBack) elem->Render();
    for (auto& elem : doorOpenUp) elem->Render();
    for (auto& elem : doorOpenDown) elem->Render();
    for (auto& elem : doorClosed) elem->Render();
}
