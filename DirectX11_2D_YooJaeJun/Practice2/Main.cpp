#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    hitbox = new ObRect;
    hitbox->scale = Vector2(200.0f, 100.0f);
    hitbox->collider = COLLIDER::RECT;
    hitbox->isFilled = false;
    hitbox->color = Color(0.0f, 0.0f, 0.0f);

    hitboxImg = new ObImage(L"RazerBeam.PNG");
    hitboxImg->scale = Vector2(200.0f, 100.0f);
    hitboxImg->uv = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

    boss = new ObRect;
    boss->scale = Vector2(200.0f, 200.0f);
    boss->collider = COLLIDER::RECT;
    boss->isFilled = false;
    boss->color = Color(0.0f, 0.0f, 0.0f);

    bossImg = new ObImage(L"mole.jpg");
    bossImg->scale = Vector2(200.0f, 200.0f);
    bossImg->uv = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

    effect = new ObCircle;
    effect->scale = Vector2(30.0f, 30.0f);
    effect->collider = COLLIDER::CIRCLE;
    effect->color = Color(0.9f, 0.2f, 0.1f);
}

void Main::Release()
{
    SafeDelete(hitbox);
    SafeDelete(boss);
    SafeDelete(effect);
}

void Main::Update()
{
    ImGui::SliderFloat2("Scale", (float*)&boss->scale, 0.0f, 800.0f);
    bossImg->scale = boss->scale;
    ImGui::SliderFloat4("UV", (float*)&bossImg->uv, 0.0f, 1.0f);

    hitbox->SetWorldPos(INPUT->GetWorldMousePos());
    hitbox->Update();
    hitboxImg->SetWorldPos(hitbox->GetWorldPos());

    boss->Update();
    
    if (boss->Intersect(hitbox))
    {
        float radius = boss->scale.x / 2;
        float minX = boss->GetWorldPos().x - radius;
        float maxX = boss->GetWorldPos().x + radius;
        effect->SetWorldPosX(Utility::Saturate(hitbox->GetWorldPos().x, minX, maxX));
        radius = boss->scale.y / 2;
        float minY = boss->GetWorldPos().y - radius;
        float maxY = boss->GetWorldPos().y + radius;
        effect->SetWorldPosY(Utility::Saturate(hitbox->GetWorldPos().y, minY, maxY));
    }
    effect->Update();

    hitboxImg->Update();
    bossImg->Update();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
    hitbox->Render();
    boss->Render();
    bossImg->Render();
    hitboxImg->Render();
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