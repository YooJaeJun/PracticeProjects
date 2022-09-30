#include "stdafx.h"

namespace Gungeon
{
    EnemyBullet::EnemyBullet()
    {
        col = new ObCircle();
        col->isFilled = false;
        col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        SetPos(Vector2(defaultSpawnPos, defaultSpawnPos));

        scalar = 500.0f;
        damage = 1;

        float hitBombScaleCoef = 1.5f;
        hitBomb = new Effect;
        hitBomb->idle = new ObImage(L"EnterTheGungeon/Enemy_0/HitBomb.png");
        hitBomb->idle->maxFrame.x = 4;
        hitBomb->idle->scale = Vector2(88.0f / 4.0f, 22.0f) * hitBombScaleCoef;
        hitBomb->idle->isVisible = false;
    }

    void EnemyBullet::Release()
    {
        Bullet::Release();
    }

    void EnemyBullet::Update()
    {
        Bullet::Update();

        if (isFired)
        {
            if (TIMER->GetTick(timeRespawn, 4.0f))
            {
                Reload();
            }
        }
    }

    void EnemyBullet::LateUpdate()
    {
    }

    void EnemyBullet::Render()
    {
        Bullet::Render();
    }
}