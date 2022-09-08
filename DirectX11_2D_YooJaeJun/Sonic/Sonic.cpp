#include "stdafx.h"

void Sonic::Init()
{
    Character::Init();
    speed = 0.0f;
    hp = 5;

    col = new ObRect();
    col->scale = Vector2(192.0f / 4.0f * 2.0f, 60.0f * 2.0f);
    col->collider = COLLIDER::RECT;
    col->isFilled = false;
    col->color = Color(1.0f, 1.0f, 1.0f);
    col->pivot = OFFSET_B;
    col->SetWorldPosX(-300.0f);
    col->SetWorldPosY(-app.GetHalfHeight() + 48.0f * 3.0f);

    run = new ObImage(L"run.bmp");
    run->scale = Vector2(192.0f / 4.0f * 2.0f, 60.0f * 2.0f);
    run->SetParentRT(*col);
    run->uv = Vector4(0.0f, 0.0f, 1.0f / 4.0f, 1.0f);
    run->pivot = OFFSET_B;
    run->maxFrame.x = 4;
    run->ChangeAnim(ANIMSTATE::LOOP, 0.05f);

    spin = new ObImage(L"spin.bmp");
    spin->scale = Vector2(240.0f / 5.0f * 2.0f, 48.0f * 2.0f);
    spin->SetParentRT(*col);
    spin->uv = Vector4(0.0f, 0.0f, 1.0f / 5.0f, 1.0f);
    spin->isVisible = false;
    spin->pivot = OFFSET_B;
    spin->maxFrame.x = 5;
    spin->ChangeAnim(ANIMSTATE::ONCE, 0.05f);

    timerRun = 0.0f;
    intervalRun = 0.05f;
    timerSpin = 0.0f;
    intervalSpin = 0.05f;
    timerSpin2 = 0.0f;
    intervalSpin2 = 0.5f;

    gravity = 0.0f;
    onGround = false;

    timerHit = 0.0f;
    intervalHit = 1.5f;

    camOriginPos = CAM->position;
}

void Sonic::Release()
{
    Character::Release();
    SafeDelete(run);
    SafeDelete(spin);
}

void Sonic::Update()
{
    Character::Update();

    ImGui::SliderInt("Hp", &hp, 0, 5);
    if (hp <= 0)
    {
        hp = 0;
        ImGui::Text("You are dead, but the test must go on.");
    }

    Vector2 velocity = DOWN * gravity * DELTA;
    col->MoveWorldPos(velocity);

    // 런, 스핀 애니
    if (state == State::run)
    {
        col->scale = run->scale;
        run->isVisible = true;
        spin->isVisible = false;
        timerSpin = 0.0f;
        timerSpin2 = 0.0f;

        // run->spin
        if (INPUT->KeyDown(VK_DOWN))
        {
            state = State::spin;

            run->isVisible = false;
            spin->isVisible = true;
            col->scale = spin->scale;
            spin->ChangeAnim(ANIMSTATE::ONCE, 0.05f);
        }

        // run->jump
        if (INPUT->KeyDown(VK_SPACE))
        {
            gravity = -800.0f;
            // jump상태가 된 직후 Main의 LateUpdate에서 충돌이 일어나 다시 run상태가 되어버리는 문제 해결 위함
            Vector2 velocity = DOWN * gravity * DELTA;
            col->MoveWorldPos(velocity);
            col->Update();

            state = State::jump;
            onGround = false;

            run->isVisible = false;
            spin->isVisible = true;
            col->scale = spin->scale;
            spin->ChangeAnim(ANIMSTATE::ONCE, 0.05f);
        }
    }
    else if (state == State::spin)
    {
        // spin->run
        if (INPUT->KeyUp(VK_DOWN))
        {
            state = State::run;
        }
        // spin->jump
        if (INPUT->KeyDown(VK_SPACE))
        {
            gravity = -800.0f;
            state = State::jump;
            onGround = false;
        }
    }
    else if (state == State::jump)
    {
        gravity += 1500.0f * DELTA;

        // jump->doubleJump
        if (INPUT->KeyDown(VK_SPACE))
        {
            gravity = -800.0f;
            state = State::doubleJump;
        }

        // jump->run
        if (onGround)
        {
            gravity = 0.0f;
            col->SetWorldPosY(lastPos.y);        // 착지 시 한 번 더 뚫고 들어가는 문제 해결 위함
            col->Update();
            state = State::run;
        }
    }
    else if (state == State::doubleJump)
    {  
        gravity += 1500.0f * DELTA;
        col->scale = spin->scale;

        // doubleJump->run
        if (onGround)
        {
            gravity = 0.0f;
            col->SetWorldPosY(lastPos.y);       // 착지 시 한 번 더 뚫고 들어가는 문제 해결 위함
            col->Update();
            state = State::run;
        }
    }

    if ((int)state != 0) cout << (int)state << '\n';

    if (hit)
    {
        timerHit += 1.0f * DELTA;
        run->color = Color(RANDOM->Float(0.8f, 1.0f), RANDOM->Float(0.4f, 0.6f), RANDOM->Float(0.4f, 0.6f));
        spin->color = Color(RANDOM->Float(0.8f, 1.0f), RANDOM->Float(0.4f, 0.6f), RANDOM->Float(0.4f, 0.6f));
        // CAM->position.x = RANDOM->Float(CAM->position.x - 2.0f, CAM->position.x + 2.0f);
        CAM->position.x = RANDOM->Float(CAM->position.x - 2.0f, CAM->position.x + 2.0f);
        if (TIMER->GetTick(timerHit, intervalHit))
        {
            run->color = Color(0.5f, 0.5f, 0.5f);
            spin->color = Color(0.5f, 0.5f, 0.5f);
            timerHit = 0.0f;
            CAM->position = camOriginPos;
            hit = false;
        }
    }

    run->Update();
    spin->Update();

    lastPos = col->GetWorldPos();
    lastState = state;
}

void Sonic::LateUpdate()
{
}

void Sonic::Render()
{
    Character::Render();
    run->Render();
    spin->Render();
}

void Sonic::Fall()
{
    if (false == onGround)
    {
        if (lastState == State::run) state = State::doubleJump;
        else state = lastState;
    }
}

void Sonic::Hit()
{
    if (false == hit)
    {
        hp--;
    }
    hit = true;
}