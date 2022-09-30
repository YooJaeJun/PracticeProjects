#include "stdafx.h"

namespace Gungeon
{
	Character::Character()
	{
		col = nullptr;
		moveDir = Vector2(0.0f, 0.0f);
		scalar = 0.0f;
		curHp = 0;
		maxHp = 0;
		scalar = 0.0f;
		isHit = false;
		state = State::idle;
	}

	void Character::Init()
	{
	}

	void Character::Release()
	{
		SafeDelete(col);
	}

	void Character::Update()
	{
		if (col) col->Update();
	}

	void Character::LateUpdate()
	{}

	void Character::Render()
	{
		if (col) col->Render(); // RENDER->push(col);
	}

	void Character::ResizeScreen()
	{
	}

	void Character::Spawn(const Vector2 wpos)
	{
		SetPosX(wpos.x);
		SetPosY(wpos.y);
	}
}