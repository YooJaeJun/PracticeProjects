#include "stdafx.h"

namespace Gungeon
{
    BossBullet::BossBullet()
    {
        col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        SetPos(DEFAULTSPAWN);

        scalar = 400.0f;
        damage = 1;

        float bulletCoef = 4.0f;
        col = new ObCircle;
        col->scale = Vector2(8.0f, 8.0f) * bulletCoef;
        col->isFilled = false;
        col->SetWorldPos(DEFAULTSPAWN);
        idle = new ObImage(L"EnterTheGungeon/Boss_0/Bullet_0.png");
        idle->scale = col->scale;
        idle->SetParentRT(*col);

        float hitBombScaleCoef = 2.5f;
        hitBomb = new Effect;
        hitBomb->idle = new ObImage(L"EnterTheGungeon/Boss_0/HitBomb.png");
        hitBomb->idle->maxFrame.x = 4;
        hitBomb->idle->scale = Vector2(88.0f / 4.0f, 22.0f) * hitBombScaleCoef;
        hitBomb->idle->isVisible = false;
    }

    void BossBullet::Release()
    {
        Bullet::Release();
    }

    void BossBullet::Update()
    {
        Bullet::Update();
    }

    void BossBullet::LateUpdate()
    {
    }

    void BossBullet::Render()
    {
        Bullet::Render();
    }

    void BossBullet::Spawn(const Vector2& coord)
    {
        SetPos(coord);
        isFired = true;
    }

    void BossBullet::Reload()
    {
        Bullet::Reload();
    }
}