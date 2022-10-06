#include "stdafx.h"

namespace Gungeon
{
	Obstacle::Obstacle()
	{
		isOpen = false;

		col = new ObRect;
		col->isFilled = false;
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
		Character::Render();
		idle->Render(); // RENDER->push(idle);
	}
}