#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    xAxis.scale.x = 1280.0f;
    xAxis.color = Color(1.0f, 0.0f, 0.0f, 1.0f);
    xAxis.pivot = OFFSET_N;
    xAxis.Update();

    yAxis.scale.x = 720.0f;
    yAxis.color = Color(0.0f, 1.0f, 0.0f, 1.0f);
    yAxis.pivot = OFFSET_N;
    yAxis.rotation = DIV2PI;
    yAxis.Update();

    player.SetWorldPos(Vector2(0.0f, 0.0f));
    player.scale = Vector2(80.0f, 80.0f);
    player.rotation = 0.0f;
    player.isFilled = true;
    player.isAxis = true;
    player.color = Color(0.2f, 0.1f, 0.8f, 1.0f);
    player.pivot = OFFSET_N;

    firePos.SetLocalPos(Vector2(160.0f, 0.0f));
    firePos.scale = Vector2(80.0f, 80.0f);
    firePos.isAxis = false;
    firePos.SetParentRT(player);

    pet.SetLocalPos(Vector2(100.0f, 100.0f));
    pet.scale = Vector2(20.0f, 20.0f);
    pet.rotation = 0.0f;
    pet.isAxis = true;
    pet.isFilled = false;
    pet.color = Color(0.8f, 0.5f, 0.3f, 1.0f);
    pet.SetParentRT(player);

    playerShootGauge.SetLocalPos(Vector2(-50.0f, 60.0f));
    playerShootGauge.scale = Vector2(100.0f, 20.0f);
    playerShootGauge.rotation = 0.0f;
    playerShootGauge.isFilled = true;
    playerShootGauge.color = Color(0.2f, 0.1f, 0.6f, 1.0f);
    playerShootGauge.pivot = OFFSET_L;
    playerShootGauge.SetParentRT(player);

    playerShootGaugeFrame.SetLocalPos(Vector2(-50.0f, 60.0f));
    playerShootGaugeFrame.scale = Vector2(100.0f, 20.0f);
    playerShootGaugeFrame.isFilled = false;
    playerShootGaugeFrame.color = Color(0.5f, 0.5f, 0.9f, 1.0f);
    playerShootGaugeFrame.pivot = OFFSET_L;
    playerShootGaugeFrame.SetParentRT(player);

    float randScale = 0.0f;
    for (auto& star : stars)
    {
        star.SetWorldPos(Vector2(RANDOM->Float(-1000.0f, 1000.0f), RANDOM->Float(-1000.0f, 1000.0f)));
        randScale = RANDOM->Float(10.0f, 70.0f);
        star.scale = Vector2(randScale, randScale);
        star.rotation = RANDOM->Float(0.0f, 360.0f) * ToRadian;
        star.color = Color(RANDOM->Float(0.0f, 1.0f), RANDOM->Float(0.0f, 1.0f), RANDOM->Float(0.0f, 1.0f), 1.0f);
        star.isFilled = true;
    }
}

void Main::Release()
{
}

void Main::Update()
{
    // cout << "Mouse : " << INPUT->GetWorldMousePos().x << ","
    //     << INPUT->GetWorldMousePos().y << endl;

    Vector2 dir = INPUT->GetWorldMousePos() - player.GetWorldPos();
    player.rotation = Utility::DirToRadian(dir);

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


    lastPos = player.GetWorldPos();
    camLastPos = Vector2(CAM->position.x, CAM->position.y);
    Vector2 sub = lastPos - camLastPos;
    CAM->position += sub * 3.0f * DELTA;

    cout << "CAM Pos: (" << CAM->position.x << ',' << CAM->position.y << ")\n";


    if (INPUT->KeyPress('W'))
    {
        // player.MoveWorldPos(player.GetUp() * 400.0f * DELTA);
        player.MoveWorldPos(UP * 400.0f * DELTA);
    }
    else if (INPUT->KeyPress('S'))
    {
        // player.MoveWorldPos(-player.GetUp() * 400.0f * DELTA);
        player.MoveWorldPos(DOWN * 400.0f * DELTA);
    }

    if (INPUT->KeyPress('A'))
    {
        // player.MoveWorldPos(-player.GetRight() * 400.0f * DELTA);
        player.MoveWorldPos(LEFT * 400.0f * DELTA);
    }
    else if (INPUT->KeyPress('D'))
    {
        // player.MoveWorldPos(player.GetRight() * 400.0f * DELTA);
        player.MoveWorldPos(RIGHT * 400.0f * DELTA);
    }



    if (INPUT->KeyDown(VK_LBUTTON))
    {
        playerShootGauge.scale.x = 0.0f;
    }

    if (INPUT->KeyPress(VK_LBUTTON))
    {
        playerShootGauge.scale.x += 100.0f * DELTA;

        if (playerShootGauge.scale.x > 100.0f)
        {
            playerShootGauge.scale.x = 0.0f;
        }
    }

    if (INPUT->KeyUp(VK_LBUTTON))
    {
        for (int i = 0; i < MAX; i++)
        {
            if (bullets[i].Shoot(player, playerShootGauge.scale.x, firePos.GetWorldPos()))
            {
                break;
            }
        }
    }

    pet.rotation2 += 60.0f * ToRadian * DELTA;

    player.Update();
    pet.Update();

    for (int i = 0; i < MAX; i++)
    {
        bullets[i].Update(player);
    }
    playerShootGauge.Update();
    playerShootGaugeFrame.Update();
    firePos.Update();

    for (auto& star : stars) star.Update();
}

void Main::LateUpdate()
{
    for (int i = 0; i < MAX; i++)
    {
        bullets[i].LateUpdate();
    }
}

void Main::Render()
{
    for (auto& star : stars) star.Render();
    xAxis.Render();
    yAxis.Render();
    player.Render();
    pet.Render();
    playerShootGauge.Render();
    playerShootGaugeFrame.Render();
    for (int i = 0; i < MAX; i++)
    {
        bullets[i].Render();
    }
    firePos.Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"À¯ÀçÁØ Game1");
    app.SetInstance(instance);
    app.InitWidthHeight(1280.0f, 720.0f);
    Main* main = new Main();
    int wParam = (int)WIN->Run(main);
    WIN->DeleteSingleton();
    SafeDelete(main);
    return wParam;
}