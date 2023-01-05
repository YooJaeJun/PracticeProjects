#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	bg = new ObImage(L"zzangu_3.jpg");
	bg->scale = Vector2(500.0f, 500.0f);
	bg->SetWorldPosX(250.0f);

	puzzleNum = 3;
	zero = Int2(0, 0);

	CreatePuzzle();
	ShufflePuzzle();
}

void Main::Release()
{
	SafeDelete(bg);
	DeletePuzzle();
}

void Main::Update()
{
	if (INPUT->KeyDown(VK_UP))
	{
		if (zero.y > 0)
		{
			Utility::Swap(puzzle[zero.x][zero.y]->uv, puzzle[zero.x][zero.y - 1]->uv);
			zero.y--;
		}
	}

	if (INPUT->KeyDown(VK_DOWN))
	{
		if (zero.y < puzzleNum - 1)
		{
			Utility::Swap(puzzle[zero.x][zero.y]->uv, puzzle[zero.x][zero.y + 1]->uv);
			zero.y++;
		}
	}

	if (INPUT->KeyDown(VK_LEFT))
	{
		if (zero.x > 0)
		{
			Utility::Swap(puzzle[zero.x][zero.y]->uv, puzzle[zero.x - 1][zero.y]->uv);
			zero.x--;
		}
	}

	if (INPUT->KeyDown(VK_RIGHT))
	{
		if (zero.x < puzzleNum - 1)
		{
			Utility::Swap(puzzle[zero.x][zero.y]->uv, puzzle[zero.x + 1][zero.y]->uv);
			zero.x++;
		}
	}

	int tempNum = puzzleNum;
	if (ImGui::SliderInt("Num", &tempNum, 2, 10))
	{
		DeletePuzzle();

		puzzleNum = tempNum;
		CreatePuzzle();
		ShufflePuzzle();
	}

	if (ImGui::Button("Shuffle"))
	{
		ShufflePuzzle();
	}

	if (ImGui::Button("Answer"))
	{
		CompletePuzzle();
	}

	bg->Update();
	for (int x = 0; x < puzzleNum; x++)
	{
		for (int y = 0; y < puzzleNum; y++)
		{
			puzzle[x][y]->Update();
		}
	}
}

void Main::LateUpdate()
{
}

void Main::Render()
{
	bg->Render();
	for (int x = 0; x < puzzleNum; x++)
	{
		for (int y = 0; y < puzzleNum; y++)
		{
			if (zero.x == x && zero.y == y)
			{
				continue;
			}
			puzzle[x][y]->Render();
		}
	}
}

void Main::ResizeScreen()
{
}

void Main::ShufflePuzzle()
{
	for (int i = 0; i < 1000; i++)
	{
		int sour1 = rand() % puzzleNum;
		int sour2 = rand() % puzzleNum;
		int dest1 = rand() % puzzleNum;
		int dest2 = rand() % puzzleNum;

		Utility::Swap(puzzle[sour1][dest1]->uv, puzzle[sour2][dest2]->uv);
	}
}

void Main::CompletePuzzle()
{
	for (int i = 0; i < puzzleNum; i++)
	{
		for (int j = 0; j < puzzleNum; j++)
		{
			puzzle[i][j]->uv = Vector4((i * 1.0f) / puzzleNum, (j * 1.0f) / puzzleNum,
				(i + 1.0f) / puzzleNum, (j + 1.0f) / puzzleNum);
		}
	}

}

void Main::CreatePuzzle()
{
	puzzle = new ObImage * *[puzzleNum];
	for (int i = 0; i < puzzleNum; i++)
	{
		puzzle[i] = new ObImage * [puzzleNum];

		for (int j = 0; j < puzzleNum; j++)
		{
			puzzle[i][j] = new ObImage(L"zzangu_3.jpg");
			puzzle[i][j]->pivot = OFFSET_LT;
			puzzle[i][j]->scale = Vector2(500.0f / puzzleNum, 500.0f / puzzleNum);
			puzzle[i][j]->SetLocalPos(Vector2(i * 500.0f / puzzleNum, -j * 500.0f / puzzleNum));
			puzzle[i][j]->uv = Vector4((i * 1.0f) / puzzleNum, (j * 1.0f) / puzzleNum,
				(i + 1.0f) / puzzleNum, (j + 1.0f) / puzzleNum);

			if (!(i == 0 && j == 0))
			{
				puzzle[i][j]->SetParentRT(*puzzle[0][0]);
			}
		}

		puzzle[0][0]->SetWorldPos(Vector2(-500.0f, 250.0f));
	}
}

void Main::DeletePuzzle()
{
	for (int x = 0; x < puzzleNum; x++)
	{
		for (int y = 0; y < puzzleNum; y++)
		{
			SafeDelete(puzzle[x][y]);
		}
		SafeDelete(puzzle[x]);
	}
	SafeDelete(puzzle);
}



int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"Game2");
	app.SetInstance(instance);
	app.InitWidthHeight(1000.0f, 500.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}