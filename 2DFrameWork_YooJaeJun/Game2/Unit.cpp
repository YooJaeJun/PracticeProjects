#include "stdafx.h"

Unit::Unit()
{
    Init();
}

void Unit::Init()
{
    hitbox.SetWorldPos(Vector2(2000.0f, 2000.0f));
    hitbox.scale = Vector2(80.0f, 80.0f);
    hitbox.rotation = 30.0f * ToRadian;
    hitbox.isFilled = true;
    hitbox.isAxis = false;
    hitbox.color = Color(0.2f, 0.2f, 0.8f, 1.0f);
    hitbox.pivot = OFFSET_N;

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
    lastPos = hitbox.GetWorldPos();
    hitbox.Update();
}

bool Unit::LateUpdate()
{
    return false;
}

void Unit::Render()
{
    hitbox.Render();
}
