#include "stdafx.h"

namespace Gungeon
{
    PlayerBullet::PlayerBullet()
    {
        col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        SetPos(DEFAULTSPAWN);

        scalar = 600.0f;
        damage = 2;

        float scaleFactor = 1.5f;
        col->scale.x = 19.0f * scaleFactor;
        col->scale.y = 19.0f * scaleFactor;
        idle = new ObImage(L"EnterTheGungeon/Player_0/Bullet_0.png");
        idle->scale = col->scale;
        idle->SetParentRT(*col);

        float bombScaleFactor = 1.5f;
        hitBomb = new Effect;
        hitBomb->idle = new ObImage(L"EnterTheGungeon/Player_0/HitBomb.png");
        hitBomb->idle->maxFrame.x = 4;
        hitBomb->idle->scale = Vector2(88.0f / 4.0f, 22.0f) * bombScaleFactor;
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