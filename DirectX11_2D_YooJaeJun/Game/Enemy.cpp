#include "stdafx.h"

Enemy::Enemy()
{
	float bulletCoef = 3.0f;

	for (auto& elem : bullet)
	{
		elem = new EnemyBullet;
		elem->col->scale.x = 8.0f * bulletCoef;
		elem->col->scale.y = 8.0f * bulletCoef;
		elem->idle = new ObImage(L"EnterTheGungeon/Enemy_0/Bullet_0.png");
		elem->idle->scale.x = 8.0f * bulletCoef;
		elem->idle->scale.y = 8.0f * bulletCoef;
		elem->idle->SetParentRT(*elem->col);
	}

	curHp = maxHp = 1;
	scalar = 30.0f;
	timeFire = 0.0f;
	timeHit = 0.0f;
	isHit = false;
	isHitAnim = false;
	timeHitAnim = 0.0f;
}

void Enemy::Release()
{
	Unit::Release();
	for (auto& elem : bullet) elem->Release();
}

void Enemy::Update()
{
	Unit::Update();

	moveDir = dest - col->GetWorldPos();
	moveDir.Normalize();
	col->MoveWorldPos(moveDir * scalar * DELTA);

	if (isHit)
	{
		if (TIMER->GetTick(timeHit, 0.01f))
		{
			isHit = false;
		}
	}

	if (state != State::die && 
		TIMER->GetTick(timeFire, 1.0f))
	{
		for (auto& elem : bullet)
		{
			if (elem->isFired) continue;

			elem->Spawn(firePos->GetWorldPos(), moveDir);
			break;
		}
	}

	for (auto& elem : bullet) if (elem) elem->Update();
}

void Enemy::LateUpdate()
{
	Unit::LateUpdate();
	for (auto& elem : bullet) if (elem) elem->LateUpdate();
}

void Enemy::Render()
{
	for (auto& elem : bullet) if (elem) elem->Render();
	Unit::Render();
}
