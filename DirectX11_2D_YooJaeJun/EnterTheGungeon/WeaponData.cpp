#include "stdafx.h"

namespace Gungeon
{
	WeaponData::WeaponData()
	{
		// °øÅë
		float scaleFactor = 1.0f;
		float effectScaleFactor = 1.0f;
		float uiWeaponScaleFactor = 1.0f;
		int uiBulletIdx = 0;

		for (auto& elem : data)
		{
			elem = new Weapon;

			elem->timeFireEffect = 0.0f;

			elem->col = new ObRect;
			elem->col->isVisible = false;
			elem->col->isFilled = false;
			elem->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
			elem->col->pivot = OFFSET_LB;

			elem->firePos = new ObRect;
			elem->firePos->isFilled = false;
			elem->firePos->scale = Vector2(10.0f, 10.0f);
			elem->firePos->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
			elem->firePos->SetParentRT(*elem->col);
			elem->firePos->zOrder = ZOrder::none;

			elem->fireEffect = new Effect;

			elem->uiBulletFrame = new UI;

			elem->uiWeapon = new UI;

			elem->uiBulletCount = new UI;
			elem->uiBulletCount->img = new ObImage(L"EnterTheGungeon/Weapon/UI_BulletCount_Infinity.png");
			elem->uiBulletCount->img->scale.x = 60.0f;
			elem->uiBulletCount->img->scale.y = 28.0f;
			elem->uiBulletCount->anchor = Anchor::rightBottom;
			elem->uiBulletCount->img->pivot = OFFSET_RB;
			elem->uiBulletCount->Spawn(-70.0f, 155.0f);
			elem->uiBulletCount->img->space = Space::screen;
			elem->uiBulletCount->img->zOrder = ZOrder::UI;
			elem->uiBulletCount->img->isVisible = false;
		}


		// ±ÇÃÑ
		scaleFactor = 1.5f;

		data[0]->type = WeaponType::pistol;

		data[0]->col->scale.x = 30.0f * scaleFactor;
		data[0]->col->scale.y = 22.0f * scaleFactor;

		data[0]->idle = new ObImage(L"EnterTheGungeon/Weapon/0/Weapon.png");
		data[0]->idle->isVisible = true;
		data[0]->idle->scale.x = 30.0f * scaleFactor;
		data[0]->idle->scale.y = 22.0f * scaleFactor;
		data[0]->idle->zOrder = ZOrder::weapon;

		effectScaleFactor = 3.0f;
		data[0]->fireEffect->idle = new ObImage(L"EnterTheGungeon/Weapon/0/Effect_Fire.png");
		data[0]->fireEffect->idle->isVisible = false;
		data[0]->fireEffect->idle->maxFrame.x = 3;
		data[0]->fireEffect->idle->scale = Vector2(45.0f / 3.0f, 11.0f) * effectScaleFactor;
		data[0]->fireEffect->idle->SetParentRT(*data[0]->firePos);
		data[0]->fireEffect->idle->zOrder = ZOrder::none;
		data[0]->fireEffect->intervalDie = 0.2f;

		data[0]->imgReloading = new ObImage(L"EnterTheGungeon/Weapon/0/Reloading.png");
		data[0]->imgReloading->isVisible = false;
		data[0]->imgReloading->pivot = Vector2(0.4f, 0.25f);
		data[0]->imgReloading->maxFrame.x = 2;
		data[0]->imgReloading->scale.x = 42.0f / 2.0f * scaleFactor;
		data[0]->imgReloading->scale.y = 22.0f * scaleFactor;
		data[0]->imgReloading->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		data[0]->imgReloading->zOrder = ZOrder::UI;
		data[0]->imgReloading->isVisible = false;

		data[0]->pivotDefault = Vector2(0.4f, 0.25f);
		data[0]->localPosDefault = Vector2(18.0f, -15.0f);
		data[0]->localFirePosDefault = Vector2(40.0f, 12.0f);


		data[0]->uiBulletFrame->img = new ObImage(L"EnterTheGungeon/Weapon/0/UI_Magazine.png");
		data[0]->uiBulletFrame->img->scale = Vector2(28.0f, 99.0f);
		data[0]->uiBulletFrame->img->pivot = OFFSET_RB;
		data[0]->uiBulletFrame->anchor = Anchor::rightBottom;
		data[0]->uiBulletFrame->Spawn(-26.0f, 30.0f);
		data[0]->uiBulletFrame->img->space = Space::screen;
		data[0]->uiBulletFrame->img->zOrder = ZOrder::UI;
		data[0]->uiBulletFrame->img->isVisible = false;

		data[0]->bulletCount = 5;
		data[0]->uiBullet.resize(data[0]->bulletCount);

		uiBulletIdx = 0;
		for (auto& elem : data[0]->uiBullet)
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

		data[0]->uiWeapon->img = new ObImage(L"EnterTheGungeon/Weapon/0/UI_Weapon.png");
		data[0]->uiWeapon->img->scale.x = 60.0f;
		data[0]->uiWeapon->img->scale.y = 48.0f;
		data[0]->uiWeapon->img->pivot = OFFSET_RB;
		data[0]->uiWeapon->anchor = Anchor::rightBottom;
		data[0]->uiWeapon->Spawn(-120.0f, 60.0f);
		data[0]->uiWeapon->img->space = Space::screen;
		data[0]->uiWeapon->img->zOrder = ZOrder::UI;
		data[0]->uiWeapon->img->isVisible = false;




		// ¼¦°Ç
		scaleFactor = 2.0f;

		data[1]->type = WeaponType::shotgun;

		data[1]->col->scale.x = 29.0f * scaleFactor;
		data[1]->col->scale.y = 21.0f * scaleFactor;

		data[1]->idle = new ObImage(L"EnterTheGungeon/Weapon/1/Weapon.png");
		data[1]->idle->pivot = OFFSET_LB;
		data[1]->idle->isVisible = true;
		data[1]->idle->scale.x = 43.0f * scaleFactor;
		data[1]->idle->scale.y = 11.0f * scaleFactor;
		data[1]->idle->zOrder = ZOrder::weapon;

		effectScaleFactor = 2.0f;
		data[1]->fireEffect->idle = new ObImage(L"EnterTheGungeon/Weapon/1/Effect_Fire.png");
		data[1]->fireEffect->idle->isVisible = false;
		data[1]->fireEffect->idle->maxFrame.x = 3;
		data[1]->fireEffect->idle->scale = Vector2(45.0f / 3.0f, 11.0f) * effectScaleFactor;
		data[1]->fireEffect->idle->SetParentRT(*data[0]->firePos);
		data[1]->fireEffect->idle->zOrder = ZOrder::none;
		data[1]->fireEffect->intervalDie = 0.2f;

		data[1]->imgReloading = new ObImage(L"EnterTheGungeon/Weapon/1/Reloading.png");
		data[1]->imgReloading->isVisible = false;
		data[1]->imgReloading->pivot = Vector2(0.4f, 0.25f);
		data[1]->imgReloading->maxFrame.x = 2;
		data[1]->imgReloading->scale.x = 42.0f / 2.0f * scaleFactor;
		data[1]->imgReloading->scale.y = 22.0f * scaleFactor;
		data[1]->imgReloading->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		data[1]->imgReloading->zOrder = ZOrder::UI;
		data[1]->imgReloading->isVisible = false;

		data[1]->pivotDefault = Vector2(0.6f, 0.25f);
		data[1]->localPosDefault = Vector2(10.0f, -15.0f);
		data[1]->localFirePosDefault = Vector2(80.0f, 6.0f);
		data[1]->state = State::die;

		data[1]->uiBulletFrame->img = new ObImage(L"EnterTheGungeon/Weapon/1/UI_Magazine.png");
		data[1]->uiBulletFrame->img->scale = Vector2(28.0f, 124.0f);
		data[1]->uiBulletFrame->img->pivot = OFFSET_RB;
		data[1]->uiBulletFrame->anchor = Anchor::rightBottom;
		data[1]->uiBulletFrame->Spawn(-26.0f, 30.0f);
		data[1]->uiBulletFrame->img->space = Space::screen;
		data[1]->uiBulletFrame->img->zOrder = ZOrder::UI;
		data[1]->uiBulletFrame->img->isVisible = false;

		data[1]->bulletCount = 7;
		data[1]->uiBullet.resize(data[1]->bulletCount);

		uiBulletIdx = 0;
		for (auto& elem : data[1]->uiBullet)
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
		data[1]->uiWeapon->img = new ObImage(L"EnterTheGungeon/Weapon/1/UI_Weapon.png");
		data[1]->uiWeapon->img->scale.x = 45.0f * uiWeaponScaleFactor;
		data[1]->uiWeapon->img->scale.y = 13.0f * uiWeaponScaleFactor;
		data[1]->uiWeapon->img->pivot = OFFSET_RB;
		data[1]->uiWeapon->anchor = Anchor::rightBottom;
		data[1]->uiWeapon->Spawn(-120.0f, 70.0f);
		data[1]->uiWeapon->img->space = Space::screen;
		data[1]->uiWeapon->img->zOrder = ZOrder::UI;
		data[1]->uiWeapon->img->isVisible = false;
	}
}