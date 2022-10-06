#include "stdafx.h"

namespace Gungeon
{
    PlayerBullet::PlayerBullet()
    {
        col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        SetPos(DEFAULTSPAWN);

        scalar = 600.0f;
        damage = 10;

        float bulletCoef = 1.5f;
        col->scale.x = 19.0f * bulletCoef;
        col->scale.y = 19.0f * bulletCoef;
        idle = new ObImage(L"EnterTheGungeon/Player_0/Bullet_0.png");
        idle->scale = col->scale * 0.8f;
        idle->SetParentRT(*col);

        float hitBombScaleCoef = 1.5f;
        hitBomb = new Effect;
        hitBomb->idle = new ObImage(L"EnterTheGungeon/Player_0/HitBomb.png");
        hitBomb->idle->maxFrame.x = 4;
        hitBomb->idle->scale = Vector2(88.0f / 4.0f, 22.0f) * hitBombScaleCoef;
        hitBomb->idle->isVisible = false;
    }

    void PlayerBullet::Release()
    {
        Bullet::Release();
    }

    void PlayerBullet::Update()
    {
        Bullet::Update();
    }

    void PlayerBullet::LateUpdate()
    {
    }

    void PlayerBullet::Render()
    {
        Bullet::Render();
    }
}