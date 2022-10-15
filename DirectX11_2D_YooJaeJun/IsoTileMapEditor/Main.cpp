#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	map = new ObIso();
	map->scale = Vector2(100.0f, 100.0f);
	//map->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight()));

	imgIdx = 0;
	tileSize = Int2(20, 20);
	tileColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
	tileState = 0;
}

void Main::Release()
{
}

void Main::Update()
{
	//FPS
	ImGui::Text("FPS : %d", TIMER->GetFramePerSecond());

	//Gui
	if (ImGui::Button("ErrorFileSystem?->Click me"))
	{
		ImGuiFileDialog::Instance()->Close();
	}

	//TileScale
	ImGui::SliderFloat2("Scale", (float*)&map->scale, 0.0f, 100.0f);

	//TileSize
	if (ImGui::SliderInt2("TileSize", (int*)&tileSize, 1, 100))
	{
		map->ResizeTile(tileSize);
	}

	//TilePos
	Vector2 pos = map->GetWorldPos();
	if (ImGui::SliderFloat2("TilePos", (float*)&pos, -1000.0f, 1000.0f))
	{
		map->SetWorldPos(pos);
	}

	//TileState
	ImGui::SliderInt("TileState", &tileState, (int)TileState::none, (int)TileState::max);

	//TileColor
	ImGui::ColorEdit4("TileColor", (float*)&tileColor, ImGuiColorEditFlags_PickerHueWheel);

	//Texture
	for (int i = 0; i < 4; i++)
	{
		string str = "Texture" + to_string(i);
		if (GUI->FileImGui(str.c_str(), str.c_str(),
			".jpg,.png,.bmp,.dds,.tga", "../Contents/Images"))
		{
			string path = ImGuiFileDialog::Instance()->GetCurrentFileName();
			SafeDelete(map->tileImages[i]);
			wstring wImgFile = L"";
			wImgFile.assign(path.begin(), path.end());
			map->tileImages[i] = new ObImage(wImgFile);
		}
		if (i < 3)
		{
			ImGui::SameLine();
		}
	}

	//Coord
	map->WorldPosToTileIdx(INPUT->GetWorldMousePos(), mouseIdx);
	ImGui::Text("mouseIdx : %d , %d", mouseIdx.x, mouseIdx.y);

	//ImageButton
	map->RenderGui(pickingIdx, imgIdx);
	ImGui::Text("pickingIdx : %d , %d", pickingIdx.x, pickingIdx.y);
	ImGui::Text("imgIdx : %d", imgIdx);

	//maxFrame
	ImGui::InputInt2("maxFrame", (int*)&map->tileImages[imgIdx]->maxFrame);

	//SaveLoad
	if (GUI->FileImGui("Save", "Save Map",
		".txt", "../Contents/TileMap"))
	{
		string path = ImGuiFileDialog::Instance()->GetCurrentFileName();
		map->file = path;
		map->Save();
	}
	ImGui::SameLine();
	if (GUI->FileImGui("Load", "Load Map", ".txt", "../Contents/TileMap"))
	{
		string path = ImGuiFileDialog::Instance()->GetCurrentFileName();
		map->file = path;
		map->Load();
		tileSize = map->GetTileSize();
	}

	//Brush
	ImVec2 min = ImGui::GetWindowPos();
	ImVec2 max;
	max.x = min.x + ImGui::GetWindowSize().x;
	max.y = min.y + ImGui::GetWindowSize().y;

	if (!ImGui::IsMouseHoveringRect(min, max))
	{
		if (INPUT->KeyPress(VK_LBUTTON))
		{
			if (map->WorldPosToTileIdx(INPUT->GetWorldMousePos(), mouseIdx))
			{
				map->SetTile(mouseIdx, pickingIdx, imgIdx, tileState, tileColor);
			}
		}
	}

	if (INPUT->KeyPress(VK_LEFT))
	{
		CAM->position.x -= 200.0f * DELTA;
	}
	if (INPUT->KeyPress(VK_RIGHT))
	{
		CAM->position.x += 200.0f * DELTA;
	}
	if (INPUT->KeyPress(VK_UP))
	{
		CAM->position.y += 200.0f * DELTA;
	}
	if (INPUT->KeyPress(VK_DOWN))
	{
		CAM->position.y -= 200.0f * DELTA;
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
	app.SetAppName(L"TileMapEditor");
	app.SetInstance(instance);
	app.InitWidthHeight(1600.0f, 800.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}