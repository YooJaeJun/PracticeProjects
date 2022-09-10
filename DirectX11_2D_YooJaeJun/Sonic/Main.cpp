#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	app.deltaScale = 1.0f;
	CAM->position = Vector2(0.0f, 0.0f);

	sonic = new Sonic();

	int idx = 0;
	for (auto& elem : floor)
	{
		elem = new Floor;
		elem->col->SetWorldPosX(-app.GetHalfWidth() + idx * 79.0f * 2.5f);
		idx++;
	}

	for (auto& elem : rock)
	{
		elem = new Obstacle;
	}
}

void Main::Release()
{
	sonic->Release();
	for (auto& elem : floor) elem->Release();
	for (auto& elem : rock) elem->Release();
}

void Main::Update()
{
	if (INPUT->KeyDown('R'))
	{
		Release();
		Init();
	}
	ImGui::SliderFloat("DeltaScale", &app.deltaScale, 0.01f, 100.0f);
	app.deltaScale += 0.1f * TIMER->GetDelta();
	app.deltaScale = Utility::Saturate(app.deltaScale, 1.0f, 10.0f);

	for (auto& elem : floor)
	{
		elem->Spawn(sonic->col->GetWorldPos().x, floorMax);
		elem->Update();
	}

	for (auto& elem : rock)
	{
		elem->Spawn(sonic->col->GetWorldPos().x, rockMax);
		elem->Update();
	}

	sonic->Update();
}

void Main::LateUpdate()
{
	for (auto& elem : floor)
	{
		if (!elem->col->colOnOff) continue;

		if (elem->col->Intersect(sonic->col->GetWorldPos()))
		{
			sonic->LandOn();
		}
	}

	for (auto& elem : rock)
	{
		if (!elem->col->colOnOff) continue;

		if (elem->col->Intersect(sonic->col))
		{
			sonic->Hit();
		}
	}
}

void Main::Render()
{
	sonic->Render();
	for (auto& elem : floor)
	{
		if (!elem->col->colOnOff) continue;
		elem->Render();
	}
	for (auto& elem : rock)
	{
		if (!elem->col->colOnOff) continue;
		elem->Render();
	}
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"런 게임 _유재준");
	app.SetInstance(instance);
	app.InitWidthHeight(1600.0f, 800.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}