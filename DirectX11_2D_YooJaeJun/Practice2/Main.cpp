#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
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
    player->SetWorldPos(INPUT->GetWorldMousePos());
    player->Update();


    boss->Update();


    
    if (boss->Intersect(player))
    {
        effect->SetWorldPos(Vector2(player->GetWorldPos().x,
            player->GetWorldPos().y));

        effect->Update();

        float radius = boss->scale.x / 2;
        effect->SetWorldPosX(Utility::Saturate(
            effect->GetWorldPos().x,
            boss->GetWorldPos().x - radius,
            boss->GetWorldPos().x + radius));
        effect->SetWorldPosY(Utility::Saturate(
            effect->GetWorldPos().y,
            boss->GetWorldPos().y - radius,
            boss->GetWorldPos().y + radius));
    }

    effect->Update();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
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