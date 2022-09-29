#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	{
		Scene01* temp = new Scene01();
		SCENE->AddScene("Scene01", temp);
	}

	SCENE->ChangeScene("Scene01");
}

void Main::Release()
{
	SCENE->Release();
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
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"Game1");
	app.SetInstance(instance);
	app.InitWidthHeight(1400.0f, 800.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}