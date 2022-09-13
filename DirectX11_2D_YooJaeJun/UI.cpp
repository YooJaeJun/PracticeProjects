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
    SafeDelete(idle);
}

void UI::Update()
{
    Character::Update();
    idle->Update();
}

void UI::LateUpdate()
{
}

void UI::Render()
{
    idle->Render();
    Character::Render();
}

void UI::Spawn(const Anchor anchor, const float coefX, const float coefY)
{
    switch (anchor)
    {
    case Anchor::LEFTTOP:
        idle->SetWorldPos(Vector2(-app.GetHalfWidth() + coefX, app.GetHalfHeight() + coefY));
        break;
    case Anchor::LEFTBOTTOM:
        idle->SetWorldPos(Vector2(-app.GetHalfWidth() + coefX, -app.GetHalfHeight() + coefY));
        break;
    case Anchor::RIGHTBOTTOM:
        idle->SetWorldPos(Vector2(app.GetHalfWidth() + coefX, -app.GetHalfHeight() + coefY));
        break;
    }
}

bool UI::DownGauge()
{
    if (idle->scale.x <= 0.0f)
    {
        idle->scale.x = 0.0f;
        idle->uv.z = 0.0f;
        return false;
    }
    else
    {
        idle->scale.x -= imgSize.x / 50.0f * DELTA;
        idle->uv.z = idle->scale.x / imgSize.x;
    }
    return true;
}

void UI::Hit(const float damage)
{
    idle->scale.x = min(idle->scale.x - damage, imgSize.x);
    idle->uv.z = min(idle->scale.x / imgSize.x, 1.0f);
}