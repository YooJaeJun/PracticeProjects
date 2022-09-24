#include "stdafx.h"

PlayerBullet::PlayerBullet()
{
    col = new ObCircle();
    col->isFilled = false;
    col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
    SetPos(Vector2(2000.0f, 2000.0f));

    scalar = 600.0f;
    damage = 5;
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
    Bullet::LateUpdate();
}

void PlayerBullet::Render()
{
    Bullet::Render();
}