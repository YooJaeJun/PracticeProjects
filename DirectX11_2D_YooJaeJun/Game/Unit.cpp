#include "stdafx.h"

Unit::Unit()
{
}

void Unit::Release()
{
	Character::Release();
	SafeDelete(idle);
	SafeDelete(walk);
	SafeDelete(roll);
	SafeDelete(hit);
	SafeDelete(die);
	SafeDelete(weapon);
}

void Unit::Update()
{
	Character::Update();

	weapon->col->rotation = Utility::DirToRadian(dest - weapon->col->GetWorldPos());

	if (state == State::die)
	{
		isHit = false;
		scalar = 0.0f;
		col->colOnOff = false;

		if (col) col->isVisible = false;
		if (idle) idle->isVisible = false;
		if (walk) walk->isVisible = false;
		if (roll) roll->isVisible = false;
		if (hit) hit->isVisible = false;
		weapon->col->isVisible = false;
		weapon->idle->isVisible = false;
	}
	else if (state == State::idle)
	{
		if (isHitAnim)
		{
			Color c = Color(0.5f, 0.5f, 0.5f, RANDOM->Float());
			if (idle) idle->color = c;
			if (walk) walk->color = c;
			if (roll) roll->color = c;
			if (hit)  hit->color = c;
			if (die)  die->color = c;

			col->SetWorldPosX(col->GetWorldPos().x + RANDOM->Float(-1.0f, 1.0f));
			col->SetWorldPosY(col->GetWorldPos().y + RANDOM->Float(-1.0f, 1.0f));

			idle->isVisible = false;
			hit->isVisible = true;

			if (TIMER->GetTick(timeHitAnim, 0.4f))	// 히트 애니용
			{
				Color c = Color(0.5f, 0.5f, 0.5f, 1.0f);
				if (idle) idle->color = c;
				if (walk) walk->color = c;
				if (roll) roll->color = c;
				if (hit)  hit->color = c;
				if (die)  die->color = c;

				hit->isVisible = false;
				idle->isVisible = true;

				isHitAnim = false;
			}
		}
		else
		{
			idle->isVisible = true;
			hit->isVisible = false;
		}
	}

	if (curHp <= 0)
	{
		curHp = 0;
		state = State::die;
	}

	if (weapon) weapon->Update();
	if (idle)	idle->Update();
	if (walk)	walk->Update();
	if (roll)	roll->Update();
	if (hit)	hit->Update();
	if (die)	die->Update();
}

void Unit::LateUpdate()
{
}

void Unit::Render()
{
	if (weapon) weapon->Render();
	if (idle)	idle->Render();
	if (walk)	walk->Render();
	if (roll)	roll->Render();
	if (hit)	hit->Render();
	if (die)	die->Render();
	Character::Render();
}


void Unit::Spawn()
{
	col->SetWorldPosX(0.0f);
	col->SetWorldPosY(0.0f);
}

void Unit::Hit(const int damage)
{
	if (false == isHit)
	{
		curHp -= damage;
		if (damage > 0)
		{
			isHit = true;
			isHitAnim = true;

			idle->isVisible = false;
			hit->isVisible = true;
			die->isVisible = false;

			hit->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
		}
	}
}

void Unit::Die()
{
	if (state != State::die)
	{
		state = State::die;
		col->scale.x = 0.0f;
		col->scale.y = 0.0f;

		idle->isVisible = false;
		hit->isVisible = false;
		die->isVisible = true;
	}
}