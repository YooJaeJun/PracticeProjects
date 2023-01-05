#include "stdafx.h"

EnemyBullet::EnemyBullet()
{
    Init();
}

void EnemyBullet::Init()
{
    Character::Init();

    col = new ObRect();
    col->scale = Vector2(68.0f / 7.0f, 48.0f * 0.8f);
    col->color = Color(1.0f, 1.0f, 1.0f);
    col->isFilled = false;
    col->SetWorldPos(Vector2(2000.0f, 2000.0f));
}

void EnemyBullet::Release()
{
    Character::Release();
}

void EnemyBullet::Update()
{
    Character::Update();
}

void EnemyBullet::LateUpdate()
{
}

void EnemyBullet::Render()
{
    Character::Render();
}