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
		SafeDelete(colTile);
	}

	void Character::Update()
	{
		if (col) col->Update();
		if (colTile) colTile->Update();
	}

	void Character::Update(const bool notRotation)
	{
		if (col) col->Update(notRotation);
		if (colTile) colTile->Update(notRotation);
	}

	void Character::LateUpdate()
	{
	}

	void Character::Render()
	{
		if (col) col->Render(); // RENDER->push(col);
		if (colTile) colTile->Render();	// RENDER->push(colTile);
	}

	void Character::ResizeScreen()
	{
	}

	void Character::Spawn(const Vector2 wpos)
	{
		SetPos(wpos);
		col->Update();
		col->isVisible = true;

		state = State::idle;
		isHit = false;
	}
	void Character::ColToggle()
	{
		col->isVisible = !col->isVisible;
		colTile->isVisible = !colTile->isVisible;
	}
}