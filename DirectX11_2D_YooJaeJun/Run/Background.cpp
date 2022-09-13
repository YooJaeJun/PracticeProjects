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
}