#include "stdafx.h"

namespace Gungeon
{
	Unit::Unit()
	{
		Init();
	}

	void Unit::Init()
	{
		lastPos = Vector2(0.0f, 0.0f);
		targetDirBefore = targetDir = Vector2(0.0f, 0.0f);
		curMoveDirState = dirB;
		curMoveDirStateBefore = dirB;
		curTargetDirState = dirB;
		curTargetDirStateBefore = dirB;
		timeFire = 0.0f;
		timeReload = 0.0f;
		pushedDir = Vector2(0.0f, 0.0f);
		timeHit = 0.0f;
		isHit = false;
		isHitAnim = 0.0f;
		timeHitAnim = 0.0f;
		timeDieAnim = 0.0f;
		timeRealDie = 0.0f;
	}

	void Unit::Release()
	{
		Character::Release();
		for (auto& elem : idle) SafeDelete(elem);
		for (auto& elem : walk) SafeDelete(elem);
		SafeDelete(hit);
		SafeDelete(fall);
		SafeDelete(die);
		SafeDelete(shadow);
	}

	void Unit::Update()
	{
		SetLastPosAndDir();

		switch (state)
		{
		case Gungeon::State::idle:
			if (moveDir.x != 0.0f || moveDir.y != 0.0f)
			{
				StartWalk();
			}
			break;
		case Gungeon::State::walk:
			if (moveDir.x == 0.0f && moveDir.y == 0.0f)
			{
				StartIdle();
			}
			break;
		case Gungeon::State::die:
			break;
		default:
			break;
		}

		Character::Update();

		for (auto& elem : idle) elem->Update();
		for (auto& elem : walk) elem->Update();
		if (hit) hit->Update();
		if (fall) fall->Update();
		if (die) die->Update();
		if (shadow) shadow->Update();
	}

	void Unit::LateUpdate()
	{
	}

	void Unit::Render()
	{
		idle[curTargetDirState]->Render(); // RENDER->push(idle[curTargetDirState]);
		walk[curTargetDirState]->Render(); // RENDER->push(walk[curTargetDirState]);
		if (hit)  hit->Render();  // RENDER->push(hit);
		if (fall) fall->Render(); // RENDER->push(fall);
		if (die)  die->Render();  // RENDER->push(die);
		Character::Render();
	}

	void Unit::ResizeScreen()
	{
	}

	void Unit::SetTarget(Weapon*& weapon)
	{
		targetDir = targetPos - Pos();
		targetDir.Normalize();	// targetDir�� ����ϹǷ� �̸� ����ȭ
		targetRotation = Utility::DirToRadian(targetDir);
		SetTargetDirState();

		if (weapon)
		{
			weapon->col->rotation = Utility::DirToRadian(targetPos - weapon->Pos());

			if (targetDir.x >= 0.0f)
			{
				if (targetDirBefore.x < 0.0f)
				{
					weapon->EquipRight();
				}
			}
			else
			{
				if (targetDirBefore.x >= 0.0f)
				{
					weapon->EquipLeft();
				}
			}
		}
	}

	void Unit::Idle()
	{
		Unit::SetTarget(curWeapon);
		SetMoveDirState();
		for (auto& elem : walk) elem->isVisible = false;
		idle[curTargetDirState]->isVisible = true;
	}

	void Unit::Walk()
	{
		Unit::SetTarget(curWeapon);
		SetMoveDirState();
		for (auto& elem : idle) elem->isVisible = false;
		walk[curTargetDirState]->isVisible = true;
	}

	void Unit::Hit(const int damage)
	{
		if (false == isHit)
		{
			curHp -= damage;
			isHit = true;
			isHitAnim = true;

			if (damage > 0)
			{
				if (hit)
				{
					idle[curTargetDirState]->isVisible = false;
					walk[curTargetDirState]->isVisible = false;
					hit->isVisible = true;
					hit->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
				}

				if (curHp <= 0)
				{
					curHp = 0;
					StartDie();
				}
			}
		}
	}

	void Unit::StartDie()
	{
		if (state != State::die)
		{
			state = State::die;

			isHit = false;
			scalar = 0.0f;

			col->isVisible = false;
			for (auto& elem : idle)
			{
				elem->isVisible = false;
				elem->ChangeAnim(ANIMSTATE::STOP, 0.2f);
			}
			for (auto& elem : walk)
			{
				elem->isVisible = false;
				elem->ChangeAnim(ANIMSTATE::STOP, 0.1f);
			}

			if (hit) hit->isVisible = false;
			shadow->isVisible = false;
			die->isVisible = true;

			die->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
		}
	}

	void Unit::SetLastPosAndDir()
	{
		lastPos = Pos();
		curMoveDirStateBefore = curMoveDirState;
		curTargetDirStateBefore = curTargetDirState;
		targetDirBefore = targetDir;
	}

	void Unit::Die()
	{
		if (TIMER->GetTick(timeDieAnim, 0.1f))
		{
			die->color = Color(0.4f, 0.4f, 0.4f, 0.4f);
		}

		if (colTile) colTile->isVisible = false;
	}

	void Unit::StartWalk()
	{
		state = State::walk;
		for (auto& elem : idle) elem->isVisible = false;
		walk[curTargetDirState]->isVisible = true;
		walk[curTargetDirState]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	}

	void Unit::StartIdle()
	{
		state = State::idle;
		for (auto& elem : walk) elem->isVisible = false;
		idle[curTargetDirState]->isVisible = true;
		idle[curTargetDirState]->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
	}

	void Unit::StepBack()
	{
		SetPos(lastPos);
	}

	void Unit::SetMoveDirState()
	{
		// �̵����⿡ ���� �ٸ� ���� �ִϸ��̼� �����ϴ� �ڵ�
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

	void Unit::SetTargetDirState()
	{
		// Ÿ�� ��ǥ(�÷��̾�� ���콺)�� ���� �ٸ� ���� �ִϸ��̼� �����ϴ� �ڵ�
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

	void Unit::FindPath(ObTileMap* map)
	{
		if (TIMER->GetTick(timeFindPath, 1.0f))
		{
			Int2 sour, dest;
			bool isFind;

			isFind = map->WorldPosToTileIdx(Pos(), sour);
			isFind &= map->WorldPosToTileIdx(targetPos, dest);

			if (isFind)
			{
				if (map->PathFinding(sour, dest, way))
				{
					g = 0.0f;
					start = Pos();
					way.pop_back();
					map->Update();
					end = way.back()->Pos;
				}
			}
		}

		if (false == way.empty())
		{
			SetPos(Vector2::Lerp(start, end, g));
			moveDir = end - start;
			moveDir.Normalize();

			g += DELTA * scalar / 100.0f;

			if (g > 1.0f)
			{
				g = 0.0f;
				start = end;
				way.pop_back();
				if (false == way.empty())
				{
					end = way.back()->Pos;
				}
			}
		}
	}

	void Unit::DontFindPath()
	{
		moveDir = Vector2(0.0f, 0.0f);
	}
	
	void Unit::Spawn(const Vector2 wpos)
	{
		Character::Spawn(wpos);

		die->isVisible = false;
		idle[curTargetDirState]->isVisible = true;
		shadow->isVisible = true;

		Color c = Color(0.5f, 0.5f, 0.5f, 1.0f);
		for (auto& elem : idle) elem->color = c;
		for (auto& elem : walk) elem->color = c;
		if (hit) hit->color = c;
		if (die) die->color = c;
	}
}