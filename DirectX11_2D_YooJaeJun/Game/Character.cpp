#include "stdafx.h"

Character::Character()
{
	moveDir = Vector2(0.0f, 0.0f);
	scalar = 0.0f;
	curHp = 0;
	maxHp = 0;
	scalar = 0.0f;
	state = State::idle;
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
	if (col) col->Render();
}