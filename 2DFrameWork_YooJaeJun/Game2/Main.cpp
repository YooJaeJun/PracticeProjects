#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
}

void Main::Release()
{
}

void Main::Update()
{
}

void Main::LateUpdate()
{
}

void Main::Render()
{
}

void Main::ResizeScreen()
{
}



int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"Game2");
	app.SetInstance(instance);
	app.InitWidthHeight(224.0f * 2.0f, 800.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}