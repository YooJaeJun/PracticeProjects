#include "stdafx.h"

PlayerBullet::PlayerBullet()
{
    Init();
}

void PlayerBullet::Init()
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

    for (auto& elem : img) elem = new ObImage(L"PlayeBullet.png");

}

void PlayerBullet::Release()
{
    Character::Release();
    SafeDelete(idle);
    for(auto& elem : img) SafeDelete(elem);
}

void PlayerBullet::Update()
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

void PlayerBullet::LateUpdate()
{
}

void PlayerBullet::Render()
{
    idle->Render();
    Character::Render();
}

void PlayerBullet::Spawn()
{

}

void PlayerBullet::Shoot(const Vector2& coord)
{
    col->SetWorldPos(coord);
    isFired = true;
}

void PlayerBullet::Reload()
{
    isFired = false;
    col->SetWorldPos(Vector2(2000.0f, 2000.0f));
}