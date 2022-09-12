#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	score = 0;
	lastScore = 0;
	gameState = GameState::PROGRESS;
	CAM->position = Vector2(0.0f, 0.0f);

	int idx = 0;
	for (auto& elem : background)
	{
		elem = new Background;
		if (idx >= 0 && idx < 2)
		{
			elem->idle = new ObImage(L"Cookie/Oven1.png");
			elem->imgSize = Vector2(569.0f, 320.0f);
		}
		else
		{
			elem->idle = new ObImage(L"Cookie/Oven2.png");
			elem->imgSize = Vector2(862.0f, 320.0f);
		}
		elem->Init();
		elem->Spawn();
		idx++;
	}
	background[1]->idle->SetWorldPosX(CAM->position.x + background[1]->idle->scale.x);
	background[3]->idle->SetWorldPosX(CAM->position.x + background[3]->idle->scale.x);

	player = new Player();

	idx = 0;
	for (auto& elem : floor)
	{
		elem = new Floor;
		elem->Spawn(idx);
		elem->idle = new ObImage(L"Cookie/Floor.png");
		elem->idle->scale = Vector2(79.0f, 48.0f) * 2.5f;
		elem->idle->SetParentRT(*elem->col);
		elem->idle->pivot = OFFSET_LT;
		idx++;
	}

	idx = 0;
	for (auto& elem : obstacleBottom)
	{
		elem = new Obstacle;
		elem->col->pivot = OFFSET_B;
		elem->col->SetWorldPosX(app.GetWidth());
		elem->col->SetWorldPosY(-app.GetHalfHeight() + 48.0f * 2.5f);
		elem->scaleCoefX = 0.4f;
		elem->scaleCoefY = 0.7f;
		elem->col->scale = Vector2(87.0f * elem->scaleCoefX, 118.0f * elem->scaleCoefY);
		elem->idle = new ObImage(L"Cookie/land0001_tm001_jp1B.png");
		elem->idle->scale = Vector2(87.0f * 0.8f, 118.0f * 0.8f);
		elem->idle->SetParentRT(*elem->col);
		elem->idle->pivot = OFFSET_B;
		idx++;
	}

	idx = 0;
	for (auto& elem : obstacleTop)
	{
		elem = new Obstacle;
		elem->col->pivot = OFFSET_B;
		elem->col->SetWorldPosX(app.GetWidth());
		elem->col->SetWorldPosY(-app.GetHalfHeight() + 400.0f);
		elem->scaleCoefX = 0.9f;
		elem->scaleCoefY = 1.0f;
		elem->col->scale = Vector2(165.0f * elem->scaleCoefX, 493.0f * elem->scaleCoefY);
		elem->idle = new ObImage(L"Cookie/land0001_tm001_sdA.png");
		elem->idle->scale = Vector2(165.0f * elem->scaleCoefX, 493.0f * elem->scaleCoefY);
		elem->idle->SetParentRT(*elem->col);
		elem->idle->pivot = OFFSET_B;
		idx++;
	}

	idx = 0;
	for (auto& elem : itemJelly)
	{
		elem = new Item;
		elem->idle = new ObImage(L"Cookie/JellyBin.png");
		elem->idle->maxFrame.x = 1;
		elem->idle->scale = Vector2(25.0f / elem->idle->maxFrame.x, 34.0f);
		elem->idle->SetParentRT(*elem->col);
		elem->type = ItemType::SCORE;
		elem->Spawn(0.0f, idx);
		idx++;
	}

	idx = 0;
	for (auto& elem : itemLife)
	{
		elem = new Item;
		elem->idle = new ObImage(L"Cookie/Life.png");
		elem->idle->maxFrame.x = 1;
		elem->idle->scale = Vector2(80.0f / elem->idle->maxFrame.x, 106.0f) * 0.75f;
		elem->idle->ChangeAnim(ANIMSTATE::STOP, 0.1f);
		elem->idle->SetParentRT(*elem->col);
		elem->type = ItemType::LIFE;
		elem->Spawn(0.0f, idx);
		idx++;
	}

	idx = 0;
	for (auto& elem : itemBoost)
	{
		elem = new Item;
		elem->idle = new ObImage(L"Cookie/ItemBoost.png");
		elem->idle->maxFrame.x = 4;
		elem->idle->scale = Vector2(348.0f / elem->idle->maxFrame.x, 85.0f) * 0.75f;
		elem->idle->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		elem->idle->SetParentRT(*elem->col);
		elem->type = ItemType::BOOST;
		elem->Spawn(0.0f, idx);
		idx++;
	}

	for (auto& elem : gauge)
	{
		elem = new UI;
	}
	gauge[0]->idle = new ObImage(L"Cookie/gaugebg_heart02.png");
	gauge[0]->imgSize = Vector2(750.0f, 46.0f);
	gauge[0]->idle->scale = gauge[0]->imgSize;
	gauge[0]->Spawn(20.0f, -10.0f);

	gauge[1]->idle = new ObImage(L"Cookie/gauge_heart_orange.png");
	gauge[1]->imgSize = Vector2(750.0f, 46.0f);
	gauge[1]->idle->scale = gauge[1]->imgSize;
	gauge[1]->Spawn(20.0f, -10.0f);

	gauge[2]->idle = new ObImage(L"Cookie/icon_heartLife.png");
	gauge[2]->imgSize = Vector2(54.0f, 54.0f);
	gauge[2]->idle->scale = gauge[2]->imgSize;
	gauge[2]->Spawn(0.0f, -5.0f);

	for (auto& elem : gauge)
	{
		elem->idle->space = SPACE::SCREEN;
		elem->idle->pivot = OFFSET_LT;
	}

	for (int i = 0; i < fontDigitMax; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			fontScore[i][j] = new UI;
			wstring name = L"Cookie/Num" + to_wstring(j) + L".png";
			fontScore[i][j]->idle = new ObImage(name);
			fontScore[i][j]->idle->space = SPACE::SCREEN;
			fontScore[i][j]->idle->isVisible = false;
			fontScore[i][j]->idle->scale = Vector2(28.0f, 38.0f);
			fontScore[i][j]->idle->SetWorldPosX(-app.GetHalfWidth() + 50.0f + 28.0f * i);
			fontScore[i][j]->idle->SetWorldPosY(app.GetHalfHeight() - 80.0f);
		}
	}
	fontScore[0][0]->idle->isVisible = true;
}

void Main::Release()
{
	for (auto& elem : background) elem->Release();
	player->Release();
	for (auto& elem : floor) elem->Release();
	for (auto& elem : obstacleBottom) elem->Release();
	for (auto& elem : obstacleTop) elem->Release();
	for (auto& elem : itemJelly) elem->Release();
	for (auto& elem : itemLife) elem->Release();
	for (auto& elem : itemBoost) elem->Release();
	for (auto& elem : gauge) elem->Release();
	for (auto& elem : fontScore) for(auto& elem2 : elem) elem2->Release();
}

void Main::Update()
{
	if (gameState == GameState::END)
	{
		player->Die();
	}

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
		if (player->col->GetWorldPos().x - elem->col->GetWorldPos().x > 700.0f)
		{
			elem->SpawnRandom(player->col->GetWorldPos().x, floorMax);
		}
		elem->Update();
	}

	int idx = 0;
	for (auto& elem : obstacleBottom)
	{
		if (player->col->GetWorldPos().x - elem->col->GetWorldPos().x > 500.0f)
		{
			elem->Spawn(player->col->GetWorldPos().x, idx);
		}
		elem->Update();
		idx++;
	}

	idx = 0;
	for (auto& elem : obstacleTop)
	{
		if (player->col->GetWorldPos().x - elem->col->GetWorldPos().x > 500.0f)
		{
			elem->Spawn(player->col->GetWorldPos().x, idx);
			elem->col->isVisible = true;
			elem->col->colOnOff = true;
		}
		elem->Update();
		idx++;
	}

	idx = 0;
	for (auto& elem : itemJelly)
	{
		if (player->col->GetWorldPos().x - elem->col->GetWorldPos().x > 500.0f)
		{
			elem->Spawn(player->col->GetWorldPos().x, itemJellyMax);
			elem->col->colOnOff = true;
		}
		elem->Update();
		idx++;
	}

	idx = 0;
	for (auto& elem : itemBoost)
	{
		if (player->col->GetWorldPos().x - elem->col->GetWorldPos().x > 500.0f)
		{
			elem->Spawn(player->col->GetWorldPos().x, idx);
		}
		elem->Update();
		idx++;
	}

	idx = 0;
	for (auto& elem : itemLife)
	{
		if (player->col->GetWorldPos().x - elem->col->GetWorldPos().x > 500.0f)
		{
			elem->Spawn(player->col->GetWorldPos().x, idx);
		}
		elem->Update();
		idx++;
	}

	player->Update();


	if (false == gauge[1]->DownGauge())
	{
		gameState = GameState::END;
	}
	for (auto& elem : gauge) elem->Update();

	for (auto& elem : fontScore) for (auto& elem2 : elem) elem2->Update();
}

void Main::LateUpdate()
{
	if (player->col->GetWorldPos().y + player->col->scale.y < -app.GetHalfHeight())
	{
		gauge[1]->Hit(300.0f);
		player->Hit(2);
		player->Spawn();
	}

	for (auto& elem : floor)
	{
		if (!elem->col->colOnOff) continue;

		if (elem->col->Intersect(player->col->GetWorldPos()))
		{
			player->LandOn();
		}
	}

	for (auto& elem : obstacleBottom)
	{
		if (!elem->col->colOnOff) continue;
		if (elem->col->Intersect(player->col))
		{
			if (player->isBoost)
			{
				score += 1;
				elem->Hit();
				break;
			}
			else if (false == player->isHit)
			{
				player->Hit(1);
				gauge[1]->Hit(150.0f);
				break;
			}
		}
	}
	for (auto& elem : obstacleTop)
	{
		if (!elem->col->colOnOff) continue;
		if (elem->col->Intersect(player->col))
		{
			if (player->isBoost)
			{
				score += 1;
				elem->Hit();
				break;
			}
			else if (false == player->isHit)
			{
				player->Hit(1);
				gauge[1]->Hit(150.0f);
				break;
			}
		}
	}

	for (auto& elem : itemJelly)
	{
		if (!elem->col->colOnOff) continue;
		if (elem->col->Intersect(player->col))
		{
			score += 1;
			elem->col->isVisible = false;
			elem->col->colOnOff = false;
		}
	}
	for (auto& elem : itemLife)
	{
		if (!elem->col->colOnOff) continue;
		if (elem->col->Intersect(player->col))
		{
			player->Hit(-2);
			gauge[1]->Hit(-150.0f);
			elem->col->colOnOff = false;
		}

	}
	for (auto& elem : itemBoost)
	{
		if (!elem->col->colOnOff) continue;
		if (elem->col->Intersect(player->col))
		{
			player->Boost();
			elem->col->colOnOff = false;
		}
	}

	if (lastScore != score)
	{
 		ChangeScoreUI();
		lastScore = score;
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

	for (auto& elem : obstacleBottom)
	{
		if (!elem->col->colOnOff) continue;
		elem->Render();
	}
	for (auto& elem : obstacleTop)
	{
		if (!elem->col->colOnOff) continue;
		elem->Render();
	}

	for (auto& elem : itemJelly)
	{
		if (!elem->col->colOnOff) continue;
		elem->Render();
	}
	for (auto& elem : itemLife)
	{
		if (!elem->col->colOnOff) continue;
		elem->Render();
	}
	for (auto& elem : itemBoost)
	{
		if (!elem->col->colOnOff) continue;
		elem->Render();
	}

	for (auto& elem : gauge) elem->Render();
	for (auto& elem : fontScore) for (auto& elem2 : elem) elem2->Render();
}

void Main::ResizeScreen()
{
	player->Spawn();

	for (auto& elem : background)
	{
		elem->Spawn();
	}
	background[1]->idle->SetWorldPosX(CAM->position.x + background[1]->idle->scale.x);
	background[3]->idle->SetWorldPosX(CAM->position.x + background[3]->idle->scale.x);

	int idx = 0;
	for (auto& elem : floor)
	{
		elem->Spawn(idx);
		idx++;
	}

	for (auto& elem : obstacleBottom) 
	{
		elem->col->SetWorldPosY(-app.GetHalfHeight() + 48.0f * 2.5f);
	}
	for (auto& elem : obstacleTop)
	{
		elem->col->SetWorldPosY(-app.GetHalfHeight() + 400.0f);
	}
	for (auto& elem : itemJelly)
	{
		elem->col->SetWorldPosY(-app.GetHalfHeight() + 200.0f);
	}
	for (auto& elem : itemLife)
	{
		elem->col->SetWorldPosY(-app.GetHalfHeight() + 200.0f);
	}
	for (auto& elem : itemBoost)
	{
		elem->col->SetWorldPosY(-app.GetHalfHeight() + 200.0f);
	}

	gauge[0]->Spawn(20.0f, -10.0f);
	gauge[1]->Spawn(20.0f, -10.0f);
	gauge[2]->Spawn(0.0f, -5.0f);

	for (int i = 0; i < fontDigitMax; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			fontScore[i][j]->idle->SetWorldPosX(-app.GetHalfWidth() + 50.0f + 28.0f * i);
			fontScore[i][j]->idle->SetWorldPosY(app.GetHalfHeight() - 80.0f);
		}
	}
}

void Main::ChangeScoreUI()
{
	string tmpScore = to_string(score);
	for (int i = 0; i < tmpScore.size(); i++)
	{
		for (int j = 0; j < 10; j++)
		{
			fontScore[i][j]->idle->isVisible = false;
		}
		fontScore[i][tmpScore[i] - '0']->idle->isVisible = true;
	}
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"쿠키런 모작 _유재준");
	app.SetInstance(instance);
	app.InitWidthHeight(1200.0f, 600.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}