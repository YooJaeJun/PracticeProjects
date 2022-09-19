#include "stdafx.h"

Boss::Boss()
{
	int idx = 0;
	float bulletCoef = 4.0f;

	for (auto& elem : bullet)
	{
		elem = new EnemyBullet;
		elem->col->scale.x = 8.0f * bulletCoef;
		elem->col->scale.y = 8.0f * bulletCoef;
		elem->idle = new ObImage(L"EnterTheGungeon/Enemy_0_Bullet.png");
		elem->idle->scale.x = 8.0f * bulletCoef;
		elem->idle->scale.y = 8.0f * bulletCoef;
		elem->idle->SetParentRT(*elem->col);
		elem->moveDir = Vector2(cos(idx * 4.0f * ToRadian), sin(idx * 4.0f * ToRadian));
		idx++;
	}

	curHp = maxHp = 1;
	scalar = 30.0f;
	timeFire = 0.0f;
	timeHit = 0.0f;
	isHit = false;
	isHitAnim = false;
	timeHitAnim = 0.0f;
}

void Boss::Release()
{
	Unit::Release();
	SafeDelete(hpGuage);
}

void Boss::Update()
{
	Unit::Update();

	col->MoveWorldPos(moveDir * scalar * DELTA);

	if (isHit)
	{
		if (TIMER->GetTick(timeHit, 0.01f))
		{
			isHit = false;
		}
	}

	if (state != State::die &&
		TIMER->GetTick(timeFire, 3.0f))
	{
		for (auto& elem : bullet)
		{
			if (elem->isFired) continue;

			elem->Spawn(Vector2(
				weapon->idle->GetWorldPivot().x + weapon->idle->scale.x / 2.0f,
				weapon->idle->GetWorldPivot().y),
				elem->moveDir);
			cout << elem->moveDir.x << ',' << elem->moveDir.y << '\n';
		}
	}

	idle->Update();

	for (auto& elem : bullet)
	{
		elem->Update();
	}

	hpGuage->img->scale.x = (float)curHp / maxHp * hpGuage->imgSize.x;
	hpGuage->img->uv.z = hpGuage->img->scale.x / hpGuage->imgSize.x;
	hpGuage->Update();
}

void Boss::LateUpdate()
{
	Unit::LateUpdate();
	for (auto& elem : bullet) if (elem) elem->LateUpdate();
	hpGuage->LateUpdate();
}

void Boss::Render()
{
	for (auto& elem : bullet) if (elem) elem->Render();
	hpGuage->Render();
	Unit::Render();
}
