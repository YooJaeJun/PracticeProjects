#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    circle.SetWorldPos(Vector2(0.0f, 0.0f));
    circle.scale = Vector2(700.0f, 700.0f);
    circle.isFilled = true;
    // circle.color = Color(0.5f, 0.1f, 0.8f, 1.0f);
}

void Main::Release()
{
}

void Main::Update()
{
    circle.Update();
    circle.color = Color(0.2f, 0.1f, 0.8f, 0.5f);
}

void Main::LateUpdate()
{
}

void Main::Render()
{
    circle.Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"������ Game3");
    app.SetInstance(instance);
    app.InitWidthHeight(1280.0f, 720.0f);
    Main* main = new Main();
    int wParam = (int)WIN->Run(main);
    WIN->DeleteSingleton();
    SafeDelete(main);
    return wParam;
}