#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	pl.SetWorldPos(Vector2(0.0f, 0.0f));
	pl.scale = Vector2(700.0f, 700.0f);
	//pl.color = Color(0.5f, 0.0f, 0.0f, 1.0f);
	pl.rotation = 0.0f;
	pl.isFilled = true;
	pl.isAxis = false;
	pl.pivot = OFFSET_N;
}

void Main::Release()
{
}

void Main::Update()
{
	pl.Update();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
	pl.Render();
}

void Main::ResizeScreen()
{
}



int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"Game2");
	app.SetInstance(instance);
	app.InitWidthHeight(1200, 800.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}