#include "stdafx.h"

Bullet::Bullet()
{
    arrow.SetWorldPos(Vector2(1000.0f, 1000.0f));
    arrow.scale.x = 30.0f;
    arrow.scale.y = 30.0f;
    arrow.rotation = 0.0f;
    arrow.isVisible = false;

    arrowPet.SetWorldPos(Vector2(1000.0f, 1000.0f));
    arrowPet.scale.x = 20.0f;
    arrowPet.scale.y = 20.0f;
    arrowPet.rotation = 0.0f;
    arrowPet.isVisible = false;
    arrowPet.isAxis = true;
    arrowPet.SetParentRT(arrow);
    arrowPet.color = Color(0.3f, 0.3f, 0.8f, 0.5f);
}

void Bullet::Update(ObRect player)
{
    if (!arrow.isVisible) return;

    arrow.MoveWorldPos(arrow.GetRight() * 200.0f * DELTA);
    arrow.Update();

    if (!arrowPet.isVisible) return;
    arrowPet.rotation2 += 400.0f * ToRadian * DELTA;
    arrowPet.Update();

    Vector2 Dis = arrow.GetWorldPos() - player.GetWorldPos();
    float dis = Dis.Length();
    if (dis > 1700.0f)
    {
        arrow.isVisible = false;
        arrowPet.isVisible = false;
    }
}

bool Bullet::Shoot(ObRect player)
{
    if (!arrow.isVisible && !arrowPet.isVisible)
    {
        arrow.isVisible = true;
        arrow.SetWorldPos(player.GetWorldPos());
        arrow.rotation = Utility::DirToRadian(player.GetRight());

        arrowPet.isVisible = true;
        arrowPet.SetLocalPos(Vector2(40.f, 40.f));
        arrow.rotation2 = 0.0f;

        return true;
    }
    return false;
}

void Bullet::Render()
{
    // if (!arrow.isVisible) return;
    // arrow.Render();

    if (!arrowPet.isVisible) return;
    arrowPet.Render();
}
