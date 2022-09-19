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
    SafeDelete(img);
    Bullet::Release();
}

void PlayerBullet::Update()
{
    img->Update();
    Bullet::Update();
}

void PlayerBullet::LateUpdate()
{
}

void PlayerBullet::Render()
{
    img->Render();
    Bullet::Render();
}

void PlayerBullet::Spawn(const Vector2& coord, const Vector2 fireDir)
{
    col->SetWorldPos(coord);
    col->rotation = Utility::DirToRadian(fireDir);
    moveDir = fireDir;
    isFired = true;
}

void PlayerBullet::Reload()
{
    col->SetWorldPos(Vector2(2000.0f, 2000.0f));
    isFired = false;
}