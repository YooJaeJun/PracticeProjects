#include "stdafx.h"

namespace Gungeon
{
    Bullet::Bullet()
    {
        col = new ObCircle();
        col->isFilled = false;

        isFired = false;
        damage = 1;
        moveDir = Vector2(0.0f, 0.0f);
        timeRespawn = 0.0f;
    }

    void Bullet::Release()
    {
        Character::Release();
        SafeDelete(idle);
        hitBomb->Release();
    }

    void Bullet::Update()
    {
        if (isFired)
        {
            Character::Update();

            moveDir.Normalize();
            Vector2 velocity = moveDir * scalar * DELTA;
            col->MoveWorldPos(velocity);
        }

        idle->Update();
        hitBomb->Update();
    }

    void Bullet::Update(const bool notRotation)
    {
        if (isFired)
        {
            Character::Update(notRotation);

            Vector2 velocity = moveDir * scalar * DELTA;
            col->MoveWorldPos(velocity);
        }

        idle->Update();
        hitBomb->Update();
    }

    void Bullet::LateUpdate()
    {
    }

    void Bullet::Render()
    {
        idle->Render(); // RENDER->push(idle);
        Character::Render();
        hitBomb->Render();
    }

    void Bullet::Spawn(const Vector2& coord)
    {
        SetPos(coord);
        isFired = true;
        idle->isVisible = true;
    }

    void Bullet::Spawn(const Vector2& coord, const Vector2& fireDir)
    {
        Spawn(coord);
        col->rotation = Utility::DirToRadian(fireDir);
        moveDir = fireDir;
    }

    void Bullet::Hit(const float damage)
    {
        hitBomb->Spawn(idle->GetWorldPos());
        Reload();
    }

    void Bullet::Reload()
    {
        SetPos(DEFAULTSPAWN);
        Update();
        idle->isVisible = false;
        isFired = false;
    }
}