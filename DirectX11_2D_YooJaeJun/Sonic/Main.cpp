#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    sonic = new Sonic();
    sonic->Init();

    int idx = 0;
    for (auto& elem : floor)
    {
        elem = new Floor();
        elem->Init();
        elem->col->SetWorldPosX(-app.GetHalfWidth() + idx * elem->img->scale.x);
        elem->col->SetWorldPosY(-app.GetHalfHeight() + elem->img->scale.y);
        idx++;
    }

    idx = 0;
    for (auto& elem : rock)
    {
        elem = new Obstacle();
        elem->Init();
        elem->col->SetWorldPosX(app.GetHalfWidth() * (idx + 1) + 100.0f);
        elem->col->SetWorldPosY(RANDOM->Float(-200.0f, 0.0f));
        idx++;
    }
}

void Main::Release()
{
    SafeDelete(sonic);
    for(auto& elem : floor) SafeDelete(elem);
    for(auto& elem : rock) SafeDelete(elem);
}

void Main::Update()
{
    ImGui::SliderFloat("DeltaScale", &app.deltaScale, 0.01f, 100.0f);
    app.deltaScale += 0.1f * TIMER->GetDelta();
    app.deltaScale = Utility::Saturate(app.deltaScale, 1.0f, 10.0f);

    ImGui::Text("Restart : R");
    ImGui::SliderFloat("speed", &floor[0]->speed, 1.5f, 15.0f);
    if (INPUT->KeyDown('R') || 
        sonic->col->GetWorldPos().y < -app.GetHalfHeight() - sonic->col->scale.y)
    {
        Release();
        Init();
    }

    sonic->Update();


    for(auto& elem : floor)
    {
        if (sonic->col->GetWorldPos().x - elem->col->GetWorldPos().x > 800.0f)
        {
            elem->col->MoveWorldPos(Vector2(79.0f * 2.5f * floorMax, 0.0f));
        }
    }

    // 오브젝트 스폰
    for (auto& elem : floor)
    {
        elem->Update();
    }

    for (auto& elem : rock)
    {
        elem->Update();
    }
}

void Main::LateUpdate()
{
    sonic->onGround = false;

    for (auto& elem : floor)
    {
        if (elem->col->Intersect(sonic->col->GetWorldPos()))
        {
            sonic->onGround = true;
            break;
        }
    }
    // 순서 때문에 바로 뒤에 배치
    sonic->Fall();

    for (auto& elem : rock)
    {
        if (elem->col->Intersect(sonic->col))
        {
            sonic->Hit();
            break;
        }
    }
}

void Main::Render()
{
    sonic->Render();
    for (auto& elem : floor) elem->Render();
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