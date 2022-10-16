#include "stdafx.h"

namespace Gungeon
{
	Weapon::Weapon()
	{
		col = new ObRect;
		col->isFilled = false;
		col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
		col->pivot = OFFSET_LB;

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
	}

	void Weapon::Release()
	{
		Character::Release();
		SafeDelete(idle);
		SafeDelete(firePos);
		SafeDelete(fireEffect);
		SafeDelete(imgReloading);

		SafeRelease(uiBulletFrame);
		SafeRelease(uiWeapon);
		SafeRelease(uiBulletCount);
		for (auto& elem : uiBullet) SafeRelease(elem);
	}

	void Weapon::Update()
	{
		Character::Update();

		idle->Update();
		if (firePos) firePos->Update();
		if (fireEffect) fireEffect->Update();
		if (imgReloading) imgReloading->Update();
		if (uiBulletFrame) uiBulletFrame->Update();
		for (auto& elem : uiBullet) if (elem) elem->Update();
		if (uiWeapon) uiWeapon->Update();
		if (uiBulletCount) uiBulletCount->Update();
	}

	void Weapon::LateUpdate()
	{
	}

	void Weapon::Render()
	{
		idle->Render(); // RENDER->push(idle);
		Character::Render();
		if (firePos) firePos->Render();
		if (fireEffect) fireEffect->Render();
		if (imgReloading) imgReloading->Render();
		if (uiBulletFrame) uiBulletFrame->Render();
		for (auto& elem : uiBullet) if (elem) elem->Render();
		if (uiWeapon) uiWeapon->Render();
		if (uiBulletCount) uiBulletCount->Render();
	}

	void Weapon::ResizeScreen()
	{
		int idx = 0;

		uiBulletFrame->Spawn(-40.0f, 80.0f);
		if (uiWeaponFrame) uiWeaponFrame->Spawn(-240.0f, 50.0f);
		uiWeapon->Spawn(-190.0f, 60.0f);
		uiBulletCount->Spawn(-140.0f, 150.0f);

		idx = 0;
		for (auto& elem : uiBullet)
		{
			elem->Spawn(-40.0f, 56.0f + idx * 12.0f);
			idx++;
		}
	}

	void Weapon::Equip()
	{
		col->SetLocalPos(localPosDefault);
		col->pivot = pivotDefault;
		idle->pivot = pivotDefault;
		firePos->SetLocalPos(localFirePosDefault);
		firePos->pivot = pivotDefault;
		if (fireEffect)
		{
			fireEffect->idle->pivot = pivotDefault;
		}
	}

	void Weapon::SwapUvY()
	{
		swap(idle->uv.y, idle->uv.w);
	}

	void Weapon::EquipRight()
	{
		SwapUvY();
		Equip();
	}

	void Weapon::EquipLeft()
	{
		SwapUvY();
		Equip();
		col->SetLocalPosX(-col->GetLocalPos().x);
		col->pivot.y = -pivotDefault.y;
		idle->pivot.y = -pivotDefault.y;
		firePos->SetLocalPosY(col->GetLocalPos().y);
		firePos->pivot.y = -pivotDefault.y;
		if (fireEffect)
		{
			fireEffect->idle->pivot.y = -pivotDefault.y;
		}
	}
}