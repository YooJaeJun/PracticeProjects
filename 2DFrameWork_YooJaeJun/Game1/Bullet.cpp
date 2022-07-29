#include "stdafx.h"

Bullet::Bullet()
{
    arrow.SetWorldPos(Vector2(1000.0f, 1000.0f));
    arrow.scale.x = 30.0f;
    arrow.scale.y = 30.0f;
    arrow.rotation = 0.0f;
    arrow.isVisible = false;

    arrowPet.SetLocalPos(Vector2(1000.0f, 1000.0f));
    arrowPet.scale.x = 20.0f;
    arrowPet.scale.y = 20.0f;
    arrowPet.rotation = 0.0f;
    arrowPet.isVisible = true;
    arrowPet.isAxis = true;
    arrowPet.SetParentRT(arrow);
    arrowPet.isFilled = true;
    arrowPet.color = Color(0.3f, 0.3f, 0.8f, 0.5f);

    isFired = false;
}

void Bullet::Update()
{
    arrow.Update();
}

void Bullet::Render()
{
    arrow.Render();
}
