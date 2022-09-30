#include "stdafx.h"

namespace Gungeon
{
    PlayerBullet::PlayerBullet()
    {
        col = new ObCircle();
        col->isFilled = false;
        col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        SetPos(Vector2(defaultSpawnPos, defaultSpawnPos));

        scalar = 600.0f;
        damage = 10;

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