#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    ball = new ObCircle();
    ball->SetWorldPos(Vector2(0.0f, -270.0f));
    ball->scale = Vector2(40.0f, 40.0f);
    ball->rotation = 90.0f * ToRadian;
    ball->collider = COLLIDER::CIRCLE;
    ballFireDir = ball->GetUp();
    ballScalar = 600.0f;

    bar = new ObRect();
    bar->SetWorldPos(Vector2(0.0f, -300.0f));
    bar->scale = Vector2(100.0f, 10.0f);
    bar->collider = COLLIDER::RECT;
    barScalar = 500.0f;
    barDir = Vector2(0.0f, 0.0f);

    int idx = 0;
    for (auto& brick : bricks)
    {
        brick = new ObRect();
        brick->scale = Vector2(60.0f, 30.0f);
        brick->collider = COLLIDER::RECT;
        brickHitTime[idx] = 0.0f;
        brickState[idx] = estate::idle;

        if (idx >= 0 and idx < 8)
        {
            brick->SetWorldPos(Vector2(-250.0f + idx * 60.0f, 300.0f - int(idx / 8.0f) * 30.0f));
            brick->color = Color(0.9f, 0.7f, 0.0f, 1.0f);
            brickLife[idx] = 2;
        }
        else if (idx >= 8 and idx < 16)
        {
            brick->SetWorldPos(Vector2(-250.0f + (idx - 8) * 60.0f, 270.0f - int(idx / 8.0f) * 30.0f));
            brick->color = Color(0.9f, 0.4f, 0.3f, 1.0f);
            brickLife[idx] = 1;
        }

        idx++;
    }

    for (auto& wall : walls)
    {
        wall = new ObRect();
        bar->collider = COLLIDER::RECT;
    }
    walls[0]->SetWorldPos(Vector2(0.0f, -480.0f));
    walls[1]->SetWorldPos(Vector2(0.0f, 480.0f));
    walls[2]->SetWorldPos(Vector2(300.0f, 0.0f));
    walls[3]->SetWorldPos(Vector2(-300.0f, 0.0f));

    walls[0]->scale = Vector2(600.0f, 10.0f);
    walls[1]->scale = Vector2(600.0f, 10.0f);
    walls[2]->scale = Vector2(10.0f, 960.0f);
    walls[3]->scale = Vector2(10.0f, 960.0f);

    walls[0]->color = Color(0.0f, 0.0f, 0.0f, 1.0f);
    walls[1]->color = Color(0.0f, 0.0f, 0.0f, 1.0f);
    walls[2]->color = Color(0.0f, 0.0f, 0.0f, 1.0f);
    walls[3]->color = Color(0.0f, 0.0f, 0.0f, 1.0f);
}

void Main::Release()
{
}

void Main::Update()
{
    if (INPUT->KeyDown('R'))
    {
        Init();
    }

    Vector2 velocity = ballFireDir * ballScalar * DELTA;
    ball->MoveWorldPos(velocity);

    if (INPUT->KeyPress(VK_LEFT))
    {
        barDir = -bar->GetRight();
        Vector2 velocity = barDir * barScalar * DELTA;
        bar->MoveWorldPos(velocity);
    }
    else if (INPUT->KeyPress(VK_RIGHT))
    {
        barDir = bar->GetRight();
        Vector2 velocity = barDir * barScalar * DELTA;
        bar->MoveWorldPos(velocity);
    }

    ball->Update();
    bar->Update();
    for (auto& wall : walls) wall->Update();

    int idx = 0;
    for (auto& brick : bricks)
    {
        if (brickState[idx] == estate::hit)
        {
            brick->color = Color(RANDOM->Float(0.6f, 1.0f), 0.0f, 0.0f);
            brickHitTime[idx] += 100.0f * DELTA;
            if (brickHitTime[idx] > 30.0f)
            {
                brick->color = brick->color = Color(0.9f, 0.4f, 0.3f, 1.0f);
                brickHitTime[idx] = 0.0f;
                brickState[idx] = estate::idle;
            }
        }
        brick->Update();
        idx++;
    }
}

void Main::LateUpdate()
{
    Vector2 mousePos = INPUT->GetWorldMousePos();

    // 먼저 위치 갱신
    // ball->Update(); 


    auto bounce = [&](GameObject* ob, bool isIntersectBar = 0)
    {
        ob->Update();
        Vector2 direction = ball->GetWorldPos() - ballLastPos;
        direction.Normalize();

        // 좌우
        if (ballLastPos.x <= ob->GetWorldPos().x - ob->scale.x / 2 - ball->scale.x / 2 or
            ballLastPos.x >= ob->GetWorldPos().x + ob->scale.x / 2 + ball->scale.x / 2)
        {
            ballFireDir.x = -direction.x;
        }
        // 상하
        else if (ballLastPos.y <= ob->GetWorldPos().y - ob->scale.y / 2 - ball->scale.y / 2 or
                 ballLastPos.y >= ob->GetWorldPos().y + ob->scale.y / 2 + ball->scale.y / 2)
        {
            ballFireDir.y = -direction.y;
        }
        // 모서리
        // else
        // {
        //     ballFireDir = -direction;
        // }

        if (isIntersectBar)
        {
            ballFireDir.x = barDir.x;
        }
    };


    if (ball->Intersect(bar))
    {
        bounce(bar, true);
    }

    int idx = 0;
    for (auto& brick : bricks)
    {
        if (ball->Intersect(brick))
        {
            bounce(brick);
            brickLife[idx]--;
            brickState[idx] = estate::hit;
        }
        if (brickLife[idx] <= 0)
        {
            brick->SetWorldPos(Vector2(2000.0f, 2000.0f));
        }
        idx++;
    }

    for (auto& wall : walls)
    {
        if (ball->Intersect(wall))
        {
            bounce(wall);
        }
    }

    ballLastPos = ball->GetWorldPos();

    ImGui::SliderFloat("Ball Last Pos X", &ballLastPos.x, -app.GetHalfWidth(), app.GetHalfWidth());
    ImGui::SliderFloat("Ball Last Pos Y", &ballLastPos.y, -app.GetHalfHeight(), app.GetHalfHeight());
    ImGui::SliderFloat("Ball Dir X", &ballFireDir.x, -1.0f, 1.0f);
    ImGui::SliderFloat("Ball Dir Y", &ballFireDir.y, -1.0f, 1.0f);
}

void Main::Render()
{
    // pl.Render();
    // circle.Render();
    // for (auto& star : stars) star.Render();
    // rect.Render();
    ball->Render();
    bar->Render();
    for (auto& brick : bricks) brick->Render();
    for (auto& wall : walls) wall->Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"유재준 Alkaloid");
    app.SetInstance(instance);
    app.InitWidthHeight(600.0f, 960.0f);
    Main* main = new Main();
    int wParam = (int)WIN->Run(main);
    WIN->DeleteSingleton();
    SafeDelete(main);
    return wParam;
}