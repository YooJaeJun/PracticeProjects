#include "stdafx.h"

void Character::Init()			
{
	speed = 0.0f;
	hp = 1;
}

void Character::Release()
{
	SafeDelete(col);
}

void Character::Update()
{
	speed += 0.15f * DELTA;
	col->Update();
}

void Character::LateUpdate()
{
}

void Character::Render()
{
	col->Render();
}