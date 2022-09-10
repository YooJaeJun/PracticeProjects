#include "stdafx.h"

Floor::Floor()
{
    Init();
}

void Floor::Init()
{
    Character::Init();

    col = new ObRect();
    col->scale = Vector2(79.0f * 2.5f, 20.0f);
    col->SetWorldPosY(-app.GetHalfHeight() + 48.0f * 2.5f);
    col->collider = COLLIDER::RECT;
    col->color = Color(1.0f, 0.0f, 0.0f);
    col->pivot = OFFSET_LT;
    col->isFilled = false;
    col->colOnOff = true;

    img = new ObImage(L"floor.bmp");
    img->scale = Vector2(79.0f, 48.0f) * 2.5f;
    img->SetParentRT(*col);
    img->pivot = OFFSET_LT;
}

void Floor::Release()
{
    Character::Release();
    SafeDelete(img);
}

void Floor::Update()
{
    img->Update();
    Character::Update();
}

void Floor::LateUpdate()
{
}

void Floor::Render()
{
    Character::Render();
    img->Render();
}

void Floor::Spawn(const float diff, const int maxn)
{
    if (diff - col->GetWorldPos().x > 500.0f)
    {
        col->MoveWorldPos(Vector2(col->scale.x * maxn, 0.0f));

        if (RANDOM->Int(0, 5))
        {
            col->colOnOff = true;
        }
        else
        {
            col->colOnOff = false;
        }
    }
}

