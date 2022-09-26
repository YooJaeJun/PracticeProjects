#include "stdafx.h"

Effect::Effect()
{
}

void Effect::Release()
{
	Character::Release();
	SafeDelete(idle);
}

void Effect::Update()
{
	Character::Update();
	idle->Update();
}

void Effect::LateUpdate()
{
}

void Effect::Render()
{
	idle->Render();	// RENDER->push(idle);
	Character::Render();
}
