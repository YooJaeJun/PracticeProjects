#include "stdafx.h"

Weapon::Weapon()
{
}

void Weapon::Release()
{
	Character::Release();
	SafeDelete(idle);
}

void Weapon::Update()
{
	Character::Update();
	idle->Update();
}

void Weapon::LateUpdate()
{
}

void Weapon::Render()
{
	idle->Render();
	Character::Render();
}
