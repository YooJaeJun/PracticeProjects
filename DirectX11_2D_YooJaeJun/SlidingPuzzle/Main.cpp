#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    mole = new ObImage(L"bono4.jpg");
    mole->scale = Vector2(600.0f, 600.0f);
    mole->SetWorldPos(Vector2(app.GetHalfWidth() - mole->scale.x / 2, 0.0f));

    puzzleNum = 3;
    SetPuzzle();
    Shuffle();

    empty = 0;
}

void Main::Release()
{
    SafeDelete(mole);
    for (auto& puzzle : puzzles) SafeDelete(puzzle);
}

void Main::Update()
{
    // ImGui::SliderFloat2("Scale", (float*)&mole->scale, 0.0f, 600.0f);
    // ImGui::SliderFloat4("UV", (float*)&mole->uv, 0.0f, 1.0f);

    if (INPUT->KeyDown(VK_UP))
    {
        if (empty - puzzleNum >= 0)
        {
            puzzles[empty]->uv = puzzles[empty - puzzleNum]->uv;
            empty -= puzzleNum;
        }
    }
    else if (INPUT->KeyDown(VK_DOWN))
    {
        if (empty + puzzleNum < puzzleNum * puzzleNum)
        {
            puzzles[empty]->uv = puzzles[empty + puzzleNum]->uv;
            empty += puzzleNum;
        }
    }
    else if (INPUT->KeyDown(VK_LEFT))
    {
        if (empty % puzzleNum != 0)
        {
            puzzles[empty]->uv = puzzles[empty - 1]->uv;
            empty--;
        }
    }
    else if (INPUT->KeyDown(VK_RIGHT))
    {
        if (empty % puzzleNum != puzzleNum - 1)
        {
            puzzles[empty]->uv = puzzles[empty + 1]->uv;
            empty++;
        }
    }



    if (ImGui::SliderInt("puzzleNum", &puzzleNum, 1, 10))
    {
        empty = 0;
        SetPuzzle();
        Shuffle();
    }

    if (ImGui::Button("Shuffle"))
    {
        Shuffle();
    }

    if (ImGui::Button("Cheat"))
    {
        for (int i = 0; i < puzzles.size(); i++)
        {
            if (i == empty) continue;
            puzzles[i]->uv = originUv[i];
        }
    }



    mole->Update();
    for (int i = 0; i < puzzles.size(); i++)
    {
        if (i == empty) continue;
        puzzles[i]->Update();
    }
}

void Main::SetPuzzle()
{
    puzzles.resize(puzzleNum * puzzleNum);
    randUv.resize(puzzleNum * puzzleNum);
    originUv.resize(puzzleNum * puzzleNum);

    int idx = 0;
    for (auto& puzzle : puzzles)
    {
        if (puzzle == nullptr)
        {
            puzzle = new ObImage(L"bono4.jpg");
        }
        puzzle->scale = mole->scale / puzzleNum;

        float x = puzzle->scale.x * (idx % puzzleNum);
        float y = puzzle->scale.y * (idx / puzzleNum);
        float z = puzzle->scale.x * (idx % puzzleNum + 1);
        float w = puzzle->scale.y * (idx / puzzleNum + 1);

        float nx = -app.GetHalfWidth() + x;     // screen to world
        float ny = app.GetHalfHeight() - y - mole->scale.x / puzzleNum;
        puzzle->SetWorldPos(Vector2(nx + puzzle->scale.x / 2, ny + puzzle->scale.y / 2));

        originUv[idx] = randUv[idx] = Vector4(
            x / mole->scale.x, y / mole->scale.y,
            z / mole->scale.x, w / mole->scale.y);

        idx++;
    }
}

void Main::Shuffle()
{
    for (int i = 0; i < randUv.size() - 1; i++)
    {
        if (i == empty) continue;
        swap(randUv[i], (randUv[RANDOM->Int(i + 1, randUv.size() - 1)]));
    }
    for (int i = 0; i < puzzles.size(); i++)
    {
        if (i == empty) continue;
        puzzles[i]->uv = randUv[i];
    }
}

void Main::LateUpdate()
{
}

void Main::Render()
{
    mole->Render();
    for (int i = 0; i < puzzles.size(); i++)
    {
        if (i == empty) continue;
        puzzles[i]->Render();
    }
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"유재준 슬라이딩 퍼즐");
    app.SetInstance(instance);
    app.InitWidthHeight(1200.0f, 600.0f);
    Main* main = new Main();
    int wParam = (int)WIN->Run(main);
    WIN->DeleteSingleton();     // 창이 없어지고 난 후 
    SafeDelete(main);           // 메모리 해제
    return wParam;
}