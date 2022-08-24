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
    /*rect.scale = Vector2(400.0f, 400.0f);
    rect.isFilled = true;
    rect.color = Color(0.0f, 0.0f, 0.0f, 1.0f);
    rect.isAxis = true;*/
    rc = new ObRect();
    rc->SetWorldPos(Vector2(0.0f, 0.0f));
    rc->scale = Vector2(100.0f, 100.0f);
    rc->collider = COLLIDER::RECT;

    rc2 = new ObRect();
    rc2->SetWorldPos(Vector2(-300.0f, 0.0f));
    rc2->scale = Vector2(100.0f, 100.0f);
    rc2->collider = COLLIDER::RECT;

    cc = new ObCircle();
    cc->SetWorldPos(Vector2(300.0f, 0.0f));
    cc->scale = Vector2(100.0f, 100.0f);
    cc->collider = COLLIDER::CIRCLE;
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
    // rect.Update();
    rc->Update();
    rc2->Update();
    cc->Update();
}

void Main::LateUpdate()
{
    // 사각형과 마우스 좌표
    if (rc->Intersect(INPUT->GetWorldMousePos()))
    {
        Vector2 dir = INPUT->GetWorldMousePos() - rc->GetWorldPos();
        dir.Normalize();
        rc->color = Color(dir.x, dir.y, 0.5f, 1.0f);
        // rc->MoveWorldPos(-dir * 100.0f * DELTA);

        if (INPUT->KeyPress(VK_LBUTTON))
        {
            Vector2 velocity = INPUT->GetWorldMousePos() - lastPos;
            rc->MoveWorldPos(velocity);
        }
    }
    else
    {
        rc->color = Color(0.0f, 0.0f, 0.0f, 1.0f);
    }

    /*Vector2 mousePos = INPUT->GetWorldMousePos();
    float rad = Utility::DirToRadian(mousePos);
    float degree = rad * 180.0f / PI;
    float degreePlus = degree < 0.0f ? degree + 360.0f : degree;
    float r = 0.0f, g = 0.0f, b = 0.0f;
    
    if (rect.Intersect(mousePos))
    {
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
    ImGui::InputInt3("RGB(0~255)", colors255);*/


    // 원과 마우스 좌표
    if (cc->Intersect(INPUT->GetWorldMousePos()))
    {
        Vector2 dir = INPUT->GetWorldMousePos() - cc->GetWorldPos();
        dir.Normalize();
        cc->color = Color(dir.x, dir.y, 0.5f, 1.0f);

        if (INPUT->KeyPress(VK_LBUTTON))
        {
            Vector2 velocity = INPUT->GetWorldMousePos() - lastPos;
            cc->MoveWorldPos(velocity);
        }
    }
    else
    {
        cc->color = Color(0.0f, 0.0f, 0.0f, 1.0f);
    }


    // 사각형과 사각형 충돌
    if (rc->Intersect(rc2))
    {
        Vector2 dir = rc->GetWorldPos() - rc2->GetWorldPos();
        dir.Normalize();
        rc2->MoveWorldPos(-dir);
    }

    // 사각형과 원 충돌
    if (rc->Intersect(cc))
    {
        Vector2 dir = rc->GetWorldPos() - cc->GetWorldPos();
        dir.Normalize();
        cc->MoveWorldPos(-dir);
    }




    lastPos = INPUT->GetWorldMousePos();
}

void Main::Render()
{
    // pl.Render();
    // circle.Render();
    // for (auto& star : stars) star.Render();
    // rect.Render();
    rc->Render();
    rc2->Render();
    cc->Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"유재준 Color");
    app.SetInstance(instance);
    app.InitWidthHeight(1280.0f, 720.0f);
    Main* main = new Main();
    int wParam = (int)WIN->Run(main);
    WIN->DeleteSingleton();
    SafeDelete(main);
    return wParam;
}