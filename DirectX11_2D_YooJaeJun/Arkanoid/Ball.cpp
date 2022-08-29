#include "stdafx.h"

void Ball::LastPosUpdate()
{
    lastPos = obj->GetWorldPos();
}


void Ball::Bounce(IntersectPos interPos, bool withBar, Vector2 barDir)
{
    Vector2 direction = obj->GetWorldPos() - lastPos;
    direction.Normalize();

    if (interPos == IntersectPos::leftRight)
    {
        SetDirX(-direction.x);
        obj->SetWorldPos(lastPos);
    }
    else if (interPos == IntersectPos::topBottom)
    {
        SetDirY(-direction.y);
        obj->SetWorldPos(lastPos);
    }
    else if (interPos == IntersectPos::edge)
    {
        SetDir(-direction);
        obj->SetWorldPos(lastPos);
    }

    if (withBar)
    {
        SetDirX(barDir.x);
    }
}

void Ball::SpawnStorm(Vector2 pos)
{
    obj->SetWorldPos(pos);
    obj->color = Color(RANDOM->Float(), RANDOM->Float(), RANDOM->Float(), 1.0f);
    dir = Vector2(RANDOM->Float(-1.0f, 1.0f), RANDOM->Float(0.0f, 1.0f));
    scalar = RANDOM->Float(500.0f, 600.0f);
}