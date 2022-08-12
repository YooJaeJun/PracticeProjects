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

    gravity += 600.0f * DELTA;
    Vector2 velocity = fireDir * scalar + DOWN * gravity;
    // cout << "gravity: " << gravity << '\n';

    arrow.MoveWorldPos(velocity * DELTA);

    arrow.rotation = Utility::DirToRadian(velocity);
    arrowPet.rotation2 += 360.0f * ToRadian * DELTA;


    arrow.Update();
    arrowPet.Update();

    /*Vector2 Dis = arrow.GetWorldPos() - player.GetWorldPos();
    float dis = Dis.Length();
    if (dis > 2000.0f)
    {
        arrow.isVisible = false;
        arrowPet.isVisible = false;
    }*/
}

void Bullet::LateUpdate()
{
    // 위
    if (arrow.GetWorldPos().y >= app.GetHalfHeight() + CAM->position.y)
    {
        fireDir.y *= -1.0f;
        gravity *= -1.0f;
        scalar *= 0.7f;

        arrow.SetWorldPosY(app.GetHalfHeight() + CAM->position.y);
    }
    // 아래
    if (arrow.GetWorldPos().y <= -app.GetHalfHeight() + CAM->position.y)
    {
        fireDir.y *= -1.0f;
        gravity *= -1.0f;
        scalar *= 0.7f;
        gravity *= 0.7f;

        arrow.SetWorldPosY(-app.GetHalfHeight() + CAM->position.y);
    }
    // 오른쪽
    if (arrow.GetWorldPos().x >= app.GetHalfWidth() + CAM->position.x)
    {
        fireDir.x *= -1.0f;
        scalar *= 0.7f;

        arrow.SetWorldPosX(app.GetHalfWidth() + CAM->position.x);
    }
    // 왼쪽
    if (arrow.GetWorldPos().x <= -app.GetHalfWidth() + CAM->position.x)
    {
        fireDir.x *= -1.0f;
        scalar *= 0.7f;

        arrow.SetWorldPosX(-app.GetHalfWidth() + CAM->position.x);
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
        this->scalar = 150.0f + scalar * 5.0f;
        arrowPetScalar = 100.0f + scalar * 3.0f;
        fireDir = player.GetRight();

        gravity = 0.0f;
        gravityCoef = 1.9f;

        arrowPet.rotation2 = 0.0f;

        return true;
    }
    return false;
}
