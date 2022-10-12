#include "stdafx.h"

namespace Gungeon
{
	Weapon2::Weapon2()
	{
		// 공통
		float scaleFactor = 1.0f;
		float effectScaleFactor = 1.0f;
		float uiWeaponScaleFactor = 1.0f;
		int uiBulletIdx = 0;

		timeFireEffect = 0.0f;

		firePos = new ObRect;
		firePos->isFilled = false;
		firePos->scale = Vector2(10.0f, 10.0f);
		firePos->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
		firePos->SetParentRT(*col);
		firePos->zOrder = ZOrder::none;

		fireEffect = new Effect;

		uiBulletFrame = new UI;

		uiWeapon = new UI;

		uiBulletCount = new UI;
		uiBulletCount->img = new ObImage(L"EnterTheGungeon/Weapon/UI_BulletCount_Infinity.png");
		uiBulletCount->img->scale.x = 60.0f;
		uiBulletCount->img->scale.y = 28.0f;
		uiBulletCount->anchor = Anchor::rightBottom;
		uiBulletCount->img->pivot = OFFSET_RB;
		uiBulletCount->Spawn(-70.0f, 155.0f);
		uiBulletCount->img->space = Space::screen;
		uiBulletCount->img->zOrder = ZOrder::UI;
		uiBulletCount->img->isVisible = false;


		// 차이
		type = WeaponType::shotgun;

		scaleFactor = 2.0f;
		col->scale.x = 29.0f * scaleFactor;
		col->scale.y = 21.0f * scaleFactor;

		idle = new ObImage(L"EnterTheGungeon/Weapon/1/Weapon.png");
		idle->pivot = OFFSET_LB;
		idle->isVisible = true;
		idle->scale.x = 43.0f * scaleFactor;
		idle->scale.y = 11.0f * scaleFactor;
		idle->zOrder = ZOrder::weapon;

		fireEffect->idle = new ObImage(L"EnterTheGungeon/Weapon/1/Effect_Fire.png");
		fireEffect->idle->isVisible = false;
		fireEffect->idle->maxFrame.x = 3;
		fireEffect->idle->scale = Vector2(45.0f / 3.0f, 11.0f) * scaleFactor;
		fireEffect->idle->SetParentRT(*firePos);
		fireEffect->idle->zOrder = ZOrder::none;
		fireEffect->intervalDie = 0.2f;

		imgReloading = new ObImage(L"EnterTheGungeon/Weapon/1/Reloading.png");
		imgReloading->isVisible = false;
		imgReloading->pivot = Vector2(0.4f, 0.25f);
		imgReloading->maxFrame.x = 2;
		imgReloading->scale.x = 42.0f / 2.0f * scaleFactor;
		imgReloading->scale.y = 22.0f * scaleFactor;
		imgReloading->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		imgReloading->zOrder = ZOrder::UI;
		imgReloading->isVisible = false;

		pivotDefault = Vector2(0.6f, 0.25f);
		localPosDefault = Vector2(10.0f, -15.0f);
		localFirePosDefault = Vector2(80.0f, 6.0f);
		state = State::die;

		uiBulletFrame->img = new ObImage(L"EnterTheGungeon/Weapon/1/UI_Magazine.png");
		uiBulletFrame->img->scale = Vector2(28.0f, 124.0f);
		uiBulletFrame->img->pivot = OFFSET_RB;
		uiBulletFrame->anchor = Anchor::rightBottom;
		uiBulletFrame->Spawn(-26.0f, 30.0f);
		uiBulletFrame->img->space = Space::screen;
		uiBulletFrame->img->zOrder = ZOrder::UI;
		uiBulletFrame->img->isVisible = false;

		bulletCount = 7;
		uiBullet.resize(bulletCount);

		uiBulletIdx = 0;
		for (auto& elem : uiBullet)
		{
			elem = new UI;
			elem->img = new ObImage(L"EnterTheGungeon/Weapon/UI_Bullet.png");
			elem->img->scale = Vector2(12.0f, 4.0f);
			elem->anchor = Anchor::rightBottom;
			elem->Spawn(-40.0f, 56.0f + uiBulletIdx * 12.0f);
			elem->img->space = Space::screen;
			elem->img->isVisible = false;
			uiBulletIdx++;
		}

		uiWeaponScaleFactor = 2.5f;
		uiWeapon->img = new ObImage(L"EnterTheGungeon/Weapon/1/UI_Weapon.png");
		uiWeapon->img->scale.x = 45.0f * uiWeaponScaleFactor;
		uiWeapon->img->scale.y = 13.0f * uiWeaponScaleFactor;
		uiWeapon->img->pivot = OFFSET_RB;
		uiWeapon->anchor = Anchor::rightBottom;
		uiWeapon->Spawn(-120.0f, 70.0f);
		uiWeapon->img->space = Space::screen;
		uiWeapon->img->zOrder = ZOrder::UI;
		uiWeapon->img->isVisible = false;
	}

	void Weapon2::Release()
	{
		Weapon::Release();
	}

	void Weapon2::Update()
	{
		Weapon::Update();
	}

	void Weapon2::LateUpdate()
	{
		Weapon::LateUpdate();
	}

	void Weapon2::Render()
	{
		Weapon::Render();
	}

	void Weapon2::ResizeScreen()
	{
		Weapon::ResizeScreen();
	}
}