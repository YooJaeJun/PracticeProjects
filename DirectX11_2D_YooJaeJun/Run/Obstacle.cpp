#include "stdafx.h"

Obstacle::Obstacle()
{
    Init();
}

void Obstacle::Init()
{
    Character::Init();

    col = new ObRect();
    col->collider = Collider::rect;
    col->isVisible = true;
    col->isFilled = false;
    col->color = Color(1.0f, 0.0f, 0.0f);

    isHit = false;
    lastPosY = 0.0f;
    isCol = true;
}

void Obstacle::Release()
{
    Character::Release();
    SafeDelete(idle);
}

void Obstacle::Update()
{
    Character::Update();
    idle->Update();

    if (isHit)
    {
        col->MoveWorldPos(Vector2(3500.0f,1000.0f) * DELTA);
        col->rotation += 20.0f * DELTA;

        if (col->GetWorldPos().y > app.GetHalfHeight() + 400.0f)
        {
            col->SetWorldPos(Vector2(CAM->position.x - 2000.0f, lastPosY));
            col->rotation = 0.0f;
            isHit = false;
            isCol = true;
        }
    }
    else
    {
        lastPosY = col->GetWorldPos().y;
    }
}

void Obstacle::LateUpdate()
{
}

void Obstacle::Render()
{
    idle->Render();
    Character::Render();
}

void Obstacle::Spawn(const float origin, const int idx)
{
    col->SetWorldPosX(origin + app.GetWidth() + 100.0f * (idx + 1));

    int totalPercent = 3;
    if (RANDOM->Int(1, totalPercent) == 1)
    {
        col->colOnOff = true;
    }
    else
    {
        col->colOnOff = false;
    }
}

void Obstacle::Hit()
{
    isHit = true;
    isCol = false;
}