#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    player.SetWorldPos(Vector2(0.0f, 0.0f));
    player.scale = Vector2(100.0f, 100.0f);
    player.rotation = 0.0f;
    player.isFilled = true;
    player.isAxis = true;
    player.color = Color(0.2f, 0.1f, 0.8f, 0.5f);
    //player.pivot = OFFSET_LT;

    pet.SetLocalPos(Vector2(100.0f, 100.0f));
    pet.scale = Vector2(30.0f, 30.0f);
    pet.rotation = 0.0f;
    pet.isAxis = true;
    pet.isFilled = true;
    pet.color = Color(0.8f, 0.5f, 0.3f, 0.5f);
    //pet.pivot = OFFSET_B;
    pet.SetParentRT(player);
}

void Main::Release()
{
}

void Main::Update()
{
    if (INPUT->KeyPress(VK_UP))
    {
        //player.MoveWorldPos(-player.GetDown() * 200.0f * DELTA);
        player.MoveWorldPos(player.GetUp() * 200.0f * DELTA);
    }
    else if (INPUT->KeyPress(VK_DOWN))
    {
        //player.MoveWorldPos(player.GetDown() * 200.0f * DELTA);
        player.MoveWorldPos(-player.GetUp() * 200.0f * DELTA);
    }

    if (INPUT->KeyPress(VK_LEFT))
    {
        player.rotation += 120.0f * ToRadian * DELTA;
    }
    else if (INPUT->KeyPress(VK_RIGHT))
    {
        player.rotation -= 120.0f * ToRadian * DELTA;
    }

    pet.rotation2 += 60.0f * ToRadian * DELTA;

    player.Update();
    pet.Update(); 



    if (INPUT->KeyDown(VK_SPACE))
        for (int i = 0; i < MAX; i++)
            if (bullet[i].Shoot(player)) 
                break;

    for (int i = 0; i < MAX; i++)
    {
        bullet[i].Update(player);
    }

    if (INPUT->KeyDown('R')) //재장전
    {
        for (int i = 0; i < MAX; i++)
        {
            if (bullet[i].arrow.isVisible)
            {
                bullet[i].arrow.isVisible = false;
                bullet[i].arrow.SetWorldPos(Vector2(1000.0f, 1000.0f));

                bullet[i].arrowPet.SetLocalPos(Vector2(40.f, 40.f));
                bullet[i].arrowPet.rotation2 = 0.0f;

                bullet[i].arrow.Update();
                bullet[i].arrowPet.Update();
            }
        }
    }
}

void Main::LateUpdate()
{
}

void Main::Render()
{
    player.Render();
    pet.Render();

    for (int i = 0; i < MAX; i++)
    {
        bullet[i].Render();
    }
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"유재준 Game1");
    app.SetInstance(instance);
	app.InitWidthHeight(1400.0f, 800.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}