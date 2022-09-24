#include "stdafx.h"

Room::Room()
{
    Init();
}

void Room::Init()
{
    col = new ObRect();
    col->scale.x = RANDOM->Float(50.0f, 100.0f);
    col->scale.y = RANDOM->Float(50.0f, 100.0f);
    col->SetWorldPosX(RANDOM->Float(-50.0f, 50.0f));
    col->SetWorldPosY(RANDOM->Float(-50.0f, 50.0f));
    col->isFilled = false;
    col->color = Color(RANDOM->Float(0.0f, 1.0f), RANDOM->Float(0.0f, 1.0f), RANDOM->Float(0.0f, 1.0f));
    col->collider = Collider::rect;

    selected = false;
}

void Room::Release()
{
    SafeDelete(col);
}

void Room::Update()
{
    col->Update();
}

void Room::LateUpdate()
{
}

void Room::Render()
{
    col->Render();
}