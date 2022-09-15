#include "stdafx.h"

Airplane::Airplane()
{
	Init();
}

void Airplane::Init()
{
	Character::Init();
	type = PlaneType::PLAYER;
	key = 0.0f;
	moveDir = Vector2(0.0f, 0.0f);
	speed = 400.0f;
	hit = nullptr;
	die = nullptr;
	state = PlaneState::RUN;
	timeShoot = 0.0f;
	isHit = false;
	timeHit = 0.0f;
	isHitAnim = false;
	timeHitAnim = 0.0f;
	speedOrigin = 0.0f;

	for (auto& elem : bomb) elem = nullptr;
}

void Airplane::Release()
{
	Character::Release();
	SafeDelete(idle);
	for (auto& elem : bomb) SafeDelete(elem);
}

void Airplane::Update()
{
	if (isHit)
	{
		idle->color = Color(0.5f, 0.5f, 0.5f, RANDOM->Float());
		if (TIMER->GetTick(timeHit, 1.0f))
		{
			idle->color = Color(0.5f, 0.5f, 0.5f, 1.0f);
			isHit = false;
		}
	}

	if (col) col->Update();
	if (idle) idle->Update();
	if (hit) hit->Update();
	if (die) die->Update();
}

void Airplane::LateUpdate()
{
}

void Airplane::Render()
{
	if (idle) idle->Render();
	if (hit) hit->Render();
	if (die) die->Render();
	if (col) col->Render();
}


void Airplane::Spawn()
{
	// col->SetWorldPosX(0.0f);
	// col->SetWorldPosY(-app.GetHalfHeight() + 200.0f);
}

void Airplane::Hit(const float damage)
{
	isHit = true;
	curHp -= 1;
	if (curHp <= 0)
	{
		curHp = 0;
		state = PlaneState::DIE;
	}
}

void Airplane::Die()
{
	state = PlaneState::DIE;
	for (auto& elem : bomb)
	{
		elem->isVisible = true;
	}
}
