#include "stdafx.h"

namespace Gungeon
{
	Weapon1::Weapon1()
	{
		float scaleFactor = 1.0f;
		float effectScaleFactor = 1.0f;
		float uiWeaponScaleFactor = 1.0f;
		int uiBulletIdx = 0;

		// ����
		type = WeaponType::pistol;

		scaleFactor = 1.5f;
		col->scale.x = 30.0f * scaleFactor;
		col->scale.y = 22.0f * scaleFactor;

		idle = new ObImage(L"EnterTheGungeon/Weapon/0/Weapon.png");
		idle->isVisible = true;
		idle->scale = Vector2(30.0f, 22.0f) * scaleFactor;
		idle->zOrder = ZOrder::weapon;

		effectScaleFactor = 3.0f;
		fireEffect->idle = new ObImage(L"EnterTheGungeon/Weapon/0/Effect_Fire.png");
		fireEffect->idle->isVisible = false;
		fireEffect->idle->maxFrame.x = 3;
		fireEffect->idle->scale = Vector2(45.0f / 3.0f, 11.0f) * effectScaleFactor;
		fireEffect->idle->SetParentRT(*firePos);
		fireEffect->idle->zOrder = ZOrder::none;
		fireEffect->intervalDie = 0.2f;

		imgReloading = new ObImage(L"EnterTheGungeon/Weapon/0/Reloading.png");
		imgReloading->isVisible = false;
		imgReloading->pivot = Vector2(0.4f, 0.25f);
		imgReloading->maxFrame.x = 2;
		imgReloading->scale = Vector2(42.0f / 2.0f, 22.0f) * scaleFactor;
		imgReloading->ChangeAnim(AnimState::loop, 0.1f);
		imgReloading->zOrder = ZOrder::UI;
		imgReloading->isVisible = false;

		pivotDefault = Vector2(0.4f, 0.25f);
		localPosDefault = Vector2(18.0f, -15.0f);
		localFirePosDefault = Vector2(40.0f, 12.0f);


		uiBulletFrame->img = new ObImage(L"EnterTheGungeon/Weapon/0/UI_Magazine.png");
		uiBulletFrame->img->scale = Vector2(28.0f, 99.0f);
		uiBulletFrame->img->pivot = OFFSET_RB;
		uiBulletFrame->anchor = Anchor::rightBottom;
		uiBulletFrame->Spawn(-26.0f, 30.0f);
		uiBulletFrame->img->space = Space::screen;
		uiBulletFrame->img->zOrder = ZOrder::UI;
		uiBulletFrame->img->isVisible = false;

		bulletCount = 5;
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

		uiWeapon->img = new ObImage(L"EnterTheGungeon/Weapon/0/UI_Weapon.png");
		uiWeapon->img->scale = Vector2(60.0f, 48.0f) * uiWeaponScaleFactor;
		uiWeapon->img->pivot = OFFSET_RB;
		uiWeapon->anchor = Anchor::rightBottom;
		uiWeapon->Spawn(-120.0f, 60.0f);
		uiWeapon->img->space = Space::screen;
		uiWeapon->img->zOrder = ZOrder::UI;
		uiWeapon->img->isVisible = false;
	}

	void Weapon1::Release()
	{
		Weapon::Release();
	}

	void Weapon1::Update()
	{
		Weapon::Update();
	}

	void Weapon1::LateUpdate()
	{
		Weapon::LateUpdate();
	}

	void Weapon1::Render()
	{
		Weapon::Render();
	}

	void Weapon1::ResizeScreen()
	{
		Weapon::ResizeScreen();
	}
}