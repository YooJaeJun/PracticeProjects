#include "stdafx.h"

Unit::Unit()
{
    Init();
}

void Unit::Init()
{
    gravity = 600.0f * DELTA;
    velocity = Vector2(0.0f, 0.0f);
    hitEffectTime = 0.0f;
    state = (int)estate::alive;
    onGround = true;
}

bool Unit::HitFrom(const float damage)
{
    state = (int)estate::hit;
    return true;
}

void Unit::Update()
{
    if (hitbox->isVisible)
    {
        lastPos = hitbox->GetWorldPos();
    }
}

bool Unit::LateUpdate()
{
    return false;
}

void Unit::Render()
{
}
