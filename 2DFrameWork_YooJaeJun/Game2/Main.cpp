#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    player = make_shared<Unit>();
    player->name = "1p";
    
    enemy = make_shared<Unit>();
    enemy->hitbox.SetWorldPos(Vector2(500.0f, -300.0f));
    enemy->name = "2p";

    for (int i = 0; i < bulletMax; i++) 
    {
        bullet[i] = make_shared<Bullet>();
    }
}

void Main::Release()
{
}

void Main::Act(shared_ptr<Unit> unit)
{
    unit->Move();

    if (INPUT->KeyDown(VK_SPACE))
    {
        unit->shootGauge.scale.x = 0.0f;
    }

    if (INPUT->KeyPress(VK_SPACE))
    {
        unit->shootGauge.scale.x += 100.0f * DELTA;

        if (unit->shootGauge.scale.x > 100.0f)
        {
            unit->shootGauge.scale.x = 0.0f;
        }
    }

    if (INPUT->KeyUp(VK_SPACE))
    {
        for (int i = 0; i < bulletMax; i++)
        {
            if (bullet[i]->Shoot(
                unit->hitbox,
                unit->shootGauge.scale.x,
                unit->firePos.GetWorldPos()))
            {
                break;
            }
        }

        turn = !turn;
    }
}

void Main::Update()
{
    if (turn == 0)  Act(player);
    else            Act(enemy);

    player->Update();
    enemy->Update();

    for (int i = 0; i < bulletMax; i++)
    {
        bullet[i]->Update(player->hitbox);
    }
}

void Main::LateUpdate()
{
    player->LateUpdate();
    enemy->LateUpdate();

    for (int i = 0; i < bulletMax; i++)
    {
        bullet[i]->LateUpdate();

        if (bullet[i]->hitbox.isVisible and 
            player->hitbox.Intersect(&bullet[i]->hitbox))
        {
            bullet[i]->hitbox.isVisible = false;
            bullet[i]->hitbox.SetWorldPos(Vector2(2000.0f, 2000.0f));

            player->HitFrom(30);
        }

        if (bullet[i]->hitbox.isVisible and
            enemy->hitbox.Intersect(&bullet[i]->hitbox))
        {
            bullet[i]->hitbox.isVisible = false;
            bullet[i]->hitbox.SetWorldPos(Vector2(2000.0f, 2000.0f));

            enemy->HitFrom(30);
        }
    }
}

void Main::Render()
{
    player->Render();
    enemy->Render();

    for (int i = 0; i < bulletMax; i++)
    {
        bullet[i]->Render();
    }
}

void Main::ResizeScreen()
{
}



int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"윾재준의 신나는 도형 포트리스 ↖^_^↗");
	app.SetInstance(instance);
	app.InitWidthHeight(1280.0f, 720.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}