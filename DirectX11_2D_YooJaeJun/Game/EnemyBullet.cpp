#include "stdafx.h"

EnemyBullet::EnemyBullet()
{
    col = new ObCircle();
    col->isFilled = false;
    col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
    col->SetWorldPos(Vector2(2000.0f, 2000.0f));

    scalar = 500.0f;
    damage = 1;
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
        if (TIMER->GetTick(timeRespawn, 3.0f))
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