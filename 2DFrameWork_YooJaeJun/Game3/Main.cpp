#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    circle.SetWorldPos(Vector2(200.0f, 0.0f));
    circle.scale = Vector2(200.0f, 200.0f);
    circle.isFilled = true;

    cc.SetWorldPos(Vector2(-200.0f, 0.0f));
    cc.scale = Vector2(200.0f, 200.0f);
    cc.isFilled = true;
}

void Main::Release()
{
}

void Main::Update()
{
    circle.Update();
    cc.Update();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
    circle.Render();
    cc.Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"À¯ÀçÁØ Game3");
    app.SetInstance(instance);
    app.InitWidthHeight(1280.0f, 720.0f);
    Main* main = new Main();
    int wParam = (int)WIN->Run(main);
    WIN->DeleteSingleton();
    SafeDelete(main);
    return wParam;
}