#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	score = 0;
	lastScore = 0;
	gameState = GameState::PROGRESS;
	CAM->position = Vector2(0.0f, 0.0f);

	bg1 = new Background;

	player = new Airplane();
}

void Main::Release()
{
	bg1->Release();
	player->Release();
}

void Main::Update()
{
	if (INPUT->KeyDown('R'))
	{
		Release();
		Init();
	}

	if (gameState == GameState::END)
	{
		player->Die();
		return;
	}

	if (INPUT->KeyPress(VK_SPACE))
	{
		bg1->idle->uv.y -= DELTA / bg1->idleImgSize.y * 200.0f;
		bg1->idle->uv.w -= DELTA / bg1->idleImgSize.y * 200.0f;
	}
	else
	{
		bg1->idle->uv.y -= DELTA / bg1->idleImgSize.y * 50.0f;
		bg1->idle->uv.w -= DELTA / bg1->idleImgSize.y * 50.0f;
	}
	bg1->Update();

	player->Update();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
	bg1->Render();
	player->Render();
}

void Main::ResizeScreen()
{
	bg1->Spawn();
	player->Spawn();
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