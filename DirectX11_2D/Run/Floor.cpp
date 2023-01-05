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
    col->collider = Collider::rect;
    col->color = Color(0.5f, 0.5f, 0.5f);
    col->pivot = OFFSET_LT;
    col->isFilled = false;
    col->colOnOff = true;
}

void Floor::Release()
{
    Character::Release();
    SafeDelete(idle);
}

void Floor::Update()
{
    idle->Update();
    Character::Update();
}

void Floor::LateUpdate()
{
}

void Floor::Render()
{
    idle->Render();
    Character::Render();
}

void Floor::Spawn(const int idx)
{
    col->SetWorldPosX(-app.GetHalfWidth() + idx * 79.0f * 2.5f);
    col->SetWorldPosY(-app.GetHalfHeight() + 48.0f * 2.5f);
}

void Floor::SpawnRandom(const float origin, const int maxn)
{
    col->MoveWorldPos(Vector2(col->scale.x * (maxn + 1), 0.0f));

    if (RANDOM->Int(0, 0) == 0)
    {
        col->colOnOff = true;
    }
    else
    {
        col->colOnOff = false;
    }
}

