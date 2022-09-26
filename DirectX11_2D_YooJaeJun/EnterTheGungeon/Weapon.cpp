#include "stdafx.h"

Weapon::Weapon()
{
}

void Weapon::Release()
{
	Character::Release();
	SafeDelete(idle);
	SafeDelete(firePos);
}

void Weapon::Update()
{
	Character::Update();
	idle->Update();
	if (firePos) firePos->Update();
}

void Weapon::LateUpdate()
{
}

void Weapon::Render()
{
	idle->Render(); // RENDER->push(idle);
	Character::Render();
	if (firePos) firePos->Render();
}
