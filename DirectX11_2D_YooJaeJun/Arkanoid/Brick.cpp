#include "stdafx.h"

void Brick::Hit()
{
    state = eState::hit;
    life--;
    if (life <= 0)
    {
        Destroy();
    }
}

void Brick::HitEffect()
{
    if (state == eState::hit)
    {
        obj->color = Color(RANDOM->Float(0.8f, 1.0f), RANDOM->Float(0.8f, 1.0f), RANDOM->Float(0.8f, 1.0f));
        hitTime += 100.0f * DELTA;
        if (hitTime > 30.0f)
        {
            if (life == 2)
            {
                obj->color = Color(0.9f, 0.7f, 0.0f);
            }
            else if (life == 1)
            {
                obj->color = Color(0.9f, 0.4f, 0.3f);
            }
            hitTime = 0.0f;
            state = eState::idle;
        }
    }
}
