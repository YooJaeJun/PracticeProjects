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
		InitWeapon();
		InitBullet();
		InitItem();
	}

	void Enemy::InitVar()
	{
		col = new ObCircle;

		curHp = maxHp = 3;
		scalar = 80.0f;
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

	void Enemy::InitSelf()
	{
		int idx = 0;
		float enemyScaleCoef = 3.0f;

		col = new ObCircle;
		col->scale.x = 16.0f * enemyScaleCoef;
		col->scale.y = 16.0f * enemyScaleCoef;
		col->color = Color(1.0f, 1.0f, 1.0f);
		col->isFilled = false;
		col->zOrder = ZOrder::object;

		idle[dirB] = new ObImage(L"EnterTheGungeon/Enemy_0/Idle_Front.png");
		idle[dirL] = new ObImage(L"EnterTheGungeon/Enemy_0/Idle_Side.png");
		idle[dirR] = new ObImage(L"EnterTheGungeon/Enemy_0/Idle_Side.png");
		idle[dirLB] = new ObImage(L"EnterTheGungeon/Enemy_0/Idle_Side.png");
		idle[dirRB] = new ObImage(L"EnterTheGungeon/Enemy_0/Idle_Side.png");
		idle[dirT] = new ObImage(L"EnterTheGungeon/Enemy_0/Idle_Back.png");
		idle[dirLT] = new ObImage(L"EnterTheGungeon/Enemy_0/Idle_Back.png");
		idle[dirRT] = new ObImage(L"EnterTheGungeon/Enemy_0/Idle_Back.png");

		idx = 0;
		for (auto& elem2 : idle)
		{
			if (idx == dirR || idx == dirRB || idx == dirRT)
			{
				elem2->reverseLR = true;
			}
			elem2->maxFrame.x = 2;
			elem2->scale.x = 28.0f / 2.0f * enemyScaleCoef;
			elem2->scale.y = 24.0f * enemyScaleCoef;
			elem2->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
			elem2->SetParentRT(*col);
			elem2->zOrder = ZOrder::object;
			idx++;
		}

		walk[dirB] = new ObImage(L"EnterTheGungeon/Enemy_0/Walk_Front.png");
		walk[dirL] = new ObImage(L"EnterTheGungeon/Enemy_0/Walk_Side.png");
		walk[dirR] = new ObImage(L"EnterTheGungeon/Enemy_0/Walk_Side.png");
		walk[dirLB] = new ObImage(L"EnterTheGungeon/Enemy_0/Walk_Side.png");
		walk[dirRB] = new ObImage(L"EnterTheGungeon/Enemy_0/Walk_Side.png");
		walk[dirT] = new ObImage(L"EnterTheGungeon/Enemy_0/Walk_Back.png");
		walk[dirLT] = new ObImage(L"EnterTheGungeon/Enemy_0/Walk_Back.png");
		walk[dirRT] = new ObImage(L"EnterTheGungeon/Enemy_0/Walk_Back.png");

		idx = 0;
		for (auto& elem2 : walk)
		{
			if (idx == dirR || idx == dirRB || idx == dirRT)
			{
				elem2->reverseLR = true;
			}
			elem2->isVisible = false;
			elem2->maxFrame.x = 6;
			elem2->scale.x = 96.0f / 6.0f * enemyScaleCoef;
			elem2->scale.y = 24.0f * enemyScaleCoef;
			elem2->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
			elem2->SetParentRT(*col);
			elem2->zOrder = ZOrder::object;
			idx++;
		}

		hit = new ObImage(L"EnterTheGungeon/Enemy_0/Hit.png");
		hit->isVisible = false;
		hit->maxFrame.x = 1;
		hit->scale.x = 16.0f * enemyScaleCoef;
		hit->scale.y = 24.0f * enemyScaleCoef;
		hit->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
		hit->SetParentRT(*col);
		hit->zOrder = ZOrder::object;

		die = new ObImage(L"EnterTheGungeon/Enemy_0/Die.png");
		die->isVisible = false;
		die->maxFrame.x = 5;
		die->scale.x = 110.0f / 5.0f * enemyScaleCoef;
		die->scale.y = 22.0f * enemyScaleCoef;
		die->SetParentRT(*col);
		die->zOrder = ZOrder::object;

		colTile = new ObRect;
		colTile->scale = Vector2(col->scale.x, col->scale.y / 2.0f);
		colTile->SetParentRT(*col);
		colTile->SetLocalPosY(col->GetWorldPos().y - col->scale.y / 2.0f);
		colTile->isFilled = false;
		colTile->color = Color(1.0f, 1.0f, 1.0f, 1.0f);

		shadow = new ObImage(L"EnterTheGungeon/Enemy_0/Shadow_1.png");
		shadow->scale.x = 12.0f * enemyScaleCoef;
		shadow->scale.y = 4.0f * enemyScaleCoef;
		shadow->SetParentRT(*col);
		shadow->SetWorldPosY(-35.0f);
		shadow->zOrder = ZOrder::shadow;
	}

	void Enemy::InitWeapon()
	{
		float enemyWeaponScaleCoef = 1.5f;
		weapon.resize(1);
		for (auto& elem : weapon)
		{
			elem = new Weapon;
			elem->col = new ObRect;
			elem->col->isVisible = false;
			elem->col->isFilled = false;
			elem->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
			elem->col->pivot = OFFSET_LB;
			elem->col->scale.x = 29.0f * enemyWeaponScaleCoef;
			elem->col->scale.y = 21.0f * enemyWeaponScaleCoef;
			elem->col->SetParentRT(*col);
			elem->col->SetLocalPos(Vector2(10.0f, -15.0f));

			elem->idle = new ObImage(L"EnterTheGungeon/Enemy_0/Weapon_0.png");
			elem->idle->pivot = OFFSET_LB;
			elem->idle->scale.x = 29.0f * enemyWeaponScaleCoef;
			elem->idle->scale.y = 21.0f * enemyWeaponScaleCoef;
			elem->idle->SetParentRT(*elem->col);
			elem->idle->zOrder = ZOrder::weapon;

			elem->firePos = new GameObject;
			elem->firePos->SetParentRT(*elem->col);
			elem->firePos->SetLocalPos(Vector2(elem->col->scale.x / 2.0f, 0.0f));
			elem->firePos->zOrder = ZOrder::none;

			float enemyWeaponEffectScaleCoef = 3.0f;
			elem->fireEffect = new Effect;
			elem->fireEffect->idle = new ObImage(L"EnterTheGungeon/Enemy_0/Effect_Fire_Weapon_0.png");
			elem->fireEffect->idle->isVisible = false;
			elem->fireEffect->idle->maxFrame.x = 3;
			elem->fireEffect->idle->scale = Vector2(45.0f / 3.0f, 11.0f) * enemyWeaponEffectScaleCoef;
			elem->fireEffect->idle->SetParentRT(*elem->firePos);
			elem->fireEffect->idle->zOrder = ZOrder::none;
			elem->fireEffect->intervalDie = 0.2f;

			elem->pivotDefault = Vector2(0.4f, 0.25f);
			elem->localPosDefault = Vector2(18.0f, -15.0f);
			elem->localFirePosDefault = Vector2(40.0f, 12.0f);
			elem->Equip();
		}
	}

	void Enemy::InitBullet()
	{
		bullet.resize(10);
		for (auto& elem : bullet)
		{
			elem = new EnemyBullet;
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
}