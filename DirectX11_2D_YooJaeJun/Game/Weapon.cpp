#include "stdafx.h"

Weapon::Weapon()
{
	col = new ObRect;
	col->isFilled = false;
	col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
}

void Weapon::Release()
{
	SafeDelete(idle);
	Character::Release();
}

void Weapon::Update()
{
	idle->Update();
	Character::Update();
}

void Weapon::LateUpdate()
{
}

void Weapon::Render()
{
	idle->Render();
	Character::Render();
}
