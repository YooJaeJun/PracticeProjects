#include "stdafx.h"

namespace Gungeon
{
	Enemy3::Enemy3()
	{
		Enemy3::Init();
	}

	void Enemy3::Init()
	{
		InitVar();
		InitSelf();
		InitWeapon();
		InitBullet();
	}

	void Enemy3::InitVar()
	{
		curHp = maxHp = 3;
		scalar = 100.0f;
		timeBulletTarget = 0.0f;
		spawnPos = Vector2(0.0f, 0.0f);
		timeBulletZ = 0.0f;
		timeBulletCircle = 0.0f;
		timeAttackToWalk = 0.0f;
		curBulletIdx = 0;
		curBulletX = 0;
		curBulletY = 0;
		fireState = FireState::none;
	}

	void Enemy3::InitSelf()
	{
		int idx = 0;

		float scaleFactor = 3.0f;
		col->scale = Vector2(16.0f, 16.0f) * scaleFactor;

		idle = new ObImage(L"EnterTheGungeon/Enemy_2/Idle.png");
		idle->isVisible = false;
		idle->maxFrame = Int2(4, 8);
		idle->scale = Vector2(52.0f / 4.0f, 112.0f / 8.0f) * scaleFactor;
		idle->ChangeAnim(AnimState::loop, 0.2f);
		idle->SetParentRT(*col);
		idle->zOrder = ZOrder::object;

		walk = new ObImage(L"EnterTheGungeon/Enemy_2/Walk.png");
		walk->isVisible = false;
		walk->maxFrame = Int2(4, 8);
		walk->scale = Vector2(52.0f / 4.0f, 112.0f / 8.0f) * scaleFactor;
		walk->ChangeAnim(AnimState::loop, 0.1f);
		walk->SetParentRT(*col);
		walk->zOrder = ZOrder::object;

		hit = new ObImage(L"EnterTheGungeon/Enemy_2/Hit.png");
		hit->isVisible = false;
		hit->maxFrame.x = 1;
		hit->scale = Vector2(13.0f, 14.0f) * scaleFactor;
		hit->ChangeAnim(AnimState::once, 0.2f);
		hit->SetParentRT(*col);
		hit->zOrder = ZOrder::object;

		die = new ObImage(L"EnterTheGungeon/Enemy_2/Die.png");
		die->isVisible = false;
		die->maxFrame.x = 2;
		die->scale = Vector2(30.0f / 2.0f, 16.0f) * scaleFactor;
		die->SetParentRT(*col);
		die->zOrder = ZOrder::object;

		attack = new ObImage(L"EnterTheGungeon/Enemy_2/Attack.png");
		attack->isVisible = false;
		attack->maxFrame.x = 13;
		attack->scale = Vector2(247.0f / 13.0f, 19.0f) * scaleFactor;
		attack->SetParentRT(*col);
		attack->zOrder = ZOrder::object;

		attackEnd = new ObImage(L"EnterTheGungeon/Enemy_2/Attack_End.png");
		attackEnd->isVisible = false;
		attackEnd->maxFrame.x = 9;
		attackEnd->scale = Vector2(153.0f / 9.0f, 23.0f) * scaleFactor;
		attackEnd->SetParentRT(*col);
		attackEnd->zOrder = ZOrder::object;

		shadow->scale = Vector2(12.0f, 4.0f) * scaleFactor;
		shadow->SetLocalPosY(-45.0f);
	}

	void Enemy3::InitWeapon()
	{
		weapon = nullptr;
	}

	void Enemy3::InitBullet()
	{
		bullet.resize(bulletMax);
		for (auto& elem : bullet)
		{
			elem = new EnemyBullet;
			elem->idle->SetParentRT(*elem->col);
		}
	}

	void Enemy3::Release()
	{
		Enemy::Release();
	}

	void Enemy3::Update()
	{
		Enemy::Update();
		attack->Update();
		attackEnd->Update();
	}

	void Enemy3::LateUpdate()
	{
		Enemy::LateUpdate();
	}

	void Enemy3::Render()
	{
		Enemy::Render();
		attack->Render();
		attackEnd->Render();
	}

	void Enemy3::Fire()
	{
		switch (fireState)
		{
		case Gungeon::FireState::none:

			if (TIMER->GetTick(timeFire, 1.0f))
			{
				spawnPos = Pos();
				for (auto& elem : bullet)
				{
					elem->scalar = 0.0f;
					elem->moveDir = Vector2(0.0f, 0.0f);
				}

				idle->isVisible = false;
				walk->isVisible = false;

				AttackStart();
				state = State::attack;
				fireState = FireState::z;
			}

			break;
		}
	}

	void Enemy3::Attack()
	{
		switch (fireState)
		{
		case Gungeon::FireState::z:

			if (TIMER->GetTick(timeBulletZ, 0.05f))
			{
				auto plusXY = [&]()
				{
					if (++curBulletX >= 5)
					{
						curBulletX = 0;
						if (++curBulletY >= 5)
						{
							curBulletY = 0;
							AttackEnd();
							fireState = FireState::circle;
						}
					}
					curBulletIdx++;
				};

				StringBulletData stringBullet;
				while (0 == stringBullet.Z[curBulletY][curBulletX])
				{
					plusXY();
				}

				bullet[curBulletIdx]->Spawn(Vector2(spawnPos.x - 50.0f + curBulletX * 20,
					spawnPos.y + 50.0f - curBulletY * 20));

				plusXY();
			}

			break;

		case Gungeon::FireState::circle:

			if (TIMER->GetTick(timeBulletCircle, 0.05f))
			{
				bullet[curBulletIdx++]->Spawn(Vector2(
					spawnPos.x - 10.0f + 80.0f * cos((curBulletIdx - 25) * 20.0f * ToRadian),
					spawnPos.y + 10.0f + 80.0f * sin((curBulletIdx - 25) * 20.0f * ToRadian)));

				if (curBulletIdx >= bulletMax)
				{
					curBulletIdx = 0;
					fireState = FireState::target;
				}
			}

			break;

		case Gungeon::FireState::target:

			for (auto& elem : bullet)
			{
				elem->scalar = 500.0f;
				elem->moveDir = targetDir;
			}

			fireState = FireState::toWalk;

			break;

		case Gungeon::FireState::toWalk:

			if (TIMER->GetTick(timeAttackToWalk, 1.5f))
			{
				AttackToWalk();
				state = State::walk;
				fireState = FireState::none;
			}

			break;
		}
	}
}