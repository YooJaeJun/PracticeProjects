#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	int idx = 0;
	for (auto& elem : background)
	{
		elem = new Background;
		if (idx >= 0 && idx < 2)
		{
			elem->img = new ObImage(L"Cookie/Oven1.png");
			elem->imgSize = Vector2(569.0f, 320.0f);
		}
		else
		{
			elem->img = new ObImage(L"Cookie/Oven2.png");
			elem->imgSize = Vector2(862.0f, 320.0f);
		}
		elem->Init();
		elem->Spawn();
		idx++;
	}
	background[0]->img->SetWorldPosX(-background[0]->img->scale.x);
	background[2]->img->SetWorldPosX(-background[2]->img->scale.x);

	CAM->position = Vector2(0.0f, 0.0f);

	player = new Player();

	idx = 0;
	for (auto& elem : floor)
	{
		elem = new Floor;
		elem->Spawn(idx);
		idx++;
	}

	for (auto& elem : obstacle)
	{
		elem = new Obstacle;
	}

	idx = 0;
	for (auto& elem : item)
	{
		elem = new Item;

		if (idx >= 0 && idx < 2)
		{
			elem->img = new ObImage(L"Cookie/Life.png");
			elem->img->maxFrame.x = 1;
			elem->img->scale = Vector2(80.0f / elem->img->maxFrame.x, 106.0f) * 0.75f;
			elem->img->ChangeAnim(ANIMSTATE::STOP, 0.1f);
			elem->type = ItemType::LIFE;
		}
		else
		{
			elem->img = new ObImage(L"Cookie/ItemBoost.png");
			elem->img->maxFrame.x = 4;
			elem->img->scale = Vector2(348.0f / elem->img->maxFrame.x, 85.0f) * 0.75f;
			elem->img->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
			elem->type = ItemType::BOOST;
		}
		elem->img->SetParentRT(*elem->col);

		idx++;
	}
}

void Main::Release()
{
	for (auto& elem : background) elem->Release();
	player->Release();
	for (auto& elem : floor) elem->Release();
	for (auto& elem : obstacle) elem->Release();
	for (auto& elem : item) elem->Release();
}

void Main::Update()
{
	if (INPUT->KeyDown('R'))
	{
		Release();
		Init();
	}

	for (auto& elem : background)
	{
		elem->Update();
	}

	for (auto& elem : floor)
	{
		elem->SpawnRandom(player->col->GetWorldPos().x, floorMax);
		elem->Update();
	}

	for (auto& elem : obstacle)
	{
		elem->Spawn(player->col->GetWorldPos().x, obstacleMax);
		elem->Update();
	}

	for (auto& elem : item)
	{
		elem->Spawn(player->col->GetWorldPos().x, itemMax);
		elem->Update();
	}

	player->Update();
}

void Main::LateUpdate()
{
	for (auto& elem : floor)
	{
		if (!elem->col->colOnOff) continue;

		if (elem->col->Intersect(player->col->GetWorldPos()))
		{
			player->LandOn();
		}
	}

	for (auto& elem : obstacle)
	{
		if (!elem->col->colOnOff) continue;

		if (elem->col->Intersect(player->col))
		{
			//player->Hit(1);
		}
	}

	for (auto& elem : item)
	{
		if (!elem->col->colOnOff) continue;

		if (elem->col->Intersect(player->col))
		{
			if (elem->type == ItemType::LIFE)
			{
				player->Hit(-2);
			}
			else if(elem->type == ItemType::BOOST)
			{
				player->Boost();
			}
			elem->col->isVisible = false;
			elem->col->colOnOff = false;
		}
	}
}

void Main::Render()
{
	for (auto& elem : background)
	{
		elem->Render();
	}

	player->Render();
	
	for (auto& elem : floor)
	{
		if (!elem->col->colOnOff) continue;
		elem->Render();
	}
	for (auto& elem : obstacle)
	{
		if (!elem->col->colOnOff) continue;
		elem->Render();
	}
	for (auto& elem : item)
	{
		if (!elem->col->colOnOff) continue;
		elem->Render();
	}
}

void Main::ResizeScreen()
{
	player->Spawn();

	for (auto& elem : background)
	{
		elem->Spawn();
	}
	background[0]->img->SetWorldPosX(-background[0]->img->scale.x);
	background[2]->img->SetWorldPosX(-background[2]->img->scale.x);

	int idx = 0;
	for (auto& elem : floor)
	{
		elem->Spawn(idx);
		idx++;
	}
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"쿠키런 모작 _유재준");
	app.SetInstance(instance);
	app.InitWidthHeight(1600.0f, 800.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}