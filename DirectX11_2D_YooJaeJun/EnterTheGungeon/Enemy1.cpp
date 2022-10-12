#include "stdafx.h"

namespace Gungeon
{
	Enemy1::Enemy1()
	{
		Enemy1::Init();
	}

	void Enemy1::Init()
	{
		InitVar();
		InitSelf();
		InitWeapon();
		InitBullet();
	}

	void Enemy1::InitVar()
	{
		curHp = maxHp = 3;
		scalar = 80.0f;
	}

	void Enemy1::InitSelf()
	{
		int idx = 0;

		float scaleFactor = 3.0f;
		col->scale.x = 16.0f * scaleFactor;
		col->scale.y = 16.0f * scaleFactor;

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
			elem2->isVisible = false;
			elem2->maxFrame.x = 2;
			elem2->scale.x = 28.0f / 2.0f * scaleFactor;
			elem2->scale.y = 24.0f * scaleFactor;
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
			elem2->scale.x = 96.0f / 6.0f * scaleFactor;
			elem2->scale.y = 24.0f * scaleFactor;
			elem2->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
			elem2->SetParentRT(*col);
			elem2->zOrder = ZOrder::object;
			idx++;
		}

		hit = new ObImage(L"EnterTheGungeon/Enemy_0/Hit.png");
		hit->isVisible = false;
		hit->maxFrame.x = 1;
		hit->scale.x = 16.0f * scaleFactor;
		hit->scale.y = 24.0f * scaleFactor;
		hit->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
		hit->SetParentRT(*col);
		hit->zOrder = ZOrder::object;

		die = new ObImage(L"EnterTheGungeon/Enemy_0/Die.png");
		die->isVisible = false;
		die->maxFrame.x = 5;
		die->scale.x = 110.0f / 5.0f * scaleFactor;
		die->scale.y = 22.0f * scaleFactor;
		die->SetParentRT(*col);
		die->zOrder = ZOrder::object;

		shadow->scale.x = 12.0f * scaleFactor;
		shadow->scale.y = 4.0f * scaleFactor;
		shadow->SetWorldPosY(-35.0f);
	}

	void Enemy1::InitWeapon()
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

	void Enemy1::InitBullet()
	{
		bullet.resize(10);
		for (auto& elem : bullet)
		{
			elem = new EnemyBullet;
		}
	}

	void Enemy1::Release()
	{
		Enemy::Release();
	}

	void Enemy1::Update()
	{
		Enemy::Update();
	}

	void Enemy1::LateUpdate()
	{
		Enemy::LateUpdate();
	}

	void Enemy1::Render()
	{
		Enemy::Render();
	}
}