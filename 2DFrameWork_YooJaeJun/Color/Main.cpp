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
    rect.scale = Vector2(400.0f, 400.0f);
    rect.isFilled = true;
    rect.color = Color(0.0f, 0.0f, 0.0f, 1.0f);
    rect.isAxis = true;
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

}

void Main::LateUpdate()
{
    Vector2 mousePos = INPUT->GetWorldMousePos();
    float rad = Utility::DirToRadian(mousePos);
    float degree = rad * 180.0f / PI;
    float degreePlus = degree < 0.0f ? degree + 360.0f : degree;
    float r = 0.0f, g = 0.0f, b = 0.0f;
    
    if (rect.Intersect(mousePos))
    {
        /*
        if (degreePlus >= 0.0f and degreePlus < 120.0f)
        {
            float color = degreePlus / 120.0f;
            r = 1.0f - color;
            g = color;
        }
        else if (degreePlus >= 120.0f and degreePlus < 240.0f)
        {
            float color = (degreePlus - 120.0f) / 120.0f;
            g = 1.0f - color;
            b = color;
        }
        else
        {
            float color = (degreePlus - 240.0f) / 120.0f;
            b = 1.0f - color;
            r = color;
        }
        */
        r = mousePos.x * 1.0f / (rect.scale.x / 2);
        g = mousePos.y * 1.0f / (rect.scale.y / 2);
        r = max(0.0f, r);
        g = max(0.0f, g);
        b = 0.5f;
    }
    rect.color = Color(r, g, b, 1.0f);


    ImGui::SliderFloat("Mouse X", &mousePos.x, -app.GetWidth(), app.GetWidth());
    ImGui::SliderFloat("Mouse Y", &mousePos.y, -app.GetHeight(), app.GetHeight());
    ImGui::SliderFloat("rad", &rad, -PI, PI);
    ImGui::SliderFloat("degree(-180~180)", &degree, -180.0f, 180.0f);
    ImGui::SliderFloat("degree(0~360)", &degreePlus, 0.0f, 360.0f);
    float colors[3] = { r, g, b };
    ImGui::InputFloat3("RGB(0~1)", colors);
    int colors255[3] = { r * 255, g * 255, b * 255 };
    ImGui::InputInt3("RGB(0~255)", colors255);
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