#include "stdafx.h"

Bullet::Bullet()
{
    Init();
}

void Bullet::Init()
{
    hitbox.SetWorldPos(Vector2(2000.0f, 2000.0f));
    hitbox.scale = Vector2(25.0f, 25.0f);
    hitbox.rotation = 0.0f;
    hitbox.isVisible = false;
    hitbox.color = Color(0.3f, 1.0f, 0.3f, 1.0f);
    hitEffectTime = 0.0f;
    state = (int)estate::die;
}

void Bullet::Update(ObCircle player)
{
    if (!hitbox.isVisible) return;

    //scalar += 300.0f * DELTA;
    gravity += 600.0f * DELTA;
    velocity = fireDir * scalar + DOWN * gravity;
    
    hitbox.MoveWorldPos(velocity * DELTA);

    hitbox.rotation = Utility::DirToRadian(velocity);

    
    hitbox.Update();

    if (state == (int)estate::hit)
    {
        hitEffectTime += 100.0f * DELTA;
        if (hitEffectTime > 30.0f)
        {
            state = (int)estate::die;
            hitEffectTime = 0.0f;
        }
    }
}

bool Bullet::LateUpdate()
{
    if (hitbox.isVisible and
        (hitbox.GetWorldPos().y >= app.GetHalfHeight() + CAM->position.y or
        hitbox.GetWorldPos().y <= -app.GetHalfHeight() + CAM->position.y or
        hitbox.GetWorldPos().x >= app.GetHalfWidth() + CAM->position.x or
        hitbox.GetWorldPos().x <= -app.GetHalfWidth() + CAM->position.x))
    {
        return HitFrom(999.0f);
    }
    return false;
}

void Bullet::Render()
{
    hitbox.Render();
}


bool Bullet::Shoot(ObCircle player, float scalar, Vector2 firePos)
{
    if (hitbox.isVisible) return false;

    state = (int)estate::alive;
    hitbox.isVisible = true;

    hitbox.SetWorldPos(firePos);
    hitbox.rotation = Utility::DirToRadian(player.GetRight());

    this->scalar = 150.0f + scalar * 7.0f;
    fireDir = player.GetRight();

    gravity = 0.0f;

    return true;
}

bool Bullet::HitFrom(const float damage)
{
    state = (int)estate::hit;
    hitbox.SetWorldPos(Vector2(2000.0f, 2000.0f));
    hitbox.isVisible = false;
    cout << "º® Ãæµ¹! \n";
    return true;
}