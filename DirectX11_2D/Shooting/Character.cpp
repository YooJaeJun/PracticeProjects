#include "stdafx.h"

void Character::Init()
{
	maxHp = 1;
	curHp = 1;
}

void Character::Release()
{
	if (idle) SafeDelete(idle);
	if (col) SafeDelete(col);
}

void Character::Update()
{
	if (idle) idle->Update();
	if (col) col->Update();
}

void Character::LateUpdate()
{
}

void Character::Render()
{
	if (idle) idle->Render();
	if (col) col->Render();
}