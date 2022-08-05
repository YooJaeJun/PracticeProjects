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
    if (!arrow.isVisible and !arrowPet.isVisible) return;

    arrowScalar += 600.0f * DELTA;  // 초당 (상수)픽셀
    arrowPetScalar += 500.0f * DELTA;

    arrow.MoveWorldPos(arrow.GetRight() * arrowScalar * DELTA);
    arrow.Update();

    arrowPet.rotation2 += arrowPetScalar * ToRadian * DELTA;
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

        // arrowScalar = -scalar * 2.0f;
        // arrowPetScalar = -scalar * 2.0f;
        arrowScalar = 50.0f + scalar * 10.0f;
        arrowPetScalar = 50.0f + scalar * 15.0f;

        return true;
    }
    return false;
}

void Bullet::Render()
{
    if (!arrow.isVisible and !arrowPet.isVisible) return;
    arrow.Render();
    arrowPet.Render();
}
