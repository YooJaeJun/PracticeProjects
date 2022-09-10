#include "stdafx.h"

void Character::Init()			
{
	hp = 1;
}

void Character::Release()
{
	SafeDelete(col);
}

void Character::Update()
{
	col->Update();
}

void Character::LateUpdate()
{
}

void Character::Render()
{
	col->Render();
}