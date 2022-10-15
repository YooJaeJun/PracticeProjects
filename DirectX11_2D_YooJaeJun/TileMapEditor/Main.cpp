#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	map = new ObTileMap();
	map->file = "map2.txt";
	map->Load();
	map->scale = Vector2(50.0f, 50.0f);
	map->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight()));
	LIGHT->light.radius = 3000.0f;
	imgIdx = 0;
	tileSize = Int2(50, 50);
	tileColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
	tileState = 0;
}

void Main::Release()
{
	SafeDelete(map);
}


void Main::Update()
{
	if (INPUT->KeyPress(VK_LEFT) || INPUT->KeyPress('A'))
	{
		CAM->position.x -= 300.0f * DELTA;
	}
	if (INPUT->KeyPress(VK_RIGHT) || INPUT->KeyPress('D'))
	{
		CAM->position.x += 300.0f * DELTA;
	}
	if (INPUT->KeyPress(VK_UP) || INPUT->KeyPress('W'))
	{
		CAM->position.y += 300.0f * DELTA;
	}
	if (INPUT->KeyPress(VK_DOWN) || INPUT->KeyPress('S'))
	{
		CAM->position.y -= 300.0f * DELTA;
	}
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
	ImGui::SliderInt("TileState", &tileState, int(TileState::none), int(TileState::max));

	//TileColor
	ImGui::ColorEdit4("TileColor", (float*)&tileColor, ImGuiColorEditFlags_PickerHueWheel);

	//Texture
	for (int i = 0; i < 4; i++)
	{
		string str = "Texture" + to_string(i);
		if (GUI->FileImGui(str.c_str(), str.c_str(),
			".jpg,.png,.bmp,.dds,.tga", "../Contents/Images/EnterTheGungeon"))
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
	if (GUI->FileImGui("Load", "Load Map",
		".txt", "../Contents/TileMap"))
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
	app.InitWidthHeight(1400.0f, 800.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}
