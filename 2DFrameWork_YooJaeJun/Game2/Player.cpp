#include "stdafx.h"

Player::Player()
{
    Init();
}

void Player::Init()
{
    firePos.SetLocalPos(Vector2(160.0f, 0.0f));
    firePos.scale = Vector2(80.0f, 80.0f);
    firePos.isAxis = false;
    firePos.SetParentRT(hitbox);

    muzzle.SetLocalPos(Vector2(0.0f, 0.0f));
    muzzle.scale = Vector2(160.0f, 10.0f);
    muzzle.isAxis = false;
    muzzle.color = Color(0.1f, 0.6f, 0.9f, 1.0f);
    muzzle.pivot = OFFSET_L;
    muzzle.SetParentRT(hitbox);

    shootGauge.SetLocalPos(Vector2(-50.0f, 70.0f));
    shootGauge.scale = Vector2(100.0f, 10.0f);
    shootGauge.rotation = 0.0f;
    shootGauge.isFilled = true;
    shootGauge.color = Color(0.2f, 0.2f, 0.7f, 1.0f);
    shootGauge.pivot = OFFSET_L;
    shootGauge.SetParentT(hitbox);

    shootGaugeFrame.SetLocalPos(Vector2(-50.0f, 70.0f));
    shootGaugeFrame.scale = Vector2(100.0f, 10.0f);
    shootGaugeFrame.isFilled = false;
    shootGaugeFrame.color = Color(0.5f, 0.5f, 0.9f, 1.0f);
    shootGaugeFrame.pivot = OFFSET_L;
    shootGaugeFrame.SetParentT(hitbox);

    hpGauge.SetLocalPos(Vector2(-50.0f, 55.0f));
    hpGauge.scale = Vector2(100.0f, 20.0f);
    hpGauge.rotation = 0.0f;
    hpGauge.isFilled = true;
    hpGauge.color = Color(1.0f, 0.2f, 0.2f, 1.0f);
    hpGauge.pivot = OFFSET_L;
    hpGauge.SetParentT(hitbox);

    hpGaugeFrame.SetLocalPos(Vector2(-50.0f, 55.0f));
    hpGaugeFrame.scale = Vector2(100.0f, 20.0f);
    hpGaugeFrame.isFilled = false;
    hpGaugeFrame.color = Color(0.9f, 0.5f, 0.5f, 1.0f);
    hpGaugeFrame.pivot = OFFSET_L;
    hpGaugeFrame.SetParentT(hitbox);


    Unit::Init();
}

void Player::Update()
{
    firePos.Update();
    muzzle.Update();
    shootGauge.Update();
    shootGaugeFrame.Update();
    hpGauge.Update();
    hpGaugeFrame.Update();


    if (state == (int)estate::hit)
    {
        hitEffectTime += 100.0f * DELTA;
        hitbox.color = Color(1.0f, RANDOM->Float(0.0f, 0.4f), RANDOM->Float(0.0f, 0.4f), 1.0f);
        hitbox.SetWorldPos(Vector2(hitbox.GetWorldPos().x + RANDOM->Float(-2.0f, 2.0f), hitbox.GetWorldPos().y));
        if (hitEffectTime > 30.0f)
        {
            state = (int)estate::alive;
            hitEffectTime = 0.0f;
            hitbox.color = Color(0.2f, 0.2f, 0.8f, 1.0f);
        }
    }


    Unit::Update();
}

bool Player::LateUpdate()
{
    Unit::LateUpdate();
    if (hitbox.isVisible and
        hitbox.GetWorldPos().y <= -app.GetHalfHeight() + CAM->position.y - 100.0f)
    {
        return HitFrom(999.9f);
    }
    return false;
}

void Player::Render()
{
    firePos.Render();
    muzzle.Render();
    shootGauge.Render();
    shootGaugeFrame.Render();
    hpGauge.Render();
    hpGaugeFrame.Render();
    Unit::Render();
}

void Player::Move()
{
    Vector2 pos = hitbox.GetWorldPos();
    if (pos.y > -100.0f)    // 윈도우 켜질 때 키를 누르면 미리 업데이트 되는데 이때 강제 보정
    {
        pos = Vector2(-500.0f, -250.0f);
    }

    if (onGround)
    {
        if (INPUT->KeyPress(VK_RIGHT))
        {
            hitbox.SetWorldPos(pos + RIGHT * 300.0f * DELTA);
        }
        else if (INPUT->KeyPress(VK_LEFT))
        {
            hitbox.SetWorldPos(pos + LEFT * 300.0f * DELTA);
        }
        if (INPUT->KeyPress(VK_UP))
        {
            hitbox.rotation += 100.0f * ToRadian * DELTA;
        }
        else if (INPUT->KeyPress(VK_DOWN))
        {
            hitbox.rotation -= 100.0f * ToRadian * DELTA;
        }
    }
}

void Player::GaugeUp()
{
    if (INPUT->KeyDown(VK_SPACE))
    {
        shootGauge.scale.x = 0.0f;
    }

    if (INPUT->KeyPress(VK_SPACE))
    {
        shootGauge.scale.x += 100.0f * DELTA;

        if (shootGauge.scale.x > 100.0f)
        {
            shootGauge.scale.x = 0.0f;
        }
    }
}

void Player::Down()
{
    gravity = 600.0f * DELTA;
    velocity = DOWN * gravity;
    hitbox.MoveWorldPos(velocity);
}

bool Player::HitFrom(const float damage)
{
    hpGauge.scale.x -= damage;
    state = (int)estate::hit;
    cout << name << " 피격!  Hp " << hpGauge.scale.x << "/" << hpGaugeFrame.scale.x << '\n';
    if (hpGauge.scale.x <= 0.0f)
    {
        hpGauge.scale.x = 0.0f;
        hitbox.SetWorldPos(Vector2(2000.0f, 2000.0f));
        hitbox.isVisible = false;
        cout << "--------------------\n";
        cout << name << "사망!  게임 종료! \n";
        cout << "--------------------\n";
        return true;
    }
    return false;
}
