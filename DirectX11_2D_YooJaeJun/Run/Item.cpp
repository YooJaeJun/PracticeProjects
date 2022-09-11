#include "stdafx.h"

Item::Item()
{
    Init();
}

void Item::Init()
{
    Character::Init();

    col = new ObCircle;
    col->isVisible = true;
    col->isFilled = false;
    col->color = Color(1.0f, 0.0f, 0.0f);
    col->SetWorldPosX(app.GetHalfWidth() + col->scale.x + RANDOM->Float(600.0f, 3000.0f));
    col->SetWorldPosY(RANDOM->Float(-200.0f, 0.0f));
}

void Item::Release()
{
    Character::Release();
    SafeDelete(img);
}

void Item::Update()
{
    Character::Update();

    if (col->GetWorldPos().x + col->scale.x / 2 < -app.GetHalfWidth())
    {
        col->SetWorldPosX(app.GetHalfWidth() + col->scale.x + RANDOM->Float(600.0f, 3000.0f));
        col->SetWorldPosY(RANDOM->Float(-200.0f, 0.0f));
        col->isVisible = true;
        col->colOnOff = true;
    }
    img->Update();
}

void Item::LateUpdate()
{
}

void Item::Render()
{
    img->Render();
    Character::Render();
}

void Item::Spawn(const float diff, const int maxn)
{
    if (diff - col->GetWorldPos().x > 500.0f)
    {
        col->SetWorldPosX(diff + app.GetWidth() + RANDOM->Float(100.0f, 1000.0f));
        col->SetWorldPosY(RANDOM->Float(-200.0f, 0.0f));

        if (RANDOM->Int(0, 4) == 0)
        {
            col->colOnOff = true;
        }
        else
        {
            col->colOnOff = false;
        }
    }
}