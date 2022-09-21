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
	rotationForMouseBefore = rotationForMouse = Vector2(0.0f, 0.0f);
}

void Unit::Release()
{
	Character::Release();
	for(auto& elem : idle) SafeDelete(elem);
	for(auto& elem : walk) SafeDelete(elem);
	if (roll[curDir]) for(auto& elem : roll) SafeDelete(elem);
	SafeDelete(hit);
	SafeDelete(die);
	SafeDelete(weapon);
	SafeDelete(firePos);
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
	else if (moveDir.y == -1.0f)
	{
		curDir = front;
	}
	else
	{
		curDir = beforeDir;
	}


	weapon->col->rotation = Utility::DirToRadian(dest - weapon->col->GetWorldPos());

	rotationForMouse = dest - col->GetWorldPos();
	
	if (rotationForMouse.x >= 0.0f)
	{
		if (rotationForMouseBefore.x < 0.0f)
		{
			swap(weapon->idle->uv.y, weapon->idle->uv.w);
			weapon->col->SetLocalPosX(18.0f);
			weapon->col->pivot = Vector2(0.4f, 0.25f);
			weapon->idle->pivot = Vector2(0.4f, 0.25f);
		}
	}
	else
	{
		if (rotationForMouseBefore.x >= 0.0f)
		{
			swap(weapon->idle->uv.y, weapon->idle->uv.w);
			weapon->col->SetLocalPosX(-18.0f);
			weapon->col->pivot = Vector2(0.4f, -0.25f);
			weapon->idle->pivot = Vector2(0.4f, -0.25f);
		}
	}


	if (state == State::die)
	{
		isHit = false;
		scalar = 0.0f;
		col->colOnOff = false;

		if (col) col->isVisible = false;
		for (auto& elem : idle) elem->isVisible = false;
		for (auto& elem : walk) elem->isVisible = false;
		if (roll[curDir]) for (auto& elem : roll) elem->isVisible = false;
		if (hit) hit->isVisible = false;
		weapon->col->isVisible = false;
		weapon->idle->isVisible = false;
	}
	else if (state == State::idle)
	{
		if (isHitAnim)
		{
			Color c = Color(0.5f, 0.5f, 0.5f, RANDOM->Float());
			for (auto& elem : idle) elem->color = c;
			for (auto& elem : walk) elem->color = c;
			if (roll[curDir]) for (auto& elem : roll) elem->color = c;
			if (hit)  hit->color = c;
			if (die)  die->color = c;

			col->SetWorldPosX(col->GetWorldPos().x + RANDOM->Float(-1.0f, 1.0f));
			col->SetWorldPosY(col->GetWorldPos().y + RANDOM->Float(-1.0f, 1.0f));

			for (auto& elem : idle) elem->isVisible = false;
			hit->isVisible = true;

			if (TIMER->GetTick(timeHitAnim, 0.4f))	// 히트 애니용
			{
				Color c = Color(0.5f, 0.5f, 0.5f, 1.0f);
				for (auto& elem : idle) elem->color = c;
				for (auto& elem : walk) elem->color = c;
				if (roll[curDir]) for (auto& elem : roll) elem->color = c;
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

	beforeDir = curDir;
	rotationForMouseBefore = rotationForMouse;

	if (weapon) weapon->Update();
	idle[curDir]->Update();
	walk[curDir]->Update();
	if (roll[curDir]) roll[curDir]->Update();
	if (hit) hit->Update();
	if (die) die->Update();
	if (firePos) firePos->Update();
}

void Unit::LateUpdate()
{
}

void Unit::Render()
{
	if (weapon) weapon->Render();
	idle[curDir]->Render();
	walk[curDir]->Render();
	if (roll[curDir]) roll[curDir]->Render();
	if (hit) hit->Render();
	if (die) die->Render();
	if (firePos) firePos->Render();
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