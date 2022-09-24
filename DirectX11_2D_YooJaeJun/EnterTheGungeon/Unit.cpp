#include "stdafx.h"

Unit::Unit()
{
	state = State::idle;
	lastPos = Vector2(0.0f, 0.0f);
	timeFire = 0.0f;
	timeReload = 0.0f;
	timeHit = 0.0f;
	isHit = false;
	isHitAnim = 0.0f;
	timeHitAnim = 0.0f;
	targetDirBefore = targetDir = Vector2(0.0f, 0.0f);
	curMoveDirState = dirB;
	curMoveDirStateBefore = dirB;
	curTargetDirState = dirB;
	curTargetDirStateBefore = dirB;
}

void Unit::Release()
{
	Character::Release();
	for(auto& elem : idle) SafeDelete(elem);
	for(auto& elem : walk) SafeDelete(elem);
	SafeDelete(hit);
	SafeDelete(fall);
	SafeDelete(die);
	SafeDelete(weapon);
	SafeDelete(firePos);
	SafeDelete(shadow);
}

void Unit::Update()
{
	lastPos = Pos();

	Character::Update();

	curMoveDirStateBefore = curMoveDirState;
	curTargetDirStateBefore = curTargetDirState;
	targetDirBefore = targetDir;

	if (weapon) weapon->Update();
	for(auto& elem : idle) elem->Update();
	for(auto& elem : walk) elem->Update();
	if (hit) hit->Update();
	if (fall) fall->Update();
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
	idle[curTargetDirState]->Render();
	walk[curTargetDirState]->Render();
	if (hit) hit->Render();
	if (fall) fall->Render();
	if (die) die->Render();
	if (firePos) firePos->Render();
	Character::Render();
}

void Unit::Idle()
{
}

void Unit::Die()
{
	isHit = false;
	scalar = 0.0f;
	col->colOnOff = false;

	if (col) col->isVisible = false;
	for (auto& elem : idle) elem->isVisible = false;
	for (auto& elem : walk) elem->isVisible = false;
	if (hit) hit->isVisible = false;
	weapon->col->isVisible = false;
	weapon->idle->isVisible = false;
	shadow->isVisible = false;
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

			idle[curTargetDirState]->isVisible = false;
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

void Unit::ToDie()
{
	if (state != State::die)
	{
		state = State::die;
		col->scale.x = 0.0f;
		col->scale.y = 0.0f;

		idle[curTargetDirState]->isVisible = false;
		if (hit) hit->isVisible = false;
		die->isVisible = true;
	}
}

void Unit::StepBack()
{
	SetPos(lastPos);
}

void Unit::SetMoveDir()
{
	// 이동방향에 따라 다른 방향 애니메이션 설정하는 코드
	if (almostEqualFloat(moveDir.x, 0.707107f) && almostEqualFloat(moveDir.y, 0.707107f))
	{
		curMoveDirState = dirRT;
	}
	else if (almostEqualFloat(moveDir.x, -0.707107f) && almostEqualFloat(moveDir.y, 0.707107f))
	{
		curMoveDirState = dirLT;
	}
	else if (almostEqualFloat(moveDir.x, -0.707107f) && almostEqualFloat(moveDir.y, -0.707107f))
	{
		curMoveDirState = dirLB;
	}
	else if (almostEqualFloat(moveDir.x, 0.707107f) && almostEqualFloat(moveDir.y, -0.707107f))
	{
		curMoveDirState = dirRB;
	}
	else if (moveDir.x == 1.0f)
	{
		curMoveDirState = dirR;
	}
	else if (moveDir.x == -1.0f)
	{
		curMoveDirState = dirL;
	}
	else if (moveDir.y == 1.0f)
	{
		curMoveDirState = dirT;
	}
	else if (moveDir.y == -1.0f)
	{
		curMoveDirState = dirB;
	}
	else
	{
		curMoveDirState = curMoveDirStateBefore;
	}
}

void Unit::SetTargetDir()
{
	// 타겟 좌표(플레이어는 마우스)에 따라 다른 방향 애니메이션 설정하는 코드
	if (targetRotation >= 30.0f * ToRadian && targetRotation < 60.0f * ToRadian)
	{
		curTargetDirState = dirRT;
	}
	else if (targetRotation >= 120.0f * ToRadian && targetRotation < 150.0f * ToRadian)
	{
		curTargetDirState = dirLT;
	}
	else if (targetRotation >= -150.0f * ToRadian && targetRotation < -120.0f * ToRadian)
	{
		curTargetDirState = dirLB;
	}
	else if (targetRotation >= -60.0f * ToRadian && targetRotation < -30.0f * ToRadian)
	{
		curTargetDirState = dirRB;
	}
	else if (targetRotation >= -30.0f * ToRadian && targetRotation < 30.0f * ToRadian)
	{
		curTargetDirState = dirR;
	}
	else if ((targetRotation >= -180.0f * ToRadian && targetRotation < -150.0f * ToRadian) ||
		(targetRotation >= 150.0f * ToRadian && targetRotation < 180.0f * ToRadian))
	{
		curTargetDirState = dirL;
	}
	else if (targetRotation >= 60.0f * ToRadian && targetRotation < 120.0f * ToRadian)
	{
		curTargetDirState = dirT;
	}
	else if (targetRotation >= -120.0f * ToRadian && targetRotation < -60.0f * ToRadian)
	{
		curTargetDirState = dirB;
	}
	else
	{
		curTargetDirState = curTargetDirStateBefore;
	}
}

vector<Vector2>& Unit::Foot()
{
	foot.resize(4);

	foot[0] = Pos() + Vector2(0.0f, -col->scale.y / 2.0f) + Vector2(-10.0f, -10.0f);
	foot[1] = Pos() + Vector2(0.0f, -col->scale.y / 2.0f) + Vector2(10.0f, -10.0f);
	foot[2] = Pos() + Vector2(0.0f, -col->scale.y / 2.0f) + Vector2(-10.0f, 10.0f);
	foot[3] = Pos() + Vector2(0.0f, -col->scale.y / 2.0f) + Vector2(10.0f, 10.0f);

	return foot;
}