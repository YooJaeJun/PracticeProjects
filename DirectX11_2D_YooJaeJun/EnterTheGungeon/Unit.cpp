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
	targetDirBefore = targetDir = Vector2(0.0f, 0.0f);
	curMove8Dir = front;
	curMove8DirBefore = front;
	curTarget8Dir = front;
	curTarget8DirBefore = front;
}

void Unit::Release()
{
	Character::Release();
	for(auto& elem : idle) SafeDelete(elem);
	for(auto& elem : walk) SafeDelete(elem);
	if (roll[curMove8Dir]) for(auto& elem : roll) SafeDelete(elem);
	SafeDelete(hit);
	SafeDelete(fall);
	SafeDelete(die);
	SafeDelete(weapon);
	SafeDelete(firePos);
	SafeDelete(shadow);
}

void Unit::Update()
{
	Character::Update();

	SetMoveDir();

	weapon->col->rotation = Utility::DirToRadian(target - weapon->col->GetWorldPos());

	targetDir = target - col->GetWorldPos();
	targetDir.Normalize();

	targetRotation = Utility::DirToRadian(targetDir);

	SetTargetDir();

	if (targetDir.x >= 0.0f)
	{
		if (targetDirBefore.x < 0.0f)
		{
			swap(weapon->idle->uv.y, weapon->idle->uv.w);
			weapon->col->SetLocalPosX(18.0f);
			weapon->col->pivot = Vector2(0.4f, 0.25f);
			weapon->idle->pivot = Vector2(0.4f, 0.25f);
		}
	}
	else
	{
		if (targetDirBefore.x >= 0.0f)
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
		if (roll[curMove8Dir]) for (auto& elem : roll) elem->isVisible = false;
		if (hit) hit->isVisible = false;
		weapon->col->isVisible = false;
		weapon->idle->isVisible = false;
		shadow->isVisible = false;
	}

	curMove8DirBefore = curMove8Dir;
	curTarget8DirBefore = curTarget8Dir;

	targetDirBefore = targetDir;

	if (weapon) weapon->Update();
	idle[curTarget8Dir]->Update();
	walk[curTarget8Dir]->Update();
	if (roll[curMove8Dir]) roll[curMove8Dir]->Update();
	if (hit) hit->Update();
	if (fall) firePos->Update();
	if (die) die->Update();
	if (firePos) firePos->Update();
	if (shadow) shadow->Update();
}

void Unit::LateUpdate()
{
}

void Unit::Render()
{
	if (shadow) shadow->Render();
	if (weapon) weapon->Render();
	idle[curTarget8Dir]->Render();
	walk[curTarget8Dir]->Render();
	if (roll[curMove8Dir]) roll[curMove8Dir]->Render();
	if (hit) hit->Render();
	if (fall) firePos->Render();
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

			idle[curTarget8Dir]->isVisible = false;
			if (hit) hit->isVisible = true;
			die->isVisible = false;
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

		idle[curTarget8Dir]->isVisible = false;
		if (hit) hit->isVisible = false;
		die->isVisible = true;
	}
}

void Unit::SetMoveDir()
{
	// 이동방향에 따라 다른 방향 애니메이션 설정하는 코드
	if (almostEqualFloat(moveDir.x, 0.707107f) && almostEqualFloat(moveDir.y, 0.707107f))
	{
		curMove8Dir = backRightDiag;
	}
	else if (almostEqualFloat(moveDir.x, -0.707107f) && almostEqualFloat(moveDir.y, 0.707107f))
	{
		curMove8Dir = backLeftDiag;
	}
	else if (almostEqualFloat(moveDir.x, -0.707107f) && almostEqualFloat(moveDir.y, -0.707107f))
	{
		curMove8Dir = leftDiag;
	}
	else if (almostEqualFloat(moveDir.x, 0.707107f) && almostEqualFloat(moveDir.y, -0.707107f))
	{
		curMove8Dir = rightDiag;
	}
	else if (moveDir.x == 1.0f)
	{
		curMove8Dir = rightSide;
	}
	else if (moveDir.x == -1.0f)
	{
		curMove8Dir = leftSide;
	}
	else if (moveDir.y == 1.0f)
	{
		curMove8Dir = back;
	}
	else if (moveDir.y == -1.0f)
	{
		curMove8Dir = front;
	}
	else
	{
		curMove8Dir = curMove8DirBefore;
	}
}

void Unit::SetTargetDir()
{
	// 타겟 좌표(플레이어는 마우스)에 따라 다른 방향 애니메이션 설정하는 코드
	if (targetRotation >= 30.0f * ToRadian && targetRotation < 60.0f * ToRadian)
	{
		curTarget8Dir = backRightDiag;
	}
	else if (targetRotation >= 120.0f * ToRadian && targetRotation < 150.0f * ToRadian)
	{
		curTarget8Dir = backLeftDiag;
	}
	else if (targetRotation >= -150.0f * ToRadian && targetRotation < -120.0f * ToRadian)
	{
		curTarget8Dir = leftDiag;
	}
	else if (targetRotation >= -60.0f * ToRadian && targetRotation < -30.0f * ToRadian)
	{
		curTarget8Dir = rightDiag;
	}
	else if (targetRotation >= -30.0f * ToRadian && targetRotation < 30.0f * ToRadian)
	{
		curTarget8Dir = rightSide;
	}
	else if ((targetRotation >= -180.0f * ToRadian && targetRotation < -150.0f * ToRadian) ||
		(targetRotation >= 150.0f * ToRadian && targetRotation < 180.0f * ToRadian))
	{
		curTarget8Dir = leftSide;
	}
	else if (targetRotation >= 60.0f * ToRadian && targetRotation < 120.0f * ToRadian)
	{
		curTarget8Dir = back;
	}
	else if (targetRotation >= -120.0f * ToRadian && targetRotation < -60.0f * ToRadian)
	{
		curTarget8Dir = front;
	}
	else
	{
		curTarget8Dir = curTarget8DirBefore;
	}
}
