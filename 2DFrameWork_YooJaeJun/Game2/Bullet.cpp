#include "stdafx.h"

Bullet::Bullet()
{
    hitbox.SetWorldPos(Vector2(2000.0f, 2000.0f));
    hitbox.scale = Vector2(15.0f, 15.0f);
    hitbox.rotation = 0.0f;
    hitbox.isVisible = false;
    hitbox.color = Color(0.3f, 1.0f, 0.3f, 1.0f);
}

void Bullet::Update(ObCircle player)
{
    if (!hitbox.isVisible) return;

    //scalar += 300.0f * DELTA;

    gravity += 600.0f * DELTA;
    Vector2 velocity = fireDir * scalar + DOWN * gravity;
    
    hitbox.MoveWorldPos(velocity * DELTA);

    hitbox.rotation = Utility::DirToRadian(velocity);

    
    hitbox.Update();

    Vector2 Dis = hitbox.GetWorldPos() - player.GetWorldPos();
    float dis = Dis.Length();
    if (dis > 2000.0f)
    {
        hitbox.isVisible = false;
    }
}

void Bullet::LateUpdate()
{
    if (hitbox.isVisible and
        (hitbox.GetWorldPos().y >= app.GetHalfHeight() + CAM->position.y or
        hitbox.GetWorldPos().y <= -app.GetHalfHeight() + CAM->position.y or
        hitbox.GetWorldPos().x >= app.GetHalfWidth() + CAM->position.x or
        hitbox.GetWorldPos().x <= -app.GetHalfWidth() + CAM->position.x))
    {
        hitbox.SetWorldPos(Vector2(2000.0f, 2000.0f));
        hitbox.isVisible = false;
        cout << "º® Ãæµ¹! \n";
    }
}

void Bullet::Render()
{
    hitbox.Render();
}

bool Bullet::Shoot(ObCircle player, float scalar, Vector2 firePos)
{
    if (hitbox.isVisible) return false;

    hitbox.isVisible = true;

    hitbox.SetWorldPos(firePos);
    hitbox.rotation = Utility::DirToRadian(player.GetRight());

    this->scalar = 150.0f + scalar * 7.0f;
    fireDir = player.GetRight();

    gravity = 0.0f;

    return true;
}
