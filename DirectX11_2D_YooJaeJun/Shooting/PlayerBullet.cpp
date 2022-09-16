#include "stdafx.h"

PlayerBullet::PlayerBullet()
{
    Init();
}

void PlayerBullet::Init()
{
    Character::Init();
    idle = nullptr;

    col = new ObRect();
    col->scale = Vector2(68.0f / 7.0f, 48.0f * 0.8f);
    col->color = Color(1.0f, 1.0f, 1.0f);
    col->isFilled = false;
    col->SetWorldPos(Vector2(2000.0f, 2000.0f));

    isFired = false;
    speed = 300.0f;
    
    level = 0;
    idleImgSize = Vector2(50.0f, 50.0f);

    for (int i = 0; i < 4; i++)
    {
        img[i] = new ObImage(L"PlayerBullet.png");
        img[i]->scale.x = idleImgSize.x / 4;
        img[i]->scale.y = idleImgSize.y;
        img[i]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
        img[i]->SetParentRT(*col);
        img[i]->SetLocalPosY(20.0f);
    }
}

void PlayerBullet::Release()
{
    Character::Release();
    for(auto& elem : img) SafeDelete(elem);
}

void PlayerBullet::Update()
{
    Character::Update();

    if (isFired)
    {
        Vector2 velocity = UP * speed * DELTA;
        col->MoveWorldPos(velocity);
    }

    if (col->GetWorldPos().y > app.GetHeight() + 1000.0f)
    {
        Reload();
    }

    for (auto& elem : img) elem->Update();
}

void PlayerBullet::LateUpdate()
{
}

void PlayerBullet::Render()
{
    Character::Render();
    for (auto& elem : img) elem->Render();
}

void PlayerBullet::ChangeLevel(const int level)
{
    this->level = level;

    if (level == 0)
    {
        col->scale.x = 50.0f;
        damage = 10;
        img[0]->SetWorldPosX(0.0f);
        img[0]->isVisible = true;
        img[1]->isVisible = false;
        img[2]->isVisible = false;
        img[3]->isVisible = false;
    }
    else if (level == 1)
    {
        col->scale.x = 100.0f;
        damage = 15;
        img[0]->SetWorldPosX(-25.0f);
        img[1]->SetWorldPosX(25.0f);
        img[0]->isVisible = true;
        img[1]->isVisible = true;
        img[2]->isVisible = false;
        img[3]->isVisible = false;
    }
    else if (level == 2)
    {
        col->scale.x = 150.0f;
        damage = 20;
        img[0]->SetWorldPosX(-50.0f);
        img[1]->SetWorldPosX(0.0f);
        img[2]->SetWorldPosX(50.0f);
        img[0]->isVisible = true;
        img[1]->isVisible = true;
        img[2]->isVisible = true;
        img[3]->isVisible = false;
    }
    else
    {
        col->scale.x = 200.0f;
        damage = 25;
        img[0]->SetWorldPosX(-75.0f);
        img[1]->SetWorldPosX(-25.0f);
        img[2]->SetWorldPosX(25.0f);
        img[3]->SetWorldPosX(75.0f);
        img[0]->isVisible = true;
        img[1]->isVisible = true;
        img[2]->isVisible = true;
        img[3]->isVisible = true;
    }
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