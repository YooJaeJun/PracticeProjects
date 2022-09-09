#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    l1 = new ObLine;
    l1->scale.x = 200.0f;
    l1->collider = COLLIDER::LINE;
    l1->SetWorldPos(Vector2(-300.0f, -300.0f));

    l2 = new ObLine;
    l2->scale.x = 200.0f;
    l2->collider = COLLIDER::LINE;
    l2->SetWorldPos(Vector2(-400.0f, 0.0f));

    rc = new ObRect;
    rc->scale = Vector2(200.0f, 200.0f);
    rc->collider = COLLIDER::RECT;
    rc->SetWorldPos(Vector2(-100.0f, 0.0f));
    rc->rotation = 45.0f * ToRadian;

    cc = new ObCircle;
    cc->scale = Vector2(200.0f, 200.0f);
    cc->collider = COLLIDER::CIRCLE;
    cc->SetWorldPos(Vector2(200.0f, 0.0f));
}

void Main::Release()
{
    SafeDelete(l1);
    SafeDelete(l2);
    SafeDelete(rc);
    SafeDelete(cc);
}

void Main::Update()
{
    Vector2 dir = INPUT->GetWorldMousePos() - l1->GetWorldPos();
    l1->rotation = Utility::DirToRadian(dir);
    l1->scale.x = sqrt(dir.x * dir.x + dir.y * dir.y);

    l1->Update();
    l2->Update();
    rc->Update();
    cc->Update();
}

void Main::LateUpdate()
{
    if (l1->Intersect(l2))
    {
        l2->color = Color(1.0f, 0.0f, 0.0f);
    }
    else l2->color = Color(0.0f, 0.0f, 0.0f);

    if (l1->Intersect(rc))
    {
        rc->color = Color(1.0f, 0.0f, 0.0f);
    }
    else rc->color = Color(0.0f, 0.0f, 0.0f);

    if (l1->Intersect(cc))
    {
        cc->color = Color(1.0f, 0.0f, 0.0f);
    }
    else cc->color = Color(0.0f, 0.0f, 0.0f);
}

void Main::Render()
{
    l1->Render();
    l2->Render();
    rc->Render();
    cc->Render();
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