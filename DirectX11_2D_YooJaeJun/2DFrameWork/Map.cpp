#include "framework.h"

Map::Map()
{
    Init();
}

Map::~Map()
{
}

void Map::Init()
{
    // tilemap
    SafeDelete(tilemap);
    tilemap = new ObTileMap;
    tilemap->scale = Vector2(100.0f, 100.0f);
    tilemap->SetWorldPos(Vector2(-app.GetHalfWidth() - 5000.0f, -app.GetHalfHeight() - 5000.0f));
    imgIdx = 1;
    tileSize = Int2(120, 120);
    tilemap->ResizeTile(tileSize);
    tileColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
    tileState = 0;
    tilemap->CreateTileCost();
    useGui = false;
}

void Map::Release()
{
    SafeDelete(tilemap);
}

void Map::Update()
{
    tilemap->Update();
    SetTilemapGUI();
}

void Map::Render()
{
    tilemap->Render();
}

void Map::SetTilemapGUI()
{
    if (false == useGui) return;


    // Gui
    if (ImGui::Button("ErrorFileSystem?->Click me"))
    {
        ImGuiFileDialog::Instance()->Close();
    }

    // TileScale
    ImGui::SliderFloat2("Scale", (float*)&tilemap->scale, 0.0f, 100.0f);

    //TileSize
    if (ImGui::SliderInt2("TileSize", (int*)&tileSize, 1, 100))
    {
        tilemap->ResizeTile(tileSize);
    }

    //TilePos
    Vector2 pos = tilemap->GetWorldPos();
    if (ImGui::SliderFloat2("TilePos", (float*)&pos, -5000.0f, 5000.0f))
    {
        tilemap->SetWorldPos(pos);
    }

    //TileState
    ImGui::SliderInt("TileState", &tileState, int(TileState::none), int(TileState::max));

    //TileColor
    ImGui::ColorEdit4("TileColor", (float*)&tileColor, ImGuiColorEditFlags_PickerHueWheel);

    //Texture
    for (int i = 0; i < imageCount; i++)
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
    ImGui::Text("cam pos : %f , %f", CAM->position.x, CAM->position.y);

    ImGui::Text("mouse pos : %f , %f", INPUT->GetWorldMousePos().x, INPUT->GetWorldMousePos().y);

    if (tilemap->WorldPosToTileIdx(INPUT->GetWorldMousePos(), mouseIdx))
    {
        ImGui::Text("mouseIdx : %d , %d", mouseIdx.x, mouseIdx.y);
        ImGui::Text("mouseOverTileState : %d", tilemap->Tiles[mouseIdx.x][mouseIdx.y].state);
        ImGui::Text("mouseOverRoomIndex : %d", tilemap->Tiles[mouseIdx.x][mouseIdx.y].roomIdx);
        ImGui::Text("mouseOverDoorDir : %d", static_cast<int>(tilemap->Tiles[mouseIdx.x][mouseIdx.y].dir));
    }

    //ImageButton
    tilemap->RenderGui(pickingIdx, imgIdx);
    ImGui::Text("pickingIdx : %d , %d", pickingIdx.x, pickingIdx.y);
    ImGui::Text("imgIdx : %d", imgIdx);

    //maxFrame
    ImGui::InputInt2("maxFrame", (int*)&tilemap->tileImages[imgIdx]->maxFrame);

    //SaveLoad
    if (GUI->FileImGui("Save", "Save Map",
        ".txt", "../Contents/TileMap"))
    {
        string path = ImGuiFileDialog::Instance()->GetCurrentFileName();
        tilemap->file = path;
        tilemap->Save();
    }
    ImGui::SameLine();
    if (GUI->FileImGui("Load", "Load Map",
        ".txt", "../Contents/TileMap"))
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
            Vector2 a = INPUT->GetWorldMousePos();
            if (tilemap->WorldPosToTileIdx(INPUT->GetWorldMousePos(), mouseIdx))
            {
                tilemap->SetTile(mouseIdx, pickingIdx, imgIdx, tileState, tileColor);
            }
        }
    }
}
