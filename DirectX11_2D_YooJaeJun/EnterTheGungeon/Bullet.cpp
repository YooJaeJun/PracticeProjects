#include "stdafx.h"

namespace Gungeon
{
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
        hitBomb->Release();
    }

    void Bullet::Update()
    {
        Character::Update();

        if (isFired)
        {
            moveDir.Normalize();
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

    void Bullet::Spawn(const Vector2& coord, const Vector2& fireDir)
    {
        SetPos(coord);
        col->rotation = Utility::DirToRadian(fireDir);
        moveDir = fireDir;
        isFired = true;
    }

    void Bullet::Hit(const float damage)
    {
        Reload();
        hitBomb->Spawn(idle->GetWorldPos());
    }

    void Bullet::Reload()
    {
        col->colOnOff = true;
        col->isVisible = true;
        SetPos(Vector2(defaultSpawnPos, defaultSpawnPos));
        idle->isVisible = true;
        isFired = false;
    }
}