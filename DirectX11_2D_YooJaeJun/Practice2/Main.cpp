#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    bg = new ObImage(L"zzangu_3.jpg");
    bg->scale = Vector2(100.0f, 100.0f);
    bg->uv = Vector4(213.0f / 401.0f, 115.0f / 400.0f, 312.0f / 401.0f, 183.0f / 400.0f);

    player = new ObRect;
    player->scale = Vector2(200.0f, 100.0f);
    player->collider = COLLIDER::RECT;
    player->isFilled = false;
    player->color = Color(0.0f, 0.0f, 0.0f);

    boss   = new ObRect;
    boss->scale = Vector2(200.0f, 200.0f);
    boss->collider = COLLIDER::RECT;
    boss->isFilled = false;
    boss->color = Color(0.0f, 0.0f, 0.0f);

    effect = new ObCircle;
    effect->scale = Vector2(30.0f, 30.0f);
    effect->collider = COLLIDER::CIRCLE;
    effect->isFilled = false;
    effect->color = Color(0.0f, 0.0f, 0.0f);
}

void Main::Release()
{
    SafeDelete(player);
    SafeDelete(boss);
    SafeDelete(effect);
}

void Main::Update()
{
    ImGui::SliderFloat2("Scale", (float*)&bg->scale, 0.0f, 800.0f);
    ImGui::SliderFloat4("UV", (float*)&bg->uv, 0.0f, 1.0f);
    bg->Update();

    player->SetWorldPos(INPUT->GetWorldMousePos());
    player->Update();


    boss->Update();
    
    if (boss->Intersect(player))
    {
        float radius = boss->scale.x / 2;
        float minX = boss->GetWorldPos().x - radius;
        float maxX = boss->GetWorldPos().x + radius;
        effect->SetWorldPosX(Utility::Saturate(player->GetWorldPos().x, minX, maxX));
        float minY = boss->GetWorldPos().y - radius;
        float maxY = boss->GetWorldPos().y + radius;
        effect->SetWorldPosY(Utility::Saturate(player->GetWorldPos().y, minY, maxY));
    }

    effect->Update();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
    bg->Render();
    player->Render();
    boss->Render();
    effect->Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"유재준 이펙트 위치");
    app.SetInstance(instance);
    app.InitWidthHeight(1280.0f, 720.0f);
    Main* main = new Main();
    int wParam = (int)WIN->Run(main);
    WIN->DeleteSingleton();     // 창이 없어지고 난 후 
    SafeDelete(main);           // 메모리 해제
    return wParam;
}