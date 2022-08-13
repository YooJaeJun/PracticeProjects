#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    xAxis.scale.x = 1280.0f;
    xAxis.color = Color(1.0f, 0.0f, 0.0f, 1.0f);
    xAxis.pivot = OFFSET_N;
    xAxis.Update();

    yAxis.scale.x = 1080.0f;
    yAxis.color = Color(0.0f, 1.0f, 0.0f, 1.0f);
    yAxis.pivot = OFFSET_N;
    yAxis.rotation = DIV2PI;
    yAxis.Update();


    player.SetWorldPos(Vector2(0.0f, 0.0f));
    player.scale = Vector2(100.0f, 100.0f);
    player.rotation = 0.0f;
    player.isFilled = true;
    player.isAxis = true;
    player.color = Color(0.0f, 0.0f, 1.0f, 1.0f);
    player.pivot = OFFSET_N;

    firePos.SetParentRT(player);    
    firePos.SetLocalPos(Vector2(200.0f, 0.0f));
    firePos.scale = Vector2(100.0f, 100.0f);
    firePos.isAxis = false;

    playerGauge.SetLocalPos(Vector2(-75.0f, 75.0f));
    playerGauge.scale = Vector2(150.0f, 30.0f);
    playerGauge.rotation = 0.0f;
    playerGauge.isFilled = true;
    playerGauge.color = Color(0.5f, 0.5f, 0.0f, 1.0f);
    playerGauge.pivot = OFFSET_L;
    //playerGauge.pivot = Vector2(0.48f, 0.0f);

    playerGauge.SetParentRT(player);

    pet.SetLocalPos(Vector2(100.0f, 100.0f));
    pet.scale = Vector2(30.0f, 30.0f);
    pet.rotation = 0.0f;
    pet.isAxis = true;
    pet.isFilled = true;
    //pet.pivot = OFFSET_B;
    pet.SetParentRT(player);
}

void Main::Release()
{
}

void Main::Update()
{
    cout << "Mouse : " << INPUT->GetWorldMousPos().x << "," 
        << INPUT->GetWorldMousPos().y << endl;

    Vector2 dir = INPUT->GetWorldMousPos() - player.GetWorldPos();
    player.rotation = Utility::DirToRadian(dir);

    if (INPUT->KeyPress('A'))
    {
        //player.MoveWorldPos(-player.GetDown() * 200.0f * DELTA);
        player.MoveWorldPos(-player.GetRight() * 200.0f * DELTA);
    }
    else if (INPUT->KeyPress('D'))
    {
        //player.MoveWorldPos(player.GetDown() * 200.0f * DELTA);
        player.MoveWorldPos(player.GetRight() * 200.0f * DELTA);
    }

    if (INPUT->KeyPress('W'))
    {
        player.MoveWorldPos(player.GetUp() * 200.0f * DELTA);
    }
    else if (INPUT->KeyPress('S'))
    {
        player.MoveWorldPos(-player.GetUp() * 200.0f * DELTA);
    }

    if (INPUT->KeyPress(VK_UP))
    {
        CAM->position += UP * 200.0f * DELTA;
    }
    else if (INPUT->KeyPress(VK_DOWN))
    {
        CAM->position += DOWN * 200.0f * DELTA;
    }

    if (INPUT->KeyPress(VK_RIGHT))
    {
        CAM->position += RIGHT * 200.0f * DELTA;
    }
    else if (INPUT->KeyPress(VK_LEFT))
    {
        CAM->position += LEFT * 200.0f * DELTA;
    }
    
    if (INPUT->KeyDown(VK_LBUTTON))
    {
        playerGauge.scale.x = 0.0f;
    }

    if (INPUT->KeyPress(VK_LBUTTON))
    {
        playerGauge.scale.x += 100.0f * DELTA;

        if (playerGauge.scale.x > 150.0f)
        {
            playerGauge.scale.x = 0.0f;
        }
    }

    if (INPUT->KeyUp(VK_LBUTTON))
    {
        for (int i = 0; i < MAX; i++)
        {
            if (bullet[i].Shoot(player, playerGauge.scale.x, firePos.GetWorldPos()))
            {
                break;
            }
        }
    }

    //if (INPUT->KeyDown('R')) //¿Á¿Â¿¸
    //{
    //    isFired = false;
    //    arrow.SetWorldPos(Vector2(1000.0f, 1000.0f));
    //}

    pet.rotation2 += 60.0f * ToRadian * DELTA;

    player.Update();
    pet.Update(); 

    for (int i = 0; i < MAX; i++)
    {
        bullet[i].Update(player);
    }
    playerGauge.Update();
    firePos.Update();
}

void Main::LateUpdate()
{
    for (int i = 0; i < MAX; i++)
    {
        bullet[i].LateUpdate();
    }
}

void Main::Render()
{
    xAxis.Render();
    yAxis.Render();
    player.Render();
    pet.Render();
    playerGauge.Render();
    for (int i = 0; i < MAX; i++)
    {
        bullet[i].Render();
    }
    firePos.Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"Game1");
    app.SetInstance(instance);
	app.InitWidthHeight(1200.0f, 600.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}