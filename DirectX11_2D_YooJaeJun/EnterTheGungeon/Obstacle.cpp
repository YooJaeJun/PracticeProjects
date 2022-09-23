#include "stdafx.h"

Obstacle::Obstacle()
{
}

void Obstacle::Release()
{
	SafeDelete(idle);
}

void Obstacle::Update()
{
	idle->Update();
}

void Obstacle::LateUpdate()
{
}

void Obstacle::Render()
{
	idle->Render();
}
