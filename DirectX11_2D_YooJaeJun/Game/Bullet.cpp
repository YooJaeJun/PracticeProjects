#include "stdafx.h"

Bullet::Bullet()
{
    isFired = false;
    damage = 0;
    moveDir = Vector2(0.0f, 0.0f);
}

void Bullet::Release()
{
    Character::Release();
}

void Bullet::Update()
{
    if (isFired)
    {
        Vector2 velocity = moveDir * scalar * DELTA;
        col->MoveWorldPos(velocity);
    }

    Character::Update();
}

void Bullet::LateUpdate()
{
}

void Bullet::Render()
{
    Character::Render();
}