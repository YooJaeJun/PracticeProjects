#include "stdafx.h"

namespace Gungeon
{
    EnemyBullet::EnemyBullet()
    {
        col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        SetPos(DEFAULTSPAWN);

        scalar = 400.0f;
        damage = 1;

        float scaleFactor = 3.0f;
        col->scale = Vector2(8.0f, 8.0f) * scaleFactor;
        SetPos(DEFAULTSPAWN);
        idle = new ObImage(L"EnterTheGungeon/Enemy_0/Bullet_0.png");
        idle->isVisible = false;
        idle->scale = col->scale;
        idle->SetParentRT(*col);

        float bombScaleFactor = 1.5f;
        hitBomb = new Effect;
        hitBomb->idle = new ObImage(L"EnterTheGungeon/Enemy_0/HitBomb.png");
        hitBomb->idle->maxFrame.x = 4;
        hitBomb->idle->scale = Vector2(88.0f / 4.0f, 22.0f) * bombScaleFactor;
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