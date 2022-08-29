#include "stdafx.h"

void Mover::Move()
{
    Vector2 velocity = dir * scalar * DELTA;
    obj->MoveWorldPos(velocity);
}

void Mover::SetDir(const Vector2 otherDir)
{
    dir = otherDir;
}

void Mover::SetDirX(const float otherDirX)
{
    dir.x = otherDirX;
}

void Mover::SetDirY(const float otherDirY)
{
    dir.y = otherDirY;
}

void Mover::Ready(const Vector2 pos)
{
    if (fired == false)
    {
        obj->SetWorldPos(pos);
        obj->isVisible = true;
        fired = true;
    }
}