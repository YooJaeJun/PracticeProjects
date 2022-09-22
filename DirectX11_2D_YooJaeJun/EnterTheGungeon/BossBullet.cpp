#include "stdafx.h"

BossBullet::BossBullet()
{
    col = new ObCircle();
    col->isFilled = false;
    col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
    col->SetWorldPos(Vector2(2000.0f, 2000.0f));

    scalar = 400.0f;
    damage = 1;
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
    col->SetWorldPos(coord);
    isFired = true;
}

void BossBullet::Reload()
{
    Bullet::Reload();
}