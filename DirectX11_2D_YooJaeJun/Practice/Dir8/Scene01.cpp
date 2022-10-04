#include "stdafx.h"

namespace Dir8
{
	Scene01::Scene01()
	{
		// tilemap
		tilemap = new ObTileMap;
		tilemap->scale = Vector2(50.0f, 50.0f);
		tilemap->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight()));
		imgIdx = 0;
		tileSize = Int2(350, 350);
		tilemap->ResizeTile(tileSize);
		tileColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
		tileState = 0;
		tilemap->CreateTileCost();

		pl = new Player();
		boss = new Boss();
	}

	Scene01::~Scene01()
	{
	}

	void Scene01::Init()
	{
		tilemap->SetTile(Int2(0, 0), Int2(4, 4));
	}

	void Scene01::Release()
	{
		SafeDelete(tilemap);
		pl->Release();
		boss->Release();
	}

	void Scene01::Update()
	{
		//FPS
		ImGui::Text("FPS : %d", TIMER->GetFramePerSecond());

		//Gui
		if (ImGui::Button("ErrorFileSystem?->Click me"))
		{
			ImGuiFileDialog::Instance()->Close();
		}

		//TileScale
		ImGui::SliderFloat2("Scale", (float*)&tilemap->scale, 0.0f, 100.0f);

		//TileSize
		if (ImGui::SliderInt2("TileSize", (int*)&tileSize, 1, 100))
		{
			tilemap->ResizeTile(tileSize);
		}

		//TilePos
		Vector2 pos = tilemap->GetWorldPos();
		if (ImGui::SliderFloat2("TilePos", (float*)&pos, -1000.0f, 1000.0f))
		{
			tilemap->SetWorldPos(pos);
		}

		//TileState
		ImGui::SliderInt("TileState", &tileState, int(TileState::none), int(TileState::tileSize));

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
				SafeDelete(tilemap->tileImages[i]);
				wstring wImgFile = L"";
				wImgFile.assign(path.begin(), path.end());
				tilemap->tileImages[i] = new ObImage(wImgFile);
			}
			if (i < 3)
			{
				ImGui::SameLine();
			}
		}

		//Coord
		tilemap->WorldPosToTileIdx(INPUT->GetWorldMousePosForZoom(), mouseIdx);
		ImGui::Text("mouseIdx : %d , %d", mouseIdx.x, mouseIdx.y);

		//ImageButton
		tilemap->RenderGui(pickingIdx, imgIdx);
		ImGui::Text("pickingIdx : %d , %d", pickingIdx.x, pickingIdx.y);
		ImGui::Text("imgIdx : %d", imgIdx);

		//maxFrame
		ImGui::InputInt2("maxFrame", (int*)&tilemap->tileImages[imgIdx]->maxFrame);

		//SaveLoad
		if (GUI->FileImGui("Save", "Save tilemap",
			".txt", "../Contents/Tiletilemap"))
		{
			string path = ImGuiFileDialog::Instance()->GetCurrentFileName();
			tilemap->file = path;
			tilemap->Save();
		}
		ImGui::SameLine();
		if (GUI->FileImGui("Load", "Load tilemap",
			".txt", "../Contents/Tiletilemap"))
		{
			string path = ImGuiFileDialog::Instance()->GetCurrentFileName();
			tilemap->file = path;
			tilemap->Load();
			tileSize = tilemap->GetTileSize();
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
				if (tilemap->WorldPosToTileIdx(INPUT->GetWorldMousePosForZoom(), mouseIdx))
				{
					tilemap->SetTile(mouseIdx, pickingIdx, imgIdx, tileState, tileColor);
				}
			}
		}

		tilemap->Update();



		boss->targetPos = pl->GetPos();

		pl->Update();
		// boss->Update();
	}

	void Scene01::LateUpdate()
	{
	}

	void Scene01::Render()
	{
		tilemap->Render();
		pl->Render();
		boss->Render();
	}

	void Scene01::ResizeScreen()
	{
	}
}