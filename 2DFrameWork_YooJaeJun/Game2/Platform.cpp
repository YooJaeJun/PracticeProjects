#include "stdafx.h"

void Platform::Init()
{
    hitbox.pivot = OFFSET_LT;
    hitbox.color = Color(0.2f, 0.0f, 0.0f, 1.0f);
    hitbox.scale = Vector2(app.GetHalfWidth() - 200.0f, 70.0f);
    hitbox.SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight() + hitbox.scale.y));
}

void Platform::Update()
{
    hitbox.Update();
}

void Platform::Render()
{
    hitbox.Render();
}
