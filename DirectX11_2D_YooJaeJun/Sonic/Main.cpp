#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    sonic = new ObRect();
    sonic->scale = Vector2(192.0f / 4.0f * 2.0f, 60.0f * 2.0f);
    sonic->SetWorldPos(Vector2(-300.0f, -50.0f));
    sonic->collider = COLLIDER::RECT;
    sonic->isFilled = false;
    sonic->color = Color(1.0f, 1.0f, 1.0f);
    sonic->pivot = OFFSET_B;

    run = new ObImage(L"run.bmp");
    run->scale = Vector2(192.0f / 4.0f * 2.0f, 60.0f * 2.0f);
    run->SetParentRT(*sonic);
    run->uv = Vector4(0.0f, 0.0f, 1.0f / 4.0f, 1.0f);
    run->pivot = OFFSET_B;

    spin = new ObImage(L"spin.bmp");
    spin->scale = Vector2(240.0f / 5.0f * 2.0f, 48.0f * 2.0f);
    spin->SetParentRT(*sonic);
    spin->uv = Vector4(0.0f, 0.0f, 1.0f / 5.0f, 1.0f);
    spin->isVisible = false;
    spin->pivot = OFFSET_B;

    int idx = 0;
    for (auto& elem : floor)
    {
        elem = new ObRect();
        elem->scale = Vector2(79.0f * 3.0f, 20.0f);
        elem->SetWorldPos(Vector2(-800.0f + idx * elem->scale.x, -240.0f));
        elem->collider = COLLIDER::RECT;
        elem->isFilled = false;
        elem->color = Color(1.0f, 0.0f, 0.0f);
        elem->pivot = OFFSET_LT;
        idx++;
    }
    idx = 0;
    for (auto& elem : floorImg)
    {
        elem = new ObImage(L"floor.bmp");
        elem->scale = Vector2(79.0f * 3.0f, 48.0f * 3.0f);
        elem->SetParentRT(*floor[idx]);
        elem->pivot = OFFSET_LT;
        idx++;
    }

    idx = 0;
    for (auto& elem : rock)
    {
        elem = new ObRect();
        elem->scale = Vector2(61.0f * 2.0f, 62.0f * 2.0f);
        elem->SetWorldPosX(800.0f * idx + 100.0f);
        elem->SetWorldPosY(RANDOM->Float(-100.0f, 0.0f));
        elem->collider = COLLIDER::RECT;
        elem->isFilled = false;
        elem->color = Color(1.0f, 0.0f, 0.0f);
        idx++;
    }
    idx = 0;
    for (auto& elem : rockImg)
    {
        elem = new ObImage(L"rock.bmp");
        elem->scale = Vector2(61.0f * 2.0f, 62.0f * 2.0f);
        elem->SetParentRT(*rock[idx]);
        idx++;
    }

    timerRun = 0.0f;
    intervalRun = 0.05f;
    frameRun = 0.0f;
    timerSpin = 0.0f;
    intervalSpin = 0.05f;
    frameSpin = 0.0f;
    timerSpin2 = 0.0f;
    intervalSpin2 = 0.5f;
    flagSpin2 = false;

    gravity = 800.0f;
    onGround = false;
    isJumping = false;
    isDoubleJumping = false;

    speed = 1.5f;

    hit = false;
    timerHit = 0.0f;
    intervalHit = 1.5f;
}

void Main::Release()
{
    SafeDelete(sonic);
    SafeDelete(run);
    SafeDelete(spin);
    for (auto& elem : floor) SafeDelete(elem);
    for (auto& elem : floorImg) SafeDelete(elem);
    for (auto& elem : rock) SafeDelete(elem);
    for (auto& elem : rockImg) SafeDelete(elem);
}

