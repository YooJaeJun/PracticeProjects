#include "stdafx.h"

PlayerBullet::PlayerBullet()
{
    col = new ObCircle();
    col->isFilled = false;
    col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
    col->SetWorldPos(Vector2(2000.0f, 2000.0f));

    scalar = 500.0f;
    damage = 1;
}

void PlayerBullet::Release()
{
    Bullet::Release();
}

void PlayerBullet::Update()
{
    Bullet::Update();

    if (isFired)
    {
        if (TIMER->GetTick(timeRespawn, 2.0f))
        {
            Reload();
        }
    }
}

void PlayerBullet::LateUpdate()
{
    Bullet::LateUpdate();
}

void PlayerBullet::Render()
{
    Bullet::Render();
}