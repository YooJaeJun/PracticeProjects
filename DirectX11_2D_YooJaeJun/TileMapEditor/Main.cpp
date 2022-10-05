#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	map = new ObTileMap();

	map->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight()));
}

void Main::Release()
{
}

void Main::Update()
{
	ImGui::Text("FPS : %d", TIMER->GetFramePerSecond());
	ImGui::SliderFloat2("Scale", (float*)&map->scale, 0.0f, 100.0f);

	map->RenderGui(pickingIdx, imgIdx);
	ImGui::Text("pickingIdx : %d , %d", pickingIdx.x, pickingIdx.y);
	ImGui::Text("imgIdx : %d", imgIdx);

	map->WorldPosToTileIdx(INPUT->GetWorldMousPos(), mouseIdx);
	ImGui::Text("mouseIdx : %d , %d", mouseIdx.x, mouseIdx.y);

	ImVec2 min = ImGui::GetWindowPos();
	ImVec2 max;
	max.x = min.x + ImGui::GetWindowSize().x;
	max.y = min.y + ImGui::GetWindowSize().y;

	if (!ImGui::IsMouseHoveringRect(min, max))
	{
		if (INPUT->KeyPress(VK_LBUTTON))
		{
			if (map->WorldPosToTileIdx(INPUT->GetWorldMousPos(), mouseIdx))
			{
				map->SetTile(mouseIdx, pickingIdx, imgIdx);
			}
		}
	}

	map->Update();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
	map->Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"Game2");
	app.SetInstance(instance);
	app.InitWidthHeight(1600.0f, 800.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}