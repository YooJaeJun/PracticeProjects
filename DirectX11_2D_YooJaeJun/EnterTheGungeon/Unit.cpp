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
		SafeDelete(idle);
		SafeDelete(walk);
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
			if (false == (moveDir.x == 0.0f && moveDir.y == 0.0f))
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

		idle->Update();
		walk->Update();
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
		idle->Render(); // RENDER->push(idle[curTargetDirState]);
		walk->Render(); // RENDER->push(walk[curTargetDirState]);
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
		targetDir.Normalize();
		SetDirState(targetDir, curTargetDirState);

		idle->frame.y = curTargetDirState;
		walk->frame.y = curTargetDirState;

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
	}

	void Unit::Walk()
	{
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
					idle->isVisible = false;
					walk->isVisible = false;
					hit->isVisible = true;
					hit->ChangeAnim(AnimState::loop, 0.2f);
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

			idle->isVisible = false;
			walk->isVisible = false;

			if (hit) hit->isVisible = false;
			shadow->isVisible = false;
			die->isVisible = true;

			die->ChangeAnim(AnimState::once, 0.1f);
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
		idle->isVisible = false;
		walk->isVisible = true;
		walk->ChangeAnim(AnimState::loop, 0.1f);
	}

	void Unit::StartIdle()
	{
		state = State::idle;
		walk->isVisible = false;
		idle->isVisible = true;
		idle->ChangeAnim(AnimState::loop, 0.2f);
	}

	void Unit::StepBack()
	{
		SetPos(lastPos);
	}

	// moveDir: �̵����⿡ ���� �ٸ� ���� �ִϸ��̼�(�÷��̾�� roll) ����
	// targetDir: Ÿ�� ��ǥ(�÷��̾�� ���콺)�� ���� �ٸ� ���� �ִϸ��̼�(���� Idle, Walk) ����
	void Unit::SetDirState(const Vector2 dir, DirState& dirState)
	{
		float rotation = Utility::DirToRadian(dir);

		if (rotation >= 30.0f * ToRadian && rotation < 60.0f * ToRadian)
		{
			dirState = dirRT;
		}
		else if (rotation >= 120.0f * ToRadian && rotation < 150.0f * ToRadian)
		{
			dirState = dirLT;
		}
		else if (rotation >= -150.0f * ToRadian && rotation < -120.0f * ToRadian)
		{
			dirState = dirLB;
		}
		else if (rotation >= -60.0f * ToRadian && rotation < -30.0f * ToRadian)
		{
			dirState = dirRB;
		}
		else if (rotation >= -30.0f * ToRadian && rotation < 30.0f * ToRadian)
		{
			dirState = dirR;
		}
		else if ((rotation > -181.0f * ToRadian && rotation <= -150.0f * ToRadian) ||
			(rotation >= 150.0f * ToRadian && rotation < 181.0f * ToRadian))
		{
			dirState = dirL;
		}
		else if (rotation >= 60.0f * ToRadian && rotation < 120.0f * ToRadian)
		{
			dirState = dirT;
		}
		else if (rotation >= -120.0f * ToRadian && rotation < -60.0f * ToRadian)
		{
			dirState = dirB;
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
		idle->isVisible = true;
		shadow->isVisible = true;

		Color c = Color(0.5f, 0.5f, 0.5f, 1.0f);
		idle->color = c;
		walk->color = c;
		if (hit) hit->color = c;
		if (die) die->color = c;
	}
}