#include "stdafx.h"
#include "Main.h"
using namespace std;

void Main::Init()
{
    {
        Scene01* tempScene = new Scene01;
        SCENE->AddScene("Scene01", tempScene);
    }

    SCENE->ChangeScene("Scene01");
}

void Main::Release()
{
}

void Main::Update()
{
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
    app.SetAppName(L"Enter the Gungeon by ������");
    app.SetInstance(instance);
    app.InitWidthHeight(1400.0f, 740.0f);
    Main* main = new Main();
    int wParam = (int)WIN->Run(main);
    WIN->DeleteSingleton();     // â�� �������� �� �� 
    SafeDelete(main);           // �޸� ����
    return wParam;
}