#include "stdafx.h"

namespace Gungeon
{
	Item::Item()
	{
	}

	void Item::Release()
	{
		Character::Release();
		SafeDelete(idle);
	}

	void Item::Update()
	{
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
		col->isVisible = false;
		idle->isVisible = false;

		state = State::die;
	}
}