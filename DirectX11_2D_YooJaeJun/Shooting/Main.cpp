#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	score = 0;
	lastScore = 0;
	gameState = GameState::PROGRESS;
	
	bg1 = new Background;
	
	player = new Player;
	
	boss = new Enemy;

	for (int i = 0; i < fontDigitMax; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			wstring name = L"Cookie/Num" + to_wstring(j) + L".png";

			fontMaxBullet[i][j] = new UI;
			fontMaxBullet[i][j]->idle = new ObImage(name);
			fontMaxBullet[i][j]->idle->space = SPACE::SCREEN;
			fontMaxBullet[i][j]->idle->isVisible = false;
			fontMaxBullet[i][j]->idleImgSize = Vector2(28.0f, 38.0f);
			fontMaxBullet[i][j]->idle->scale = fontMaxBullet[i][j]->idleImgSize;
			fontMaxBullet[i][j]->idle->SetWorldPosX(app.GetHalfWidth() - 50.0f - 28.0f * i);
			fontMaxBullet[i][j]->idle->SetWorldPosY(-app.GetHalfHeight() + 50.0f);
			fontMaxBullet[i][j]->anchor = Anchor::RIGHTBOTTOM;
		}
	}
	for (int i = 0; i < fontDigitMax; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			wstring name = L"Cookie/Num" + to_wstring(j) + L".png";

			fontCurBullet[i][j] = new UI;
			fontCurBullet[i][j]->idle = new ObImage(name);
			fontCurBullet[i][j]->idle->space = SPACE::SCREEN;
			fontCurBullet[i][j]->idle->isVisible = false;
			fontCurBullet[i][j]->idleImgSize = Vector2(28.0f, 38.0f);
			fontCurBullet[i][j]->idle->scale = fontCurBullet[i][j]->idleImgSize;
			fontCurBullet[i][j]->idle->SetParentRT(*fontMaxBullet[fontDigitMax - 1][0]->idle);
			fontCurBullet[i][j]->idle->SetLocalPosX(-60.0f - 28.0f * i);
			fontCurBullet[i][j]->anchor = Anchor::RIGHTBOTTOM;
		}
	}

	fontSlash = new UI;
	fontSlash->idle = new ObImage(L"Cookie/Num11.png");
	fontSlash->idle->space = SPACE::SCREEN;
	fontSlash->idle->isVisible = true;
	fontSlash->idleImgSize = Vector2(27.0f, 44.0f);
	fontSlash->idle->scale = fontSlash->idleImgSize;
	fontSlash->idle->SetParentRT(*fontMaxBullet[fontDigitMax - 1][0]->idle);
	fontSlash->idle->SetLocalPosX(-30.0f);
	fontSlash->anchor = Anchor::RIGHTBOTTOM;

	lastRemainBullet = 0;

	ChangeFont(fontMaxBullet, bulletMax);

	menu = new ObRect();
	menu->scale = Vector2(100.0f, 50.0f);
	menu->space = SPACE::SCREEN;
	menu->pivot = OFFSET_LT;
	menu->SetWorldPos(Vector2(-app.GetHalfWidth(), app.GetHalfHeight()));
}

void Main::Release()
{
	bg1->Release();
	player->Release();
	boss->Release();
	for (auto& elem : fontCurBullet) for (auto& elem2 : elem) elem2->Release();
	for (auto& elem : fontMaxBullet) for (auto& elem2 : elem) elem2->Release();
	fontSlash->Release();
}

void Main::Update()
{
	if (INPUT->KeyDown('R'))
	{
		Release();
		Init();
	}

	ImGui::Text("FPS : %d", TIMER->GetFramePerSecond());

	if (ImGui::Button("vSync"))
	{
		cout << app.vSync << endl;
		app.vSync = !app.vSync;
	}

	if (ImGui::Button("reverseLR"))
	{
		player->idle->reverseLR = !player->idle->reverseLR;
	}

	ImGui::SliderFloat("rotationY", &player->idle->rotationY, 0.0f, PI);

	if (gameState == GameState::END)
	{
		player->Die();
		return;
	}

	if (INPUT->KeyPress(VK_SPACE))
	{
		bg1->idle->uv.y -= DELTA / bg1->idleImgSize.y * 200.0f;
		bg1->idle->uv.w -= DELTA / bg1->idleImgSize.y * 200.0f;
	}
	else
	{
		bg1->idle->uv.y -= DELTA / bg1->idleImgSize.y * 50.0f;
		bg1->idle->uv.w -= DELTA / bg1->idleImgSize.y * 50.0f;
	}
	bg1->Update();

	player->Update();

	boss->Update();

	int curRemainBullet = 0;
	for (auto& elem : player->bullet)
	{
		if (false == elem->isFired)
		{
			curRemainBullet++;
		}
		elem->Update();
	}

	if (lastRemainBullet != curRemainBullet)
	{
		ChangeFont(fontCurBullet, curRemainBullet);
		lastRemainBullet = curRemainBullet;
	}

	for (auto& elem : fontCurBullet) for (auto& elem2 : elem) elem2->Update();
	for (auto& elem : fontMaxBullet) for (auto& elem2 : elem) elem2->Update();
	fontSlash->Update();

	menu->Update();
}

void Main::LateUpdate()
{
	for (auto& elem : player->bullet)
	{
		if (boss->state != PlaneState::DIE && 
			boss->col->Intersect(elem->col))
		{
			elem->col->SetWorldPos(Vector2(2000.0f, 2000.0f));
			boss->Hit(elem->damage);
		}
	}

	if (menu->IntersectScreenMouse(INPUT->GetScreenMousePos()))
	{
		menu->color = Color(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else
	{
		menu->color = Color(0.0f, 0.0f, 0.0f, 1.0f);
	}
}

void Main::Render()
{
	bg1->Render();
	player->Render();
	boss->Render();

	for (auto& elem : fontCurBullet) for (auto& elem2 : elem) elem2->Render();
	for (auto& elem : fontMaxBullet) for (auto& elem2 : elem) elem2->Render();
	fontSlash->Render();

	menu->Render();
}

void Main::ResizeScreen()
{
	bg1->Spawn();
	player->Spawn();
	for (auto& elem : player->bullet) elem->Spawn();

	for (int i = 0; i < fontDigitMax; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			fontMaxBullet[i][j]->Spawn(-50.0f - 28.0f * i, 50.0f);
		}
	}
}

void Main::ChangeFont(UI* font[][10], const int num)
{
	string tmpScore = to_string(num);
	if (tmpScore.size() == fontDigitMax - 1) tmpScore = '0' + tmpScore;

	for (int i = 0; i < tmpScore.size(); i++)
	{
		for (int j = 0; j < 10; j++)
		{
			font[tmpScore.size() - 1 - i][j]->idle->isVisible = false;
		}
		font[tmpScore.size() - 1 - i][tmpScore[i] - '0']->idle->isVisible = true;
	}
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"슈팅 게임 _유재준");
	app.SetInstance(instance);
	app.InitWidthHeight(448.0f, 800.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}