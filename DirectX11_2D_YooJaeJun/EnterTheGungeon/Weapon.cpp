#include "stdafx.h"

namespace Gungeon
{
	Weapon::Weapon()
	{
		timeFireEffect = 0.0f;
	}

	void Weapon::Release()
	{
		Character::Release();
		SafeDelete(idle);
		SafeDelete(firePos);
		SafeDelete(fireEffect);
	}

	void Weapon::Update()
	{
		Character::Update();

		idle->Update();
		if (firePos) firePos->Update();

		if (fireEffect && fireEffect->idle->isVisible)
		{
			if (TIMER->GetTick(timeFireEffect, 0.2f))
			{
				fireEffect->idle->isVisible = false;
			}
			fireEffect->Update();
		}
	}

	void Weapon::LateUpdate()
	{
	}

	void Weapon::Render()
	{
		idle->Render(); // RENDER->push(idle);
		Character::Render();
		// if (firePos) firePos->Render();
		if (fireEffect) fireEffect->Render();
	}

	void Weapon::EquipRight()
	{
		swap(idle->uv.y, idle->uv.w);
		col->SetLocalPosX(18.0f);
		col->pivot = Vector2(0.4f, 0.25f);
		idle->pivot = Vector2(0.4f, 0.25f);
		firePos->SetLocalPosX(40.0f);
		firePos->SetLocalPosY(12.0f);
		firePos->pivot = Vector2(0.4f, 0.25f);
		if (fireEffect)
		{
			fireEffect->idle->pivot = Vector2(0.4f, 0.25f);
		}
	}

	void Weapon::EquipLeft()
	{
		swap(idle->uv.y, idle->uv.w);
		col->SetLocalPosX(-18.0f);
		col->pivot = Vector2(0.4f, -0.25f);
		idle->pivot = Vector2(0.4f, -0.25f);
		firePos->SetLocalPosX(40.0f);
		firePos->SetLocalPosY(-6.0f);
		firePos->pivot = Vector2(0.4f, -0.25f);
		if (fireEffect)
		{
			fireEffect->idle->pivot = Vector2(0.4f, -0.25f);
		}
	}
}