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

    arrowSpeed *= 1.002f;
    arrowPetSpeed *= 1.002f;

    arrow.MoveWorldPos(arrow.GetRight() * arrowSpeed * DELTA);
    arrow.Update();

    if (!arrowPet.isVisible) return;
    arrowPet.rotation2 += arrowPetSpeed * ToRadian * DELTA;
    arrowPet.Update();

    Vector2 Dis = arrow.GetWorldPos() - player.GetWorldPos();
    float dis = Dis.Length();
    if (dis > 1700.0f)
    {
        arrow.isVisible = false;
        arrowPet.isVisible = false;
        arrowPet.rotation2 = 0.0f;
    }
}

bool Bullet::Shoot(ObRect player, const float scalar)
{
    if (!arrow.isVisible && !arrowPet.isVisible)
    {
        arrow.isVisible = true;
        arrow.SetWorldPos(player.GetWorldPos());
        arrow.rotation = Utility::DirToRadian(player.GetRight());

        arrowPet.isVisible = true;
        arrowPet.SetLocalPos(Vector2(40.f, 40.f));
        arrow.rotation2 = 0.0f;

        arrowSpeed = 100.0f + scalar * 4.0f;
        arrowPetSpeed = 200.0f + scalar * 4.0f;

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
