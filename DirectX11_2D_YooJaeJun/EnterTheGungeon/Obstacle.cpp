#include "stdafx.h"

namespace Gungeon
{
	Obstacle::Obstacle()
	{
		isOpen = false;

		col = new ObRect;
		col->isFilled = false;
		col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	}

	void Obstacle::Release()
	{
		Character::Release();
		SafeDelete(idle);
	}

	void Obstacle::Update()
	{
		Character::Update();
		idle->Update();
	}

	void Obstacle::LateUpdate()
	{
	}

	void Obstacle::Render()
	{
		idle->Render(); // RENDER->push(idle);
		Character::Render();
	}
}