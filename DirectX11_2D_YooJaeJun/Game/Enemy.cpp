#include "stdafx.h"

Enemy::Enemy()
{
	col = new ObRect();
	col->isFilled = false;
	col->color = Color(1.0f, 1.0f, 1.0f);
	// col->rotation = -180.0f * ToRadian;

	hpGuage = new UI;
	hpGuage->img = new ObImage(L"Cookie/Time.png");
	hpGuage->imgSize.x = 242.0f;
	hpGuage->imgSize.y = 86.0f;
	hpGuage->img->scale.x = hpGuage->imgSize.x * 0.5f;
	hpGuage->img->scale.y = hpGuage->imgSize.y * 0.5f;
	hpGuage->img->SetWorldPosX(-hpGuage->imgSize.x * 0.5f);
	hpGuage->img->SetWorldPosY(app.GetHalfHeight() - hpGuage->imgSize.y * 0.5f);
	hpGuage->img->pivot = OFFSET_L;
	hpGuage->img->space = SPACE::SCREEN;

	for (auto& elem : bullet)
	{
		elem = new EnemyBullet;
		elem->img = new ObImage(L"EnterTheGungeon/Enemy_0_Bullet.png");
		elem->img->scale.x = 8.0f;
		elem->img->scale.y = 8.0f;
		elem->img->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		elem->img->SetParentRT(*col);
		elem->img->SetLocalPosY(20.0f);
	}

	scalar = 30.0f;
	timeFire = 0.0f;
	timeHit = 0.0f;
	isHit = false;
	isHitAnim = false;
	timeHitAnim = 0.0f;
}

void Enemy::Release()
{
	SafeDelete(idle);
	SafeDelete(hpGuage);
	for (auto& elem : bullet) elem->Release();
	Character::Release();
}

void Enemy::Update()
{
	hpGuage->img->scale.x = (float)curHp / maxHp * hpGuage->imgSize.x;
	hpGuage->img->uv.z = hpGuage->img->scale.x / hpGuage->imgSize.x;
	hpGuage->Update();

	if (state == State::die)
	{
		isHit = false;
		idle->color.w = 0.2f;
		if (TIMER->GetTick(timeHit, 2.5f))
		{
			state = State::idle;
			col->SetWorldPos(Vector2(2000.0f, 2000.0f));
		}
	}
	idle->Update();

	for (auto& elem : bullet) elem->Update();
	Character::Update();
}

void Enemy::LateUpdate()
{
	for (auto& elem : bullet) elem->LateUpdate();
}

void Enemy::Render()
{
	hpGuage->Render();
	idle->Render();
	for (auto& elem : bullet) elem->Render();
	Character::Render();
}

void Enemy::Move(const Vector2& dir)
{
	col->MoveWorldPos(dir * scalar * DELTA);
}
