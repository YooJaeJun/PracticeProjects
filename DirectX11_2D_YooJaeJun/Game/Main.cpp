#include "stdafx.h"
#include "Main.h"
using namespace std;

void Main::Init()
{
    bg = new UI;
    bg->img = new ObImage(L"EnterTheGungeon/Background.png");
    bg->img->scale.x = 700.0f * 2.0f;
    bg->img->scale.y = 370.0f * 2.0f;

    player = new Player;

    for (auto& elem : enemy)
    {
        elem = new Enemy;

        elem->col->scale.x = 24.0f / 2.0f * 2.0f;
        elem->col->scale.y = 24.0f * 2.0f;
        elem->col->SetWorldPosX(200.0f);
        elem->col->SetWorldPosY(200.0f);

        elem->idle = new ObImage(L"EnterTheGungeon/Enemy_0_Idle.png");
        elem->idle->scale.x = 24.0f;
        elem->idle->scale.y = 24.0f;
        elem->idle->maxFrame.x = 2;
        elem->idle->scale.x = 24.0f / 2.0f * 2.0f;
        elem->idle->scale.y = 24.0f * 2.0f;
        elem->idle->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
        elem->idle->SetParentRT(*elem->col);
    }
}

void Main::Release()
{
    SafeDelete(bg);
    SafeDelete(player);
    for(auto& elem : enemy) SafeDelete(elem);
}

void Main::Update()
{
    if (INPUT->KeyDown('R'))
    {
        Release();
        Init();
    }
    bg->Update();
    player->Update();
    for (auto& elem : enemy)
    {
        if (player->col)
        {
            Vector2 dir = player->col->GetWorldPos() - elem->col->GetWorldPos();
            dir.Normalize();
            elem->Move(dir);
        }
        elem->Update();
    }
}

void Main::LateUpdate()
{
    player->LateUpdate();
    for(auto& elem : enemy) elem->LateUpdate();

    for (auto& bulletElem : player->bullet)
    {
        for (auto& enemyElem : enemy)
        {
            if (bulletElem->col->Intersect(enemyElem->col))
            {
                enemyElem->col->colOnOff = false;
                enemyElem->idle->isVisible = false;
                bulletElem->col->colOnOff = false;
                bulletElem->img->isVisible = false;
            }
        }
    }
}

void Main::Render()
{
    bg->Render();
    player->Render();
    for (auto& elem : enemy) elem->Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"Enter the Gungeon by 유재준");
    app.SetInstance(instance);
    app.InitWidthHeight(1400.0f, 740.0f);
    Main* main = new Main();
    int wParam = (int)WIN->Run(main);
    WIN->DeleteSingleton();     // 창이 없어지고 난 후 
    SafeDelete(main);           // 메모리 해제
    return wParam;
}