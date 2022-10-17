#include "stdafx.h"
#include "Main.h"
using namespace DanmakuEditor;

void Main::Init()
{
	bullets.resize(5);
	InitBullet();
}

void DanmakuEditor::Main::InitBullet()
{
	bullets.resize(bullets.size() * 2);
	for (auto& elem : bullets)
	{
		if (!elem)
		{
			elem = new ObImage(L"EnterTheGungeon/player_1/Bullet_0.png");
			elem->scale = Vector2(16.0f, 16.0f) * 2.0f;
			elem->isVisible = false;
		}
	}
}

void Main::Release()
{
	for (auto& elem : bullets) SafeDelete(elem);
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

	//Coord
	ImGui::Text("mousePos : %f , %f", INPUT->GetWorldMousePos().x, INPUT->GetWorldMousePos().y);
	
	switch (clickState)
	{
	case DanmakuEditor::Main::ClickState::none:
		if (INPUT->KeyDown(VK_LBUTTON))
		{
			Vector2 mouse = INPUT->GetWorldMousePos();
			start.push_back(mouse);
			lines.push_back(new ObLine(mouse, Vector2(-400.0f, 0.0f)));
			lines.back()->isVisible = false;
			clickState = ClickState::keyDown;
		}
		break;
	case DanmakuEditor::Main::ClickState::keyDown:
		if (INPUT->KeyDown(VK_LBUTTON))
		{
			Vector2 mouse = INPUT->GetWorldMousePos();
			end.push_back(mouse);
			lines.back()->SetW(ObNode(mouse));
			lines.back()->isVisible = true;
			clickState = ClickState::none;
		}
		break;
	default:
		break;
	}

	if (ImGui::Button("Fire"))
	{
		fireFlag = true;
		timeExitFire = 0.0f;

		if (end.size() > bullets.size())
		{
			InitBullet();
		}
		for (int i = 0; i < end.size(); i++)
		{
			bullets[i]->isVisible = true;
			bullets[i]->SetWorldPos(start[i]);
		}
	}

	if (fireFlag)
	{
		for (int i = 0; i < end.size(); i++)
		{
			Vector2 dir = end[i] - start[i];
			dir.Normalize();
			bullets[i]->MoveWorldPos(dir * 300.0f * DELTA);
		}

		if (TIMER->GetTick(timeExitFire, 2.0f))
		{
			fireFlag = false;
		}
	}
	



	for (auto& elem : bullets) elem->Update();
	for (auto& elem : lines) elem->Update();
}

void Main::LateUpdate()
{
}
void Main::Render()
{
	for (auto& elem : bullets) elem->Render();
	for (auto& elem : lines) elem->Render();
}

void Main::ResizeScreen()
{

}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"DanmakuEditor");
	app.SetInstance(instance);
	app.InitWidthHeight(1400.0f, 800.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}
