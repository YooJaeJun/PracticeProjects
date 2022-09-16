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
    damage = 1.0f;
    idleImgSize = Vector2(68.0f, 48.0f);

    for (int i = 0; i < 4; i++)
    {
        img[i] = new ObImage(L"PlayerBullet.png");
        img[i]->maxFrame.x = 4;
        img[i]->scale.x = idleImgSize.x / img[i]->maxFrame.x;
        img[i]->scale.y = idleImgSize.y;
        img[i]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
        img[i]->SetParentRT(*col);
        img[i]->SetLocalPosY(20.0f);
    }
}

void PlayerBullet::Release()
{
    Bullet::Release();
    for(auto& elem : img) SafeDelete(elem);
}

void PlayerBullet::Update()
{
    Bullet::Update();
    for (auto& elem : img) elem->Update();
}

void PlayerBullet::LateUpdate()
{
}

void PlayerBullet::Render()
{
    Bullet::Render();
    for (auto& elem : img) elem->Render();
}

void PlayerBullet::ChangeLevel(const int level)
{
    this->level = level;

    if (level == 0)
    {
        col->scale.x = 17.0f;
        damage = 1.0f;
        img[0]->SetLocalPosX(0.0f);
        img[0]->isVisible = true;
        img[1]->isVisible = false;
        img[2]->isVisible = false;
        img[3]->isVisible = false;
    }
    else if (level == 1)
    {
        col->scale.x = 34.0f;
        damage = 1.5f;
        img[0]->SetLocalPosX(-8.5f);
        img[1]->SetLocalPosX(8.5f);
        img[0]->isVisible = true;
        img[1]->isVisible = true;
        img[2]->isVisible = false;
        img[3]->isVisible = false;
    }
    else if (level == 2)
    {
        col->scale.x = 51.0f;
        damage = 2.0f;
        img[0]->SetLocalPosX(-17.0f);
        img[1]->SetLocalPosX(0.0f);
        img[2]->SetLocalPosX(17.0f);
        img[0]->isVisible = true;
        img[1]->isVisible = true;
        img[2]->isVisible = true;
        img[3]->isVisible = false;
    }
    else
    {
        col->scale.x = 68.0f;
        damage = 2.5f;
        img[0]->SetLocalPosX(-25.5f);
        img[1]->SetLocalPosX(-8.5f);
        img[2]->SetLocalPosX(8.5f);
        img[3]->SetLocalPosX(25.5f);
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
    col->SetWorldPos(Vector2(2000.0f, 2000.0f));
    isFired = false;
}