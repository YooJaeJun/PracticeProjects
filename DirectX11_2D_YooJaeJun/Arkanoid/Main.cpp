#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    int idx = 0;
    for (auto& brick : bricks)
    {
        brick = new ObRect();
        brick->SetWorldPos(Vector2(-300.0f + idx * 20.0f, 600.0f - idx / 10 * 60.0f));
        brick->scale = Vector2(60.0f, 30.0f);
        brick->collider = COLLIDER::RECT;
        idx++;
    }

    ball = new ObCircle();
    ball->SetWorldPos(Vector2(200.0f, -200.0f));
    ball->scale = Vector2(100.0f, 100.0f);
    ball->rotation = 90.0f * ToRadian;
    ball->collider = COLLIDER::CIRCLE;

    ballFireDir = ball->GetUp();
}

void Main::Release()
{
}

void Main::Update()
{
    Vector2 velocity = ballFireDir * 400.0f * DELTA;
    ball->MoveWorldPos(velocity);

    ball->Update();
    for (auto& brick : bricks) brick->Update();
}

void Main::LateUpdate()
{
    Vector2 mousePos = INPUT->GetWorldMousePos();
    float rad = Utility::DirToRadian(mousePos);
    float degree = rad * 180.0f / PI;
    float degreePlus = degree < 0.0f ? degree + 360.0f : degree;
    ImGui::SliderFloat("Mouse X", &mousePos.x, -app.GetWidth(), app.GetWidth());
    ImGui::SliderFloat("Mouse Y", &mousePos.y, -app.GetHeight(), app.GetHeight());
    ImGui::SliderFloat("rad", &rad, -PI, PI);
    ImGui::SliderFloat("degree(-180~180)", &degree, -180.0f, 180.0f);
    ImGui::SliderFloat("degree(0~360)", &degreePlus, 0.0f, 360.0f);
    

    // 먼저 위치 갱신
    ball->Update(); 

    // 원과 사각형
    for (auto& brick : bricks)
    {
        if (ball->Intersect(brick))
        {
            ballFireDir *= -1.0f;
        }
    }

    mouseLastPos = INPUT->GetWorldMousePos();
}

void Main::Render()
{
    // pl.Render();
    // circle.Render();
    // for (auto& star : stars) star.Render();
    // rect.Render();
    for (auto& brick : bricks) brick->Render();
    ball->Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"유재준 Alkaloid");
    app.SetInstance(instance);
    app.InitWidthHeight(600.0f, 1200.0f);
    Main* main = new Main();
    int wParam = (int)WIN->Run(main);
    WIN->DeleteSingleton();
    SafeDelete(main);
    return wParam;
}