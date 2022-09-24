#include "stdafx.h"

void Bar::Init()
{
    obj = new ObRect();
    obj->SetWorldPos(Vector2(0.0f, -300.0f));
    obj->scale = Vector2(100.0f, 15.0f);
    obj->color = Color(0.2f, 0.9f, 0.7f, 1.0f);
    obj->isVisible = true;
    obj->collider = Collider::rect;
    dir = Vector2(0.0f, 0.0f);
    scalar = 600.0f;
}

void Bar::Imprison(GameObject* other)
{
    if (obj->GetWorldPos().x > other->GetWorldPos().x)
    {
        obj->SetWorldPosX(other->GetWorldPos().x + other->scale.x / 2 + obj->scale.x / 2);
    }
    else
    {
        obj->SetWorldPosX(other->GetWorldPos().x - other->scale.x / 2 - obj->scale.x / 2);
    }
}
