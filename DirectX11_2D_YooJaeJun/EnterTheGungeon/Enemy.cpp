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
		timeAiming = 0.0f;
	}

	void Enemy::InitSelf()
	{
		int idx = 0;

		state = State::die;

		col = new ObCircle;
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
		Unit::SetTarget(weapon);
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
		moveDir = targetDir;
		Unit::Idle();

		Fire();
		Hitting();
	}

	void Enemy::Walk()
	{
		moveDir = targetDir;
		Unit::Walk();

		Fire();
		Hitting();
	}

	void Enemy::Die()
	{
		Unit::Die();

		timeRealDie += DELTA;
		col->MoveWorldPos(pushedDir * pushedScalar * cos(timeRealDie / 0.63f * DIV2PI) * DELTA);

		if (timeRealDie > 0.63f)
		{
			pushedDir = Vector2(0.0f, 0.0f);
		}
	}

	void Enemy::Fire()
	{
	}

	void Enemy::Hit(const int damage, const Vector2& dir)
	{
		pushedDir = dir;

		Unit::Hit(damage);

		hit->ChangeAnim(AnimState::once, 0.1f);

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
			idle->color = c;
			walk->color = c;
			hit->color = c;

			idle->isVisible = false;
			walk->isVisible = false;
			hit->isVisible = true;

			timeHitAnim += DELTA;
			col->MoveWorldPos(pushedDir * pushedScalar * cos(timeHitAnim / 0.63f * DIV2PI) * DELTA);

			if (timeHitAnim > 0.63f)
			{
				Color c = Color(0.5f, 0.5f, 0.5f, 1.0f);
				idle->color = c;
				walk->color = c;
				hit->color = c;
				die->color = c;

				walk->isVisible = true;
				hit->isVisible = false;

				isHitAnim = false;

				pushedDir = Vector2(0.0f, 0.0f);
			}
		}
		else
		{
			idle->color.w = 1.0f;
			walk->color.w = 1.0f;
			hit->isVisible = false;
		}
	}

	void Enemy::StartDie()
	{
		Unit::StartDie();

		way.clear();

		weapon->idle->isVisible = false;

		if (pushedDir.x < 0.0f)
		{
			die->reverseLR = true;
		}
		else
		{
			die->reverseLR = false;
		}

		pushedScalar = 400.0f;

		dropItem->Spawn(Pos());
		dropItem->col->isVisible = true;
		dropItem->idle->isVisible = true;
		dropItem->state = State::idle;
	}

	void Enemy::Spawn(const Vector2 wpos)
	{
		Unit::Spawn(wpos);

		InitVar();

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

		dropItem->idle->isVisible = false;
		dropItem->state = State::die;
	}
	void Enemy::ColToggle()
	{
		Character::ColToggle();
		weapon->col->isVisible = !weapon->col->isVisible;
		weapon->firePos->isVisible = !weapon->firePos->isVisible;
		for (auto& bulletElem : bullet)
		{
			bulletElem->col->isVisible = !bulletElem->col->isVisible;
		}
	}
}