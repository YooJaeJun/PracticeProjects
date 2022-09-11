#include "stdafx.h"

Obstacle::Obstacle()
{
    Init();
}

void Obstacle::Init()
{
    Character::Init();

    col = new ObCircle();
    col->scale = Vector2(61.0f * 2.0f, 62.0f * 2.0f);
    col->collider = COLLIDER::CIRCLE;
    col->isFilled = false;
    col->color = Color(1.0f, 0.0f, 0.0f);
    col->SetWorldPosX(app.GetHalfWidth() + col->scale.x + RANDOM->Float(600.0f, 3000.0f));
    col->SetWorldPosY(RANDOM->Float(-200.0f, 0.0f));

    img = new ObImage(L"rock.bmp");
    img->scale = Vector2(61.0f * 2.0f, 62.0f * 2.0f);
    img->SetParentRT(*col);
}

void Obstacle::Release()
{
    Character::Release();
    SafeDelete(img);
}

void Obstacle::Update()
{
    Character::Update();

    if (col->GetWorldPos().x + col->scale.x / 2 < -app.GetHalfWidth())
    {
        col->SetWorldPosX(app.GetHalfWidth() + col->scale.x + RANDOM->Float(600.0f, 3000.0f));
        col->SetWorldPosY(RANDOM->Float(-200.0f, 0.0f));
    }
    img->Update();
}

void Obstacle::LateUpdate()
{
}

void Obstacle::Render()
{
    img->Render();
    Character::Render();
}

void Obstacle::Spawn(const float diff, const int maxn)
{
    if (diff - col->GetWorldPos().x > 500.0f)
    {
        col->SetWorldPosX(diff + app.GetWidth() + RANDOM->Float(100.0f, 1000.0f));
        col->SetWorldPosY(RANDOM->Float(-200.0f, 0.0f));

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