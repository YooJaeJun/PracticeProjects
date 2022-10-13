#include "stdafx.h"

Enemy::Enemy()
{
	Init();
}

void Enemy::Init()
{
	Character::Init();
	Airplane::Init();
	type = PlaneType::enemy;
	maxHp = curHp = 50;

	col = new ObRect();
	col->scale.x = 126.0f;
	col->scale.y = 62.0f;
	col->SetWorldPos(Vector2(0.0f, 300.0f));
	col->color = Color(1.0f, 1.0f, 1.0f);
	col->isFilled = false;
	// col->rotation = -180.0f * ToRadian;

	idle = new ObImage(L"monster_wave.png");
	idleImgSize = Vector2(126.0f, 62.0f);
	idle->maxFrame.x = 1;
	idle->scale.x = idleImgSize.x / idle->maxFrame.x;
	idle->scale.y = idleImgSize.y;
	idle->uv = Vector4(0.0f, 0.0f, 1.0f / idle->maxFrame.x, 1.0f);
	idle->SetParentRT(*col);

	hpGuage = new UI;
	hpGuage->idle = new ObImage(L"Cookie/Time.png");
	hpGuage->idleImgSize.x = 242.0f;
	hpGuage->idleImgSize.y = 86.0f;
	hpGuage->idle->scale.x = hpGuage->idleImgSize.x * 0.5f;
	hpGuage->idle->scale.y = hpGuage->idleImgSize.y * 0.5f;
	hpGuage->idle->SetWorldPosX(-hpGuage->idleImgSize.x * 0.5f);
	hpGuage->idle->SetWorldPosY(app.GetHalfHeight() - hpGuage->idleImgSize.y * 0.5f);
	hpGuage->idle->pivot = OFFSET_L;
	hpGuage->idle->space = Space::screen;

	for (auto& elem : bomb)
	{
		elem = new ObImage(L"bomb.png");
		elem->isVisible = false;
		elem->maxFrame.x = 4.0f;
		elem->scale.x = 128.0f / elem->maxFrame.x;
		elem->scale.y = 32.0f;
		elem->ChangeAnim(AnimState::loop, 0.1f);
		elem->SetParentT(*col);
	}
	timeBombBetween = 0.0f;
}

void Enemy::Release()
{
	Character::Release();
	SafeDelete(idle);
	SafeDelete(hpGuage);
}

void Enemy::Update()
{
	Airplane::Update();

	hpGuage->idle->scale.x = (float)curHp / maxHp * hpGuage->idleImgSize.x;
	hpGuage->idle->uv.z = hpGuage->idle->scale.x / hpGuage->idleImgSize.x;
	hpGuage->Update();

	if (state == PlaneState::die)
	{
		isHit = false;
		idle->color.w = 0.2f;
		for (auto& elem : bomb)
		{
			if (TIMER->GetTick(timeBombBetween, 0.3f))
			{
				elem->SetLocalPosX(RANDOM->Float(-50.0f, 50.0f));
				elem->SetLocalPosY(RANDOM->Float(-50.0f, 50.0f));
				elem->isVisible = true;
			}
		}
		if (TIMER->GetTick(timeHit, 2.5f))
		{
			state = PlaneState::run;
			col->SetWorldPos(Vector2(2000.0f, 2000.0f));
			for (auto& elem : bomb)
			{
				elem->isVisible = false;
				elem->SetWorldPos(Vector2(2000.0f, 2000.0f));
			}
		}
	}
	for (auto& elem : bomb) elem->Update();
}

void Enemy::LateUpdate()
{
}

void Enemy::Render()
{
	Airplane::Render();
	hpGuage->Render();
	for (auto& elem : bomb) elem->Render();
}
