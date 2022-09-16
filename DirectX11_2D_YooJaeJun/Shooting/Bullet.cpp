#include "stdafx.h"

Bullet::Bullet()
{
    Init();
}

void Bullet::Init()
{
    Character::Init();
}

void Bullet::Release()
{
    Character::Release();
    SafeDelete(idle);
}

void Bullet::Update()
{
    idle->Update();

    if (isFired)
    {
        Vector2 velocity = UP * speed * DELTA;
        col->MoveWorldPos(velocity);
    }

    if (col->GetWorldPos().y > app.GetHeight() + 1000.0f)
    {
        Reload();
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

void Bullet::Spawn()
{
    // idle->scale.x = idleImgSize.x * scaleCoef.x;
    // idle->scale.y = idleImgSize.y * scaleCoef.y;
}

void Bullet::Shoot(const Vector2& coord)
{
}

void Bullet::Reload()
{
}