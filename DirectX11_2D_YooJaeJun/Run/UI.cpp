#include "stdafx.h"

UI::UI()
{
    Init();
}

void UI::Init()
{
    Character::Init();
    col = nullptr;
}

void UI::Release()
{
    Character::Release();
    SafeDelete(img);
}

void UI::Update()
{
    Character::Update();
    img->Update();
}

void UI::LateUpdate()
{
}

void UI::Render()
{
    img->Render();
    Character::Render();
}