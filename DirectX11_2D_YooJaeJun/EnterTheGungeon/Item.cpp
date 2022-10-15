#include "stdafx.h"

namespace Gungeon
{
	Item::Item()
	{
		flagAbsorbed = false;
		targetPos = Vector2(0.0f, 0.0f);
		scalar = 600.0f;
	}

	void Item::Release()
	{
		Character::Release();
		SafeDelete(idle);
	}

	void Item::Update()
	{
		if (flagAbsorbed)
		{
			Vector2 dir = targetPos - Pos();
			dir.Normalize();
			col->MoveWorldPos(dir * scalar * DELTA);
		}

		Character::Update();
		idle->Update();
	}

	void Item::LateUpdate()
	{
	}

	void Item::Render()
	{
		Character::Render();
		idle->Render(); // RENDER->push(idle);
	}

	void Item::Hit()
	{
		SetPos(DEFAULTSPAWN);
		idle->isVisible = false;
		flagAbsorbed = false;
		state = State::die;
	}
}