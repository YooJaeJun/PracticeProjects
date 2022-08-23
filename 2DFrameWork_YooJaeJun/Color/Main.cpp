#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    /*
    circle.SetWorldPos(Vector2(0.0f, 0.0f));
    circle.scale = Vector2(700.0f, 700.0f);
    circle.isFilled = true;

    pl.SetWorldPos(Vector2(0.0f, 0.0f));
    pl.scale = Vector2(700.0f, 700.0f);
    pl.isFilled = true;
    pl.color = Color(0.5f, 0.0f, 0.0f, 1.0f);
    */
    /*
    for (auto& star : stars)
    {
        star.SetWorldPos(Vector2(RANDOM->Float(-2000.0f, 2000.0f), RANDOM->Float(-2000.0f, 2000.0f)));
        star.scale = Vector2(RANDOM->Float(50.0f, 50.0f), RANDOM->Float(200.0f, 200.0f));
        star.rotation = RANDOM->Float(0.0f, 360.0f) * ToRadian;
        star.isFilled = true;
    }
    */
    rect.scale = Vector2(255.0f, 255.0f);
    rect.isFilled = true;
    rect.color = Color(0.0f, 0.0f, 0.0f, 1.0f);
}

void Main::Release()
{
}

void Main::Update()
{
    // ImGui::ColorEdit3("Color", (float*)&pl.color, ImGuiColorEditFlags_PickerHueWheel);
    // pl.Update();
    // circle.Update();
    // for(auto& star : stars) star.Update();
    rect.Update();

    Vector2 mousePos = INPUT->GetWorldMousePos();
    ImGui::SliderFloat("Mouse X", &mousePos.x, -app.GetWidth(), app.GetWidth());
    ImGui::SliderFloat("Mouse Y", &mousePos.y, -app.GetHeight(), app.GetHeight());
}

void Main::LateUpdate()
{
    if (rect.Intersect(INPUT->GetWorldMousePos()))
    {
        // rect.color = Color(INPUT->GetWorldMousePos().x, INPUT->GetWorldMousePos().y, INPUT->GetWorldMousePos().y, 1.0f);
    }
    else
    {
        rect.color = Color(0.0f, 0.0f, 0.0f, 1.0f);
    }
}

void Main::Render()
{
    // pl.Render();
    // circle.Render();
    // for (auto& star : stars) star.Render();
    rect.Render();
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