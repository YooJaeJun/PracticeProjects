#include "stdafx.h"

Obstacle::Obstacle()
{
	isOpen = false;
}

void Obstacle::Release()
{
	Character::Release();
	SafeDelete(idle);
}

void Obstacle::Update()
{
	Character::Update();
	idle->Update();
}

void Obstacle::LateUpdate()
{
}

void Obstacle::Render()
{
	Character::Render();
	idle->Render(); // RENDER->push(idle);
}
