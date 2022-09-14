#include "stdafx.h"

Background::Background()
{
    Init();
}

void Background::Init()
{
    Character::Init();
    col = nullptr;
    idle = new ObImage(L"bg.png");
    idleImgSize = Vector2(224.0f, 2144.0f);
    idle->space = SPACE::SCREEN;
    scaleCoef = Vector2(2.0f, 2.0f);
    idle->scale.x = idleImgSize.x * scaleCoef.x;
    idle->scale.y = idleImgSize.y * scaleCoef.y;
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
    idle->scale.x = idleImgSize.x * scaleCoef.x;
    idle->scale.y = idleImgSize.y * scaleCoef.y;
}