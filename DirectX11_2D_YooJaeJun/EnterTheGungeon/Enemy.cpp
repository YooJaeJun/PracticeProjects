#include "stdafx.h"

namespace Gungeon
{
	Enemy::Enemy()
	{
		Init();
	}

	void Enemy::Init()
	{
		InitVar();
		InitBullet();
		InitItem();
	}

	void Enemy::InitVar()
	{
		curHp = maxHp = 3;
		scalar = 120.0f;
		timeFire = 0.0f;
		timeHit = 0.0f;
		isHit = false;
		isHitAnim = false;
		timeHitAnim = 0.0f;
		timeSetMoveDir = 0.0f;
		timeSetTargetDir = 0.0f;
		pushedDir = Vector2(0.0f, 0.0f);
		pushedScalar = 100.0f;
		pushedScalarCoef = 0.0f;
		timeAiming = 0.0f;
	}

	void Enemy::InitBullet()
	{
		float bulletCoef = 3.0f;
		bullet.resize(10);

		for (auto& elem : bullet)
		{
			elem = new EnemyBullet;
			elem->col->scale = Vector2(8.0f, 8.0f) * bulletCoef;
			elem->idle = new ObImage(L"EnterTheGungeon/Enemy_0/Bullet_0.png");
			elem->idle->scale = Vector2(8.0f, 8.0f) * bulletCoef;
			elem->idle->SetParentRT(*elem->col);
		}
	}

	void Enemy::InitItem()
	{
		float itemCoef = 0.5f;
		dropItem = new Item;
		dropItem->col = new ObCircle;
		dropItem->col->scale = Vector2(40.0f, 40.0f) * itemCoef;
		dropItem->col->isVisible = false;
		dropItem->col->isFilled = false;
		dropItem->col->SetWorldPos(DEFAULTSPAWN);
		dropItem->idle = new ObImage(L"EnterTheGungeon/Player_0/UI_Gold.png");
		dropItem->idle->scale = Vector2(40.0f, 40.0f) * itemCoef;
		dropItem->idle->SetParentRT(*dropItem->col);
		dropItem->idle->isVisible = false;
		dropItem->state = State::die;
	}

	void Enemy::Release()
	{
		Unit::Release();
		for (auto& elem : bullet) elem->Release();
	}

	void Enemy::Update()
	{
		Unit::Update();

		switch (state)
		{
		case State::idle:
			Idle();
			for (auto& elem : bullet) elem->Update();	// 방에 충돌체 생기기 전까지 임시로 상태에 끼워넣음
			break;
		case State::walk:
			Walk();
			for (auto& elem : bullet) elem->Update();	// 방에 충돌체 생기기 전까지 임시로 상태에 끼워넣음
			break;
		case State::die:
			Die();
			break;
		default:
			break;
		}

		dropItem->Update();
	}

	void Enemy::LateUpdate()
	{
	}

	void Enemy::Render()
	{
		for (auto& elem : bullet) elem->Render();
		Unit::Render();

		dropItem->Render();
	}

	void Enemy::Idle()
	{
		Unit::SetTarget();

		moveDir = targetDir;
		SetMoveDirState();

		Fire();
		if (false == isHit)
		{
			StartWalk();
		}
		Hitting();
	}

	void Enemy::Walk()
	{
		Unit::SetTarget();

		moveDir = targetDir;
		SetMoveDirState();

		Fire();
		if (false == isHit)
		{
			StartIdle();
		}
		Hitting();
	}

	void Enemy::Die()
	{
		Unit::Die();

		pushedScalar -= pushedScalarCoef * DELTA;
		pushedScalarCoef += 800.0f * DELTA;
		col->MoveWorldPos(pushedDir * pushedScalar * DELTA);

		if (TIMER->GetTick(timeRealDie, 0.5f))
		{
			pushedDir = Vector2(0.0f, 0.0f);
			pushedScalar = 100.0f;
			pushedScalarCoef = 0.0f;
		}
	}

	void Enemy::StartWalk()
	{
		if (moveDir.x == 0.0f && moveDir.y == 0.0f)
		{
			idle[curTargetDirState]->isVisible = true;
			for (auto& elem : walk) elem->isVisible = false;
		}
		else
		{
			state = State::walk;
			for (auto& elem : idle) elem->isVisible = false;
			walk[curTargetDirState]->isVisible = true;
		}
	}

	void Enemy::StartIdle()
	{
		if (moveDir.x == 0.0f && moveDir.y == 0.0f)
		{
			state = State::idle;
			idle[curTargetDirState]->isVisible = true;
			for (auto& elem : walk) elem->isVisible = false;
		}
		else
		{
			for (auto& elem : idle) elem->isVisible = false;
			walk[curTargetDirState]->isVisible = true;
		}
	}

	void Enemy::Fire()
	{
		if (TIMER->GetTick(timeFire, 1.0f))
		{
			for (auto& elem : bullet)
			{
				if (elem->isFired) continue;

				elem->Spawn(weapon[curWeaponIdx]->firePos->GetWorldPos(), moveDir);
				weapon[curWeaponIdx]->fireEffect->Spawn(weapon[curWeaponIdx]->firePos->GetWorldPos());

				break;
			}
		}
	}

	void Enemy::Hit(const int damage, const Vector2& dir)
	{
		pushedDir = dir;

		Unit::Hit(damage);

		hit->ChangeAnim(ANIMSTATE::ONCE, 0.1f);

		if (pushedDir.x < 0.0f)
		{
			hit->reverseLR = true;
		}
		else
		{
			hit->reverseLR = false;
		}
	}

	void Enemy::Hitting()
	{
		if (isHit)
		{
			if (TIMER->GetTick(timeHit, 0.01f))
			{
				isHit = false;
			}
		}

		if (isHitAnim)
		{
			Color c = Color(RANDOM->Float(0.6f, 1.0f), 0.5f, 0.5f, RANDOM->Float(0.2f, 1.0f));
			for (auto& elem : idle) elem->color = c;
			for (auto& elem : walk) elem->color = c;
			hit->color = c;

			pushedScalar -= pushedScalarCoef * DELTA;
			pushedScalarCoef += 200.0f * DELTA;
			col->MoveWorldPos(pushedDir * pushedScalar * DELTA);

			for (auto& elem : idle) elem->isVisible = false;
			for (auto& elem : walk) elem->isVisible = false;
			hit->isVisible = true;


			if (TIMER->GetTick(timeHitAnim, 0.5f))
			{
				Color c = Color(0.5f, 0.5f, 0.5f, 1.0f);
				for (auto& elem : idle) elem->color = c;
				for (auto& elem : walk) elem->color = c;
				hit->color = c;
				die->color = c;

				walk[curTargetDirState]->isVisible = true;
				hit->isVisible = false;

				isHitAnim = false;

				pushedDir = Vector2(0.0f, 0.0f);
				pushedScalar = 100.0f;
				pushedScalarCoef = 0.0f;
			}
		}
		else
		{
			idle[curTargetDirState]->color.w = 1.0f;
			walk[curTargetDirState]->color.w = 1.0f;
			hit->isVisible = false;
		}
	}

	void Enemy::StartDie()
	{
		Unit::StartDie();

		if (pushedDir.x < 0.0f)
		{
			die->reverseLR = true;
		}
		else
		{
			die->reverseLR = false;
		}

		pushedScalar = 400.0f;
		pushedScalarCoef = 0.0f;

		for (auto& elem : bullet)
		{
			elem->col->colOnOff = false;
			elem->col->isVisible = false;
			elem->idle->colOnOff = false;
			elem->idle->isVisible = false;
			elem->hitBomb->idle->isVisible = false;
		}

		dropItem->Spawn(Pos());
		dropItem->col->isVisible = true;
		dropItem->idle->isVisible = true;
		dropItem->state = State::idle;
	}

	void Enemy::FindPath(ObTileMap* map)
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
			// SetPos(Vector2::Lerp(start, end, g));
			moveDir = way.back()->Pos - Pos();
			moveDir.Normalize();
			col->MoveWorldPos(moveDir * scalar * DELTA);
	
			g += DELTA * 2.0f;
	
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