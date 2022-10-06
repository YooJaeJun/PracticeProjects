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
		targetDir.Normalize();	// targetDir도 써서 정규화
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
			col->colOnOff = false;

			col->isVisible = false;
			for (auto& elem : idle)
			{
				elem->isVisible = false;
				elem->ChangeAnim(ANIMSTATE::STOP, 0.2f);
			}
			for (auto& elem : walk)
			{
				elem->isVisible = false;
				elem->ChangeAnim(ANIMSTATE::STOP, 0.2f);
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

	void Unit::StepBack()
	{
		SetPos(lastPos);
	}

	void Unit::SetMoveDirState()
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

	void Unit::SetTargetDirState()
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

	void Unit::FindPath(ObTileMap* map)
	{
		if (TIMER->GetTick(timeFindPath, 2.0f))
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
					end = way.back()->Pos;
				}
			}
		}

		if (false == way.empty())
		{
			SetPos(Vector2::Lerp(start, end, g));

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
}