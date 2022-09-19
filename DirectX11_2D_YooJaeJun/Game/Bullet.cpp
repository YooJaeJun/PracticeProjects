#include "stdafx.h"

Bullet::Bullet()
{
    isFired = false;
    damage = 1;
    moveDir = Vector2(0.0f, 0.0f);
    timeRespawn = 0.0f;
}

void Bullet::Release()
{
    Character::Release();
    SafeDelete(idle);
}

void Bullet::Update()
{
    Character::Update();

    if (isFired)
    {
        Vector2 velocity = moveDir * scalar * DELTA;
        col->MoveWorldPos(velocity);
    }

    if (idle) idle->Update();
}

void Bullet::LateUpdate()
{
}

void Bullet::Render()
{
    if (idle) idle->Render();
    Character::Render();
}

void Bullet::Spawn(const Vector2& coord, const Vector2& fireDir)
{
    col->SetWorldPos(coord);
    col->rotation = Utility::DirToRadian(fireDir);
    moveDir = fireDir;
    isFired = true;
}

void Bullet::Hit(const float damage)
{
    if (false == isHit)
    {
        if (damage > 0)
        {
            col->colOnOff = false;
            col->isVisible = false;
            idle->isVisible = false;
            isFired = false;
        }
    }
}

void Bullet::Reload()
{
    col->colOnOff = true;
    col->isVisible = true;
    idle->isVisible = true;
    isFired = false;
    col->SetWorldPos(Vector2(2000.0f, 2000.0f));
}