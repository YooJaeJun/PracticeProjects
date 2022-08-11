#include "stdafx.h"

Unit::Unit()
{
    Init();
}

void Unit::Init()
{
    hitbox.SetWorldPos(Vector2(-500.0f, -300.0f));
    hitbox.scale = Vector2(80.0f, 80.0f);
    hitbox.rotation = 0.0f;
    hitbox.isFilled = true;
    hitbox.isAxis = true;
    hitbox.color = Color(0.2f, 0.2f, 0.8f, 1.0f);
    hitbox.pivot = OFFSET_N;

    firePos.SetLocalPos(Vector2(160.0f, 0.0f));
    firePos.scale = Vector2(80.0f, 80.0f);
    firePos.isAxis = false;
    firePos.SetParentRT(hitbox);


    shootGauge.SetLocalPos(Vector2(-50.0f, 75.0f));
    shootGauge.scale = Vector2(100.0f, 20.0f);
    shootGauge.rotation = 0.0f;
    shootGauge.isFilled = true;
    shootGauge.color = Color(0.2f, 0.2f, 0.7f, 1.0f);
    shootGauge.pivot = OFFSET_L;
    shootGauge.SetParentT(hitbox);

    shootGaugeFrame.SetLocalPos(Vector2(-50.0f, 75.0f));
    shootGaugeFrame.scale = Vector2(100.0f, 20.0f);
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

    hitEffectTime = 0.0f;
    hitState = false;
}

void Unit::Move()
{
    if (INPUT->KeyPress(VK_RIGHT))
    {
        hitbox.SetWorldPos(hitbox.GetWorldPos() += RIGHT * 300.0f * DELTA);
    }
    else if (INPUT->KeyPress(VK_LEFT))
    {
        hitbox.SetWorldPos(hitbox.GetWorldPos() += LEFT * 300.0f * DELTA);
    }
    if (INPUT->KeyPress(VK_UP))
    {
        hitbox.rotation += 200.0f * ToRadian * DELTA;
    }
    else if (INPUT->KeyPress(VK_DOWN))
    {
        hitbox.rotation -= 200.0f * ToRadian * DELTA;
    }
}

void Unit::HitFrom(float damage)
{
    hitState = true;
    hpGauge.scale.x -= damage;
    cout << name << "충돌!  Hp " << hpGauge.scale.x << "/" << hpGaugeFrame.scale.x << '\n';
    if (hpGauge.scale.x <= 0.0f)
    {
        hpGauge.scale.x = 0.0f;
        hitbox.SetWorldPos(Vector2(2000.0f, 2000.0f));
        hitbox.isVisible = false;
        cout << "------------------------------\n";
        cout << name << "사망!  게임 종료! \n";
        cout << "------------------------------\n";
    }
}

void Unit::Update()
{
    if (hitState)
    {
        hitEffectTime += 100.0f * DELTA;
        hitbox.color = Color(1.0f, RANDOM->Float(0.0f, 0.4f), RANDOM->Float(0.0f, 0.4f), 1.0f);
        if (hitEffectTime > 30.0f)
        {
            hitState = false;
            hitEffectTime = 0.0f;
            hitbox.color = Color(0.2f, 0.2f, 0.8f, 1.0f);
        }
    }


    hitbox.Update();
    shootGauge.Update();
    shootGaugeFrame.Update();
    hpGauge.Update();
    hpGaugeFrame.Update();
    firePos.Update();
}

void Unit::LateUpdate()
{
}

void Unit::Render()
{
    hitbox.Render();
    shootGauge.Render();
    shootGaugeFrame.Render();
    hpGauge.Render();
    hpGaugeFrame.Render();
    firePos.Render();
}
