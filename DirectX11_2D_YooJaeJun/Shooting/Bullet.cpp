#include "stdafx.h"

Bullet::Bullet()
{
    Init();
}

void Bullet::Init()
{
    Character::Init();
    col = new ObRect();
    col->scale = Vector2(68.0f / 7.0f, 48.0f * 0.8f);
    col->color = Color(1.0f, 1.0f, 1.0f);
    col->isFilled = false;
    col->SetWorldPos(Vector2(2000.0f, 2000.0f));

    idle = new ObImage(L"PlayeBullet.png");
    idleImgSize = Vector2(68.0f, 48.0f);
    idle->maxFrame.x = 4;
    scaleCoef = Vector2(2.0f, 2.0f);
    idle->scale.x = idleImgSize.x / idle->maxFrame.x * scaleCoef.x;
    idle->scale.y = idleImgSize.y * scaleCoef.y;
    idle->uv = Vector4(0.0f, 0.0f, 1.0f / idle->maxFrame.x, 1.0f);
    idle->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
    idle->SetParentRT(*col);
    idle->SetLocalPosY(20.0f);

    isFired = false;
    speed = 400.0f;
}

void Bullet::Release()
{
    Character::Release();
    SafeDelete(idle);
}

void Bullet::Update()
{
    Character::Update();
    idle->Update();

    if (isFired)
    {
        Vector2 velocity = UP * speed * DELTA;
        col->MoveWorldPos(velocity);
    }

    if (col->GetWorldPos().y > app.GetHeight() + 1000.0f)
    {
        Reload();
    }
}

void Bullet::LateUpdate()
{
}

void Bullet::Render()
{
    idle->Render();
    Character::Render();
}

void Bullet::Spawn()
{
    // idle->scale.x = idleImgSize.x * scaleCoef.x;
    // idle->scale.y = idleImgSize.y * scaleCoef.y;
}

void Bullet::Shoot(const Vector2& coord)
{
    col->SetWorldPos(coord);
    isFired = true;
}

void Bullet::Reload()
{
    isFired = false;
    col->SetWorldPos(Vector2(2000.0f, 2000.0f));
}