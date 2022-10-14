#include "stdafx.h"

namespace Gungeon
{
	Enemy2::Enemy2()
	{
		Enemy2::Init();
	}

	void Enemy2::Init()
	{
		InitVar();
		InitSelf();
		InitWeapon();
		InitBullet();
	}

	void Enemy2::InitVar()
	{
		curHp = maxHp = 3;
		scalar = 80.0f;
	}

	void Enemy2::InitSelf()
	{
		int idx = 0;

		float scaleFactor = 3.0f;
		col->scale = Vector2(16.0f, 16.0f) * scaleFactor;

		idle = new ObImage(L"EnterTheGungeon/Enemy_0/Idle.png");
		idle->isVisible = false;
		idle->maxFrame = Int2(2, 8);
		idle->scale = Vector2(28.0f / 2.0f, 192.0f / 8.0f) * scaleFactor;
		idle->ChangeAnim(AnimState::loop, 0.2f);
		idle->SetParentRT(*col);
		idle->zOrder = ZOrder::object;

		walk = new ObImage(L"EnterTheGungeon/Enemy_0/Walk.png");

		idx = 0;
		walk->isVisible = false;
		walk->maxFrame = Int2(6, 8);
		walk->scale = Vector2(96.0f / 6.0f, 192.0f / 8.0f) * scaleFactor;
		walk->ChangeAnim(AnimState::loop, 0.1f);
		walk->SetParentRT(*col);
		walk->zOrder = ZOrder::object;

		hit = new ObImage(L"EnterTheGungeon/Enemy_0/Hit.png");
		hit->isVisible = false;
		hit->maxFrame.x = 1;
		hit->scale = Vector2(16.0f, 24.0f) * scaleFactor;
		hit->ChangeAnim(AnimState::once, 0.2f);
		hit->SetParentRT(*col);
		hit->zOrder = ZOrder::object;

		die = new ObImage(L"EnterTheGungeon/Enemy_0/Die.png");
		die->isVisible = false;
		die->maxFrame.x = 5;
		die->scale = Vector2(110.0f / 5.0f, 22.0f) * scaleFactor;
		die->SetParentRT(*col);
		die->zOrder = ZOrder::object;

		shadow->scale = Vector2(12.0f, 4.0f) * scaleFactor;
		shadow->SetLocalPosY(-35.0f);
	}

	void Enemy2::InitWeapon()
	{
		weapon = new Weapon1;
		weapon->col->SetParentRT(*col);
		weapon->col->SetLocalPos(Vector2(10.0f, -15.0f));
		weapon->idle->SetParentRT(*weapon->col);
		weapon->firePos->SetLocalPos(Vector2(weapon->col->scale.x / 2.0f, 0.0f));
		weapon->fireEffect->idle->SetParentRT(*weapon->firePos);
		weapon->imgReloading->SetParentRT(*weapon->col);
		weapon->Equip();
	}

	void Enemy2::InitBullet()
	{
		bullet.resize(10);
		for (auto& elem : bullet)
		{
			elem = new EnemyBullet;
		}
	}

	void Enemy2::Release()
	{
		Enemy::Release();
	}

	void Enemy2::Update()
	{
		Enemy::Update();
	}

	void Enemy2::LateUpdate()
	{
		Enemy::LateUpdate();
	}

	void Enemy2::Render()
	{
		Enemy::Render();
	}
}