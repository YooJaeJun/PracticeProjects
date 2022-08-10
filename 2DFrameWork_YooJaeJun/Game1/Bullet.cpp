#include "stdafx.h"

Bullet::Bullet()
{
    arrow.SetWorldPos(Vector2(2000.0f, 2000.0f));
    arrow.scale.x = 30.0f;
    arrow.rotation = 0.0f;
    arrow.isVisible = false;
    //isFired = false;

    arrowPet.SetLocalPos(Vector2(30.0f, 30.0f));
    arrowPet.scale = Vector2(15.0f, 15.0f);
    arrowPet.isVisible = false;
    arrowPet.isAxis = true;
    arrowPet.SetParentRT(arrow);
    arrowPet.color = Color(0.3f, 0.3f, 0.8f, 0.5f);
}

void Bullet::Update(ObRect player)
{
    if (!arrow.isVisible) return;
    if (!arrowPet.isVisible) return;

    //scalar += 300.0f * DELTA;

    // gravity += 600.0f * DELTA;
    // Vector2 velocity = fireDir * arrowScalar + DOWN * gravity;


    Vector2 arrowPos = arrow.GetWorldPos();
    float halfWidth = app.GetHalfWidth();
    float halfHeight = app.GetHalfHeight();
    Vector2 cameraPos = CAM->position;
    Vector2 velocity;
    
    // x 초과
    if (arrowPos.x < -halfWidth + cameraPos.x ||
        arrowPos.x > halfWidth + cameraPos.x)
    {
        fireDir.x = -fireDir.x;
        velocity = fireDir * arrowScalar;
        if (arrowPos.x < -halfWidth + cameraPos.x)
            arrow.SetWorldPosX(-halfWidth + cameraPos.x);

        else if (arrowPos.x > halfWidth + cameraPos.x)
            arrow.SetWorldPosX(halfWidth + cameraPos.x);
    }
    // y 초과
    else if (arrowPos.y < -halfHeight + cameraPos.y ||
        arrowPos.y > halfHeight + cameraPos.y)
    {
        fireDir.y = -fireDir.y;
        velocity = fireDir * arrowScalar;
        if (arrowPos.y < -halfHeight + cameraPos.y)
            arrow.SetWorldPosY(-halfHeight + cameraPos.y);

        else if (arrowPos.y > halfHeight + cameraPos.y)
            arrow.SetWorldPosY(halfHeight + cameraPos.y);
    }
    // 일반
    else
    {
        velocity = fireDir * arrowScalar;
        arrow.MoveWorldPos(velocity * DELTA);
    }

    arrowPet.rotation2 += 360.0f * ToRadian * DELTA;

    arrow.rotation = Utility::DirToRadian(velocity);




    arrow.Update();
    arrowPet.Update();

    Vector2 Dis = arrow.GetWorldPos() - player.GetWorldPos();

    float dis = Dis.Length();

    if (dis > 2000.0f)
    {
        arrow.isVisible = false;
        arrowPet.isVisible = false;
    }
}

void Bullet::Render()
{
    arrow.Render();
    arrowPet.Render();
}

bool Bullet::Shoot(ObRect player, float scalar, Vector2 firePos)
{
    if (!arrow.isVisible)
    {
        arrow.isVisible = true;
        arrowPet.isVisible = true;

        arrow.SetWorldPos(firePos);
        arrow.rotation = Utility::DirToRadian(player.GetRight());

        //              150 ~ 450
        //this->scalar = -scalar * 5.0f;
        arrowScalar = 150.0f + scalar * 5.0f;
        arrowPetScalar = 100.0f + scalar * 3.0f;
        fireDir = player.GetRight();

        gravity = 0.0f;

        arrowPet.rotation2 = 0.0f;

        return true;
    }
    return false;
}
