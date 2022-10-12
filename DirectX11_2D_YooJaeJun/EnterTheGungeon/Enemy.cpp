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
		InitSelf();
		InitItem();
	}

	void Enemy::InitVar()
	{
		timeFire = 0.0f;
		timeHit = 0.0f;
		isHit = false;
		isHitAnim = false;
		timeHitAnim = 0.0f;
		timeSetMoveDir = 0.0f;
		timeSetTargetDir = 0.0f;
		pushedScalar = 400.0f;
		pushedScalarFactor = 0.0f;
		timeAiming = 0.0f;
	}

	void Enemy::InitSelf()
	{
		int idx = 0;

		state = State::die;

		col = new ObCircle;
		col->isVisible = false;
		col->isFilled = false;
		col->color = Color(1.0f, 1.0f, 1.0f);
		col->zOrder = ZOrder::object;
		SetPos(DEFAULTSPAWN);

		colTile = new ObRect;
		colTile->scale = Vector2(col->scale.x, col->scale.y / 2.0f);
		colTile->SetParentRT(*col);
		colTile->SetLocalPosY(col->GetWorldPos().y - col->scale.y / 2.0f);
		colTile->isFilled = false;
		colTile->color = Color(1.0f, 1.0f, 1.0f, 1.0f);

		shadow = new ObImage(L"EnterTheGungeon/Enemy_0/Shadow_1.png");
		shadow->SetParentRT(*col);
		shadow->zOrder = ZOrder::shadow;
	}

	void Enemy::InitItem()
	{
		float scaleFactor = 0.5f;
		dropItem = new Item;
		dropItem->col = new ObCircle;
		dropItem->col->scale = Vector2(40.0f, 40.0f) * scaleFactor;
		dropItem->col->isVisible = false;
		dropItem->col->isFilled = false;
		dropItem->SetPos(DEFAULTSPAWN);
		dropItem->idle = new ObImage(L"EnterTheGungeon/Player_0/UI_Gold.png");
		dropItem->idle->scale = Vector2(40.0f, 40.0f) * scaleFactor;
		dropItem->idle->SetParentRT(*dropItem->col);
		dropItem->idle->isVisible = false;
		dropItem->state = State::die;
	}

	void Enemy::Release()
	{
		Unit::Release();
		weapon->Release();
		for (auto& elem : bullet) elem->Release();
	}

	void Enemy::Update()
	{
		Unit::Update();

		switch (state)
		{
		case State::idle:
			Idle();
			break;
		case State::walk:
			Walk();
			break;
		case State::die:
			Die();
			break;
		default:
			break;
		}

		weapon->Update();
		for (auto& elem : bullet) elem->Update();
		dropItem->Update();
	}

	void Enemy::LateUpdate()
	{
	}

	void Enemy::Render()
	{
		for (auto& elem : bullet) elem->Render();
		Unit::Render();

		weapon->Render();
		dropItem->Render();
	}

	void Enemy::Idle()
	{
		Unit::SetTarget(weapon);
		Unit::Idle();

		Fire();
		Hitting();
	}

	void Enemy::Walk()
	{
		Unit::SetTarget(weapon);
		moveDir = targetDir;
		Unit::Walk();

		Fire();
		Hitting();
	}

	void Enemy::Die()
	{
		Unit::Die();

		pushedScalar -= pushedScalarFactor * DELTA;
		pushedScalarFactor += 800.0f * DELTA;
		col->MoveWorldPos(pushedDir * pushedScalar * DELTA);

		if (TIMER->GetTick(timeRealDie, 0.5f))
		{
			pushedDir = Vector2(0.0f, 0.0f);
			pushedScalar = 400.0f;
			pushedScalarFactor = 0.0f;
		}
	}

	void Enemy::Fire()
	{
		if (TIMER->GetTick(timeFire, 1.0f))
		{
			for (auto& elem : bullet)
			{
				if (elem->isFired) continue;

				elem->Spawn(weapon->firePos->GetWorldPos(), moveDir);
				weapon->fireEffect->Spawn(weapon->firePos->GetWorldPos());

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

			pushedScalar -= pushedScalarFactor * DELTA;
			pushedScalarFactor += 200.0f * DELTA;
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
				pushedScalar = 400.0f;
				pushedScalarFactor = 0.0f;
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

		weapon->col->isVisible = false;
		weapon->idle->isVisible = false;
		weapon->firePos->isVisible = false;

		if (pushedDir.x < 0.0f)
		{
			die->reverseLR = true;
		}
		else
		{
			die->reverseLR = false;
		}

		pushedScalar = 400.0f;
		pushedScalarFactor = 0.0f;

		for (auto& elem : bullet)
		{
			elem->col->isVisible = false;
			elem->idle->isVisible = false;
			elem->hitBomb->idle->isVisible = false;
		}

		dropItem->Spawn(Pos());
		dropItem->col->isVisible = true;
		dropItem->idle->isVisible = true;
		dropItem->state = State::idle;
	}

	void Enemy::Spawn(const Vector2 wpos)
	{
		Unit::Spawn(wpos);

		InitVar();

		walk[curTargetDirState]->isVisible = true;
		walk[curTargetDirState]->ChangeAnim(ANIMSTATE::LOOP, 0.1f);

		weapon->col->isVisible = true;
		weapon->idle->isVisible = true;
		weapon->firePos->isVisible = true;

		if (pushedDir.x < 0.0f)
		{
			die->reverseLR = true;
		}
		else
		{
			die->reverseLR = false;
		}

		pushedScalar = 400.0f;
		pushedScalarFactor = 0.0f;

		dropItem->col->isVisible = false;
		dropItem->idle->isVisible = false;
		dropItem->state = State::die;
	}
}