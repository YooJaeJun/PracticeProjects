#include "stdafx.h"
#include "Main.h"
using namespace Gungeon;

void Main::Init()
{
    LIGHT->light.radius = 2000.0f;
    LIGHT->light.select = 0.0f;

    mapGen = new ProcedureMapGeneration;

    {
        Scene01* tempScene = new Scene01();
        tempScene->mapGen = mapGen;
        SCENE->AddScene("Scene01", tempScene);
    }
    {
        Scene02* tempScene = new Scene02();
        tempScene->mapGen = mapGen;
        tempScene->player = player;
        SCENE->AddScene("Scene02", tempScene);
    }
    {
        Scene03* tempScene = new Scene03();
        tempScene->player = player;
        SCENE->AddScene("Scene03", tempScene);
    }

    SCENE->ChangeScene("Scene01");
}

void Main::Release()
{
    SafeRelease(mapGen);
    SafeRelease(player);
    SCENE->Release();
}

void Main::Update()
{
    ImGui::Text("FPS : %d", TIMER->GetFramePerSecond());

    SCENE->Update();
}

void Main::LateUpdate()
{
    SCENE->LateUpdate();
}

void Main::Render()
{
    SCENE->Render();
}

void Main::ResizeScreen()
{
    SCENE->ResizeScreen();
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"Enter the Gungeon by 유재준");
    app.SetInstance(instance);
    app.InitWidthHeight(1400.0f, 740.0f);
    app.background = Color(0.0f, 0.0f, 0.0f, 1.0f);
    Main* main = new Main();
    int wParam = (int)WIN->Run(main);
    WIN->DeleteSingleton();     // 창이 없어지고 난 후 
    SafeDelete(main);           // 메모리 해제
    return wParam;
}
