#include "stdafx.h"

Item::Item()
{
    Init();
}

void Item::Init()
{
    Character::Init();

    col = new ObCircle;
    col->collider = Collider::circle;
    col->isVisible = false;
    col->isFilled = false;
    col->color = Color(1.0f, 0.0f, 0.0f);
}

void Item::Release()
{
    Character::Release();
    SafeDelete(idle);
}

void Item::Update()
{
    Character::Update();
    idle->Update();
}

void Item::LateUpdate()
{
}

void Item::Render()
{
    idle->Render();
    Character::Render();
}

void Item::Spawn(const float origin, const int maxn)
{
    col->MoveWorldPos(Vector2(100.0f * maxn, 0.0f));

    int totalPercent = 1;
    if (type == ItemType::SCORE)
    {
        totalPercent = 1;
        col->SetWorldPosY(-app.GetHalfHeight() + 200.0f);
    }
    else if (type == ItemType::LIFE)
    {
        totalPercent = 3;
        col->SetWorldPosX(CAM->position.x + app.GetHalfWidth() + col->scale.x);
        col->SetWorldPosY(-app.GetHalfHeight() + RANDOM->Float(300.0f, 400.0f));
    }
    else if (type == ItemType::BOOST)
    {
        totalPercent = 3;
        col->SetWorldPosX(CAM->position.x + app.GetHalfWidth() + col->scale.x);
        col->SetWorldPosY(-app.GetHalfHeight() + RANDOM->Float(300.0f, 400.0f));
    }

    if (RANDOM->Int(1, totalPercent) == 1)
    {
        col->colOnOff = true;
    }
    else
    {
        col->colOnOff = false;
    }
}