#include "stdafx.h"

Background::Background()
{
}

void Background::Init()
{
    Character::Init();
    col = nullptr;
}

void Background::Release()
{
    Character::Release();
    SafeDelete(img);
}

void Background::Update()
{
    Character::Update();

    if (CAM->position.x - img->GetWorldPos().x > img->scale.x + app.GetHalfWidth())
    {
        img->SetWorldPosX(img->GetWorldPos().x + img->scale.x * 2);
    }
    img->Update();
}

void Background::LateUpdate()
{
}

void Background::Render()
{
    img->Render();
    Character::Render();
}

void Background::Spawn()
{
    img->pivot = OFFSET_L;
    img->scale.x = imgSize.x * app.GetWidth() / imgSize.x;
    img->scale.y = imgSize.y * app.GetWidth() / imgSize.x;
    img->SetWorldPosX(0.0f);
    img->SetWorldPosY(-app.GetHalfHeight() + imgSize.y * app.GetHeight() / imgSize.x);
}