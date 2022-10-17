#include "stdafx.h"

namespace Gungeon
{
    BossBullet::BossBullet()
    {
        scalar = 400.0f;
        damage = 1;
        angle = 0.0f;
        atkAngle = 0.0f;

        float scaleFactor = 5.0f;
        col->scale = Vector2(8.0f, 8.0f) * scaleFactor;
        col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        SetPos(DEFAULTSPAWN);

        idle = new ObImage(L"EnterTheGungeon/boss_1/Bullet_0.png");
        idle->isVisible = false;
        idle->scale = col->scale;
        idle->SetParentRT(*col);

        float bombScaleFactor = 2.5f;
        hitBomb = new Effect;
        hitBomb->idle = new ObImage(L"EnterTheGungeon/boss_1/HitBomb.png");
        hitBomb->idle->maxFrame.x = 4;
        hitBomb->idle->scale = Vector2(88.0f / 4.0f, 22.0f) * bombScaleFactor;
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

    void BossBullet::Update(const bool notRotation)
    {
        Bullet::Update(notRotation);
    }

    void BossBullet::LateUpdate()
    {
    }

    void BossBullet::Render()
    {
        Bullet::Render();
    }

    void BossBullet::Reload()
    {
        Bullet::Reload();
    }
}