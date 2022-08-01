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

    shootVelocityGauge.SetLocalPos(Vector2(-50.0f, 70.0f));
    shootVelocityGauge.scale = Vector2(100.0f, 20.0f);
    shootVelocityGauge.rotation = 0.0f;
    shootVelocityGauge.isFilled = true;
    shootVelocityGauge.color = Color(0.2f, 0.2f, 0.7f, 1.0f);
    shootVelocityGauge.pivot = OFFSET_L;
    shootVelocityGauge.SetParentRT(player);

    shootVelocityGaugeFrame.SetLocalPos(Vector2(-50.0f, 70.0f));
    shootVelocityGaugeFrame.scale = Vector2(100.0f, 20.0f);
    shootVelocityGaugeFrame.rotation = 0.0f;
    shootVelocityGaugeFrame.isFilled = false;
    shootVelocityGaugeFrame.color = Color(0.5f, 0.5f, 0.9f, 1.0f);
    shootVelocityGaugeFrame.pivot = OFFSET_L;
    shootVelocityGaugeFrame.SetParentRT(player);
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


    if (INPUT->KeyPress(VK_SPACE))
    {
        shootVelocityGauge.scale.x += 120.0f * DELTA;
        if (shootVelocityGauge.scale.x > 100.0f)
        {
            shootVelocityGauge.scale.x = 0.0f;
        }
    }

    if (INPUT->KeyUp(VK_SPACE))
    {
        for (int i = 0; i < MAX; i++)
        {
            if (bullet[i].Shoot(player))
            {
                bullet[i].arrowSpeed += shootVelocityGauge.scale.x * 3.0f;
                bullet[i].arrowPetSpeed += shootVelocityGauge.scale.x * 5.5f;
                break;
            }
        }

        shootVelocityGauge.scale.x = 0.0f;
    }


    for (int i = 0; i < MAX; i++)
    {
        bullet[i].Update(player);
    }

    shootVelocityGauge.Update();
    shootVelocityGaugeFrame.Update();
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
    shootVelocityGauge.Render();
    shootVelocityGaugeFrame.Render();
}

void Main::ResizeScreen()
{

}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"À¯ÀçÁØ Game1");
    app.SetInstance(instance);
	app.InitWidthHeight(1400.0f, 800.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}