#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    circle.SetWorldPos(Vector2(0.0f, 0.0f));
    circle.scale = Vector2(700.0f, 700.0f);
    circle.isFilled = true;

    pl.SetWorldPos(Vector2(0.0f, 0.0f));
    pl.scale = Vector2(700.0f, 700.0f);
    pl.isFilled = true;
    pl.color = Color(0.5f, 0.0f, 0.0f, 1.0f);

    stars[0].SetWorldPos(Vector2(0.0f, 0.0f));
    stars[0].scale = Vector2(500.0f, 500.0f);
    stars[0].rotation = -20.0f * ToRadian;
    stars[0].isFilled = true;

    stars[1].SetWorldPos(Vector2(-400.0f, 0.0f));
    stars[1].scale = Vector2(300.0f, 300.0f);
    stars[1].rotation = 70.0f * ToRadian;
    stars[1].color = Color(0.6f, 0.4f, 0.0f, 1.0f);
    stars[1].isFilled = false;

    stars[2].SetWorldPos(Vector2(400.0f, 0.0f));
    stars[2].scale = Vector2(300.0f, 300.0f);
    stars[2].rotation = 30.0f * ToRadian;
    stars[2].color = Color(0.0f, 0.6f, 0.4f, 1.0f);
    stars[2].isFilled = false;

    stars[3].SetWorldPos(Vector2(-400.0f, 0.0f));
    stars[3].scale = Vector2(100.0f, 100.0f);
    stars[3].rotation = 30.0f * ToRadian;
    stars[3].color = Color(0.6f, 0.4f, 0.0f, 1.0f);
    stars[3].isFilled = true;

    stars[4].SetWorldPos(Vector2(400.0f, 0.0f));
    stars[4].scale = Vector2(100.0f, 100.0f);
    stars[4].rotation = 80.0f * ToRadian;
    stars[4].color = Color(0.0f, 0.6f, 0.4f, 1.0f);
    stars[4].isFilled = true;
}

void Main::Release()
{
}

void Main::Update()
{
    pl.Update();
    circle.Update();
    for(auto& star : stars) star.Update();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
    pl.Render();
    // circle.Render();
    // for (auto& star : stars) star.Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"À¯ÀçÁØ Color");
    app.SetInstance(instance);
    app.InitWidthHeight(1280.0f, 720.0f);
    Main* main = new Main();
    int wParam = (int)WIN->Run(main);
    WIN->DeleteSingleton();
    SafeDelete(main);
    return wParam;
}