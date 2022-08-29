#include "stdafx.h"

void Unit::Init()
{
}

void Unit::Update()
{
	obj->Update();
}

void Unit::LateUpdate()
{
}

void Unit::Render()
{
	obj->Render();
}

void Unit::Release()
{
	delete obj;
}

void Unit::Destroy(Vector2 pos)
{
	obj->SetWorldPos(pos);
	obj->isVisible = false;
}