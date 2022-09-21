#include "stdafx.h"

Unit::Unit()
{
	state = State::idle;
	timeFire = 0.0f;
	timeReload = 0.0f;
	timeHit = 0.0f;
	isHit = false;
	isHitAnim = 0.0f;
	timeHitAnim = 0.0f;
	godMode = false;
}

void Unit::Release()
{
	Character::Release();
	for(auto& elem : idle) SafeDelete(elem);
	for(auto& elem : walk) SafeDelete(elem);
	for(auto& elem : roll) SafeDelete(elem);
	SafeDelete(hit);
	SafeDelete(die);
	SafeDelete(weapon);
}

void Unit::Update()
{
	Character::Update();

	// normalize 고려
	if (almost_equal_float(moveDir.x, 0.707107f) && almost_equal_float(moveDir.y, 0.707107f))
	{
		curDir = backRightDiag;
	}
	else if (almost_equal_float(moveDir.x, -0.707107f) && almost_equal_float(moveDir.y, 0.707107f))
	{
		curDir = backLeftDiag;
	}
	else if (almost_equal_float(moveDir.x, -0.707107f) && almost_equal_float(moveDir.y, -0.707107f))
	{
		curDir = leftDiag;
	}
	else if (almost_equal_float(moveDir.x, 0.707107f) && almost_equal_float(moveDir.y, -0.707107f))
	{
		curDir = rightDiag;
	}
	else if (moveDir.x == 1.0f)
	{
		curDir = rightSide;
	}
	else if (moveDir.x == -1.0f)
	{
		curDir = leftSide;
	}
	else if (moveDir.y == 1.0f)
	{
		curDir = back;
	}
	else
	{
		curDir = beforeCurDir;
	}

	weapon->col->rotation = Utility::DirToRadian(dest - weapon->col->GetWorldPos());

	if (state == State::die)
	{
		isHit = false;
		scalar = 0.0f;
		col->colOnOff = false;

		if (col) col->isVisible = false;
		if (idle[curDir]) idle[curDir]->isVisible = false;
		if (walk[curDir]) walk[curDir]->isVisible = false;
		if (roll[curDir]) roll[curDir]->isVisible = false;
		if (hit) hit->isVisible = false;
		weapon->col->isVisible = false;
		weapon->idle->isVisible = false;
	}
	else if (state == State::idle)
	{
		if (isHitAnim)
		{
			Color c = Color(0.5f, 0.5f, 0.5f, RANDOM->Float());
			if (idle[curDir]) idle[curDir]->color = c;
			if (walk[curDir]) walk[curDir]->color = c;
			if (roll[curDir]) roll[curDir]->color = c;
			if (hit)  hit->color = c;
			if (die)  die->color = c;

			col->SetWorldPosX(col->GetWorldPos().x + RANDOM->Float(-1.0f, 1.0f));
			col->SetWorldPosY(col->GetWorldPos().y + RANDOM->Float(-1.0f, 1.0f));

			idle[curDir]->isVisible = false;
			hit->isVisible = true;

			if (TIMER->GetTick(timeHitAnim, 0.4f))	// 히트 애니용
			{
				Color c = Color(0.5f, 0.5f, 0.5f, 1.0f);
				if (idle[curDir]) idle[curDir]->color = c;
				if (walk[curDir]) walk[curDir]->color = c;
				if (roll[curDir]) roll[curDir]->color = c;
				if (hit)  hit->color = c;
				if (die)  die->color = c;

				hit->isVisible = false;
				idle[curDir]->isVisible = true;

				isHitAnim = false;
			}
		}
		else
		{
			idle[curDir]->isVisible = true;
			if (idle[curDir]->color.w == 1.0f) idle[curDir]->color.w = 1.0f;
			if (walk[curDir]->color.w == 1.0f) walk[curDir]->color.w = 1.0f;
			hit->isVisible = false;
		}
	}

	beforeCurDir = curDir;

	if (weapon) weapon->Update();
	if (idle[curDir])	idle[curDir]->Update();
	if (walk[curDir])	walk[curDir]->Update();
	if (roll[curDir])	roll[curDir]->Update();
	if (hit)	hit->Update();
	if (die)	die->Update();
}

void Unit::LateUpdate()
{
}

void Unit::Render()
{
	if (weapon) weapon->Render();
	if (idle[curDir])	idle[curDir]->Render();
	if (walk[curDir])	walk[curDir]->Render();
	if (roll[curDir])	roll[curDir]->Render();
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

			idle[curDir]->isVisible = false;
			hit->isVisible = true;
			die->isVisible = false;

			hit->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
		}
		if (curHp <= 0)
		{
			curHp = 0;
			state = State::die;
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

		idle[curDir]->isVisible = false;
		hit->isVisible = false;
		die->isVisible = true;
	}
}