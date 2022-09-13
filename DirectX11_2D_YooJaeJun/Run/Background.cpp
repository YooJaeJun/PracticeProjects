#include "stdafx.h"

Background::Background()
{
    Init();
}

void Background::Init()
{
    Character::Init();
    col = nullptr;
}

void Background::Release()
{
    Character::Release();
    SafeDelete(idle);
}

void Background::Update()
{
    Character::Update();

    if (CAM->position.x - idle->GetWorldPos().x > idle->scale.x)
    {
        idle->MoveWorldPos(Vector2(idle->scale.x * 2, 0.0f));
    }
    idle->Update();
}

void Background::LateUpdate()
{
}

void Background::Render()
{
    idle->Render();
    Character::Render();
}

void Background::Spawn()
{
    idle->scale.x = imgSize.x * app.GetWidth() / imgSize.x;
    idle->scale.y = imgSize.y * app.GetHeight() / imgSize.y;
    idle->SetWorldPosX(CAM->position.x + 0.0f);
}