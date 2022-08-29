#include "stdafx.h"

void Unit::Init()
{
	score = 0;
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


void Unit::Move()
{
    Vector2 velocity = dir * scalar * DELTA;
    obj->MoveWorldPos(velocity);
}

void Unit::SetDir(const Vector2 otherDir)
{
    dir = otherDir;
}

void Unit::SetDirX(const float otherDirX)
{
    dir.x = otherDirX;
}

void Unit::SetDirY(const float otherDirY)
{
    dir.y = otherDirY;
}