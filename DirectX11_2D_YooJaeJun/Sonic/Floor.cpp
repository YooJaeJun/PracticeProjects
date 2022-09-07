#include "stdafx.h"

void Floor::Init()
{
    Character::Init();
    col = new ObRect();
    col->scale = Vector2(79.0f * 3.0f, 20.0f);
    col->collider = COLLIDER::RECT;
    col->isFilled = false;
    col->color = Color(1.0f, 0.0f, 0.0f);
    col->pivot = OFFSET_LT;

    img = new ObImage(L"floor.bmp");
    img->scale = Vector2(79.0f * 3.0f, 48.0f * 3.0f);
    img->SetParentRT(*col);
    img->pivot = OFFSET_LT;

    speed = 1.0f;
}

void Floor::Release()
{
    Character::Release();
    SafeDelete(img);
}

void Floor::Update()
{
    Character::Update();
    col->MoveWorldPos(Vector2(-speed, 0.0f));
    if (col->GetWorldPos().x + col->scale.x < -app.GetHalfWidth())
    {
        int r = RANDOM->Int(0, 4);
        if (r) col->SetWorldPosX(-app.GetHalfWidth() + 7.0f * col->scale.x);
        else col->SetWorldPosX(-app.GetHalfWidth() + 17.0f * col->scale.x);
        col->SetWorldPosY(-app.GetHalfHeight() + img->scale.y);
    }
    img->Update();
}

void Floor::LateUpdate()
{
}

void Floor::Render()
{
    img->Render();
    Character::Render();
}