void Main::Update()
{
    ImGui::Text("Restart : R");
    if (INPUT->KeyDown('R'))
    {
        Release();
        Init();
    }

    sonic->Update();

    // 런, 스핀 애니
    if (TIMER->GetTick(timerRun, intervalRun))
    {
        timerRun = 0.0f;
        if (++frameRun >= 3.0f)
        {
            frameRun = 0.0f;
        }
        run->uv = Vector4(frameRun / 4.0f, 0.0f, 
            (frameRun + 1.0f) / 4.0f, 1.0f);
    }

    if (INPUT->KeyPress(VK_DOWN) || isJumping || isDoubleJumping)
    {
        run->isVisible = false;
        spin->isVisible = true;
        sonic->scale = spin->scale;
        
        if (TIMER->GetTick(timerSpin2, intervalSpin2))
        {
            flagSpin2 = true;
            spin->uv = Vector4(4.0f / 5.0f, 0.0f, 1.0f, 1.0f);
        }
        if (false == flagSpin2 && TIMER->GetTick(timerSpin, intervalSpin))
        {
            timerSpin = 0.0f;
            if (++frameSpin >= 4.0f)
            {
                frameSpin = 0.0f;
            }
            spin->uv = Vector4(frameSpin / 5.0f, 0.0f,
                (frameSpin + 1.0f) / 5.0f, 1.0f);
        }
    }
    else
    {
        sonic->scale = run->scale;
        run->isVisible = true;
        spin->isVisible = false;
        frameSpin = 0.0f;
        timerSpin2 = 0.0f;
        flagSpin2 = false;
    }

    // 중력, 점프
    if (onGround)
    {
        gravity = 800.0f;
        isJumping = false;
        isDoubleJumping = false;
    }
    else
    {
        gravity += 1500.0f * DELTA;
        Vector2 velocity = DOWN * gravity * DELTA;
        sonic->MoveWorldPos(velocity);
    }

    if (isJumping && false == isDoubleJumping && INPUT->KeyDown(VK_SPACE))
    {
        isDoubleJumping = true;
        gravity = -800.0f;
    }
    if (false == isJumping && INPUT->KeyDown(VK_SPACE))
    {
        sonic->SetWorldPosY(sonic->GetWorldPos().y + 20.0f);
        sonic->Update();
        gravity = -800.0f;
        onGround = false;
        isJumping = true;
    }

    run->Update();
    spin->Update();

    // 오브젝트 스폰
    ImGui::SliderFloat("speed", &speed, 1.5f, 15.0f);
    speed += 0.2f * DELTA;
    for (auto& elem : floor)
    {
        elem->MoveWorldPos(Vector2(-speed, 0.0f));
        if (elem->GetWorldPos().x + elem->scale.x < -app.GetHalfWidth())
        {
            elem->SetWorldPosX(elem->scale.x * 6.0f - 90.0f);
        }
        elem->Update();
    }

    for (auto& elem : rock)
    {
        elem->MoveWorldPos(Vector2(-speed, 0.0f));
        if (elem->GetWorldPos().x + elem->scale.x / 2 < -app.GetHalfWidth())
        {
            elem->SetWorldPosX(app.GetHalfWidth() + elem->scale.x + RANDOM->Float(100.0f, 1000.0f));
            elem->SetWorldPosY(RANDOM->Float(-100.0f, 0.0f));
        }
        elem->Update();
    }

    for (auto& elem : floorImg) elem->Update();
    for (auto& elem : rockImg) elem->Update();
}

void Main::LateUpdate()
{
    bool flag = false;
    for (auto& elem : floor)
    {
        if (sonic->Intersect(elem))
        {
            onGround = true;
            flag = true;
        }
    }
    if (false == flag)
    {
        onGround = false;
    }

    for (auto& elem : rock)
    {
        if (sonic->Intersect(elem))
        {
            hit = true;
            break;
        }
    }
    if (hit)
    {
        timerHit += 1.0f * DELTA;
        run->color = Color(RANDOM->Float(0.5f, 0.8f), 0.0f, 0.0f);
        spin->color = Color(RANDOM->Float(0.5f, 0.8f), 0.0f, 0.0f);
        if (TIMER->GetTick(timerHit, intervalHit))
        {
            run->color = Color(0.5f, 0.5f, 0.5f);
            spin->color = Color(0.5f, 0.5f, 0.5f);
            timerHit = 0.0f;
            hit = false;
        }
    }
}

void Main::Render()
{
    sonic->Render();
    run->Render();
    spin->Render();
    for (auto& elem : floorImg)elem->Render();
    for (auto& elem : floor) elem->Render();
    for (auto& elem : rockImg) elem->Render();
    for (auto& elem : rock) elem->Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"유재준 소닉");
    app.SetInstance(instance);
    app.InitWidthHeight(1600.0f, 800.0f);
    Main* main = new Main();
    int wParam = (int)WIN->Run(main);
    WIN->DeleteSingleton();     // 창이 없어지고 난 후 
    SafeDelete(main);           // 메모리 해제
    return wParam;
}