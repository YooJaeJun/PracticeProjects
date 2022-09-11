#include "stdafx.h"

Floor::Floor()
{
    Init();
}

void Floor::Init()
{
    Character::Init();

    col = new ObRect();
    Spawn(0);
    col->collider = COLLIDER::RECT;
    col->color = Color(1.0f, 0.0f, 0.0f);
    col->pivot = OFFSET_LT;
    col->isFilled = false;
    col->colOnOff = true;

    img = new ObImage(L"Cookie/Floor.png");
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
    img->Render();
    Character::Render();
}

void Floor::Spawn(const int idx)
{
    col->scale = Vector2(79.0f * 2.5f, 20.0f);
    col->SetWorldPosX(-app.GetHalfWidth() + idx * 79.0f * 2.5f);
    col->SetWorldPosY(-app.GetHalfHeight() + 48.0f * 2.5f);
}

void Floor::SpawnRandom(const float diff, const int maxn)
{
    if (diff - col->GetWorldPos().x > 700.0f)
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

