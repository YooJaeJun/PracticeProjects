#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	player = new Player;

	isChangingSceneBefore = false;

	{	// 익명 스코프
		Stage01* temp = new Stage01();
		temp->player = player;
		SCENE->AddScene("Stage01", temp);
	}

	{
		Stage02* temp = new Stage02();
		temp->player = player;
		SCENE->AddScene("Stage02", temp);
	}

	SCENE->ChangeScene("Stage01");
}

void Main::Release()
{
	SCENE->Release();
	player->Release();
}

void Main::Update()
{
	if (INPUT->KeyDown('1'))
	{
		isChangingSceneBefore = true;
		SCENE->ChangeScene("Stage01", 2.0f);
	}
	else if (INPUT->KeyDown('2'))
	{
		isChangingSceneBefore = true;
		SCENE->ChangeScene("Stage02", 2.0f);
	}

	if (isChangingSceneBefore)
	{
		LIGHT->light.radius -= 1000.0f * DELTA;

		if (TIMER->GetTick(timeLighter, 2.0f))
		{
			isChangingSceneBefore = false;
		}
	}
	else
	{
		LIGHT->light.radius += 1000.0f * DELTA;
		LIGHT->light.radius = Utility::Saturate(LIGHT->light.radius, 0.0f, 2000.0f);
	}

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
	app.SetAppName(L"슈팅 게임 _유재준");
	app.SetInstance(instance);
	app.InitWidthHeight(448.0f, 800.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}