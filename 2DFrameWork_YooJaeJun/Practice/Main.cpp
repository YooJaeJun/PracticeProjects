#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    x = 2560.0f;
    y = 1440.0f;

    Color basicColor = Color(0.9f, 0.5f, 0.3f, 1.0f);

    bg = new ObImage(L"Background_Ruin.jpg");
    bg->scale = Vector2(x, y);
    bg->Update();

    xAxis.scale.x = 4000.0f;
    xAxis.color = Color(1.0f, 0.0f, 0.0f, 1.0f);
    xAxis.pivot = OFFSET_N;
    xAxis.Update();

    yAxis.scale.x = 4000.0f;
    yAxis.color = Color(0.0f, 1.0f, 0.0f, 1.0f);
    yAxis.pivot = OFFSET_N;
    yAxis.rotation = DIV2PI;
    yAxis.Update();

    player.SetWorldPos(Vector2(0.0f, 0.0f));
    player.scale = Vector2(80.0f, 80.0f);
    player.rotation = 0.0f;
    player.isFilled = true;
    player.isAxis = true;
    player.color = basicColor;
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
    pet.color = basicColor;
    pet.SetParentRT(player);

    playerShootGauge.SetLocalPos(Vector2(-50.0f, 60.0f));
    playerShootGauge.scale = Vector2(100.0f, 20.0f);
    playerShootGauge.rotation = 0.0f;
    playerShootGauge.isFilled = true;
    playerShootGauge.color = basicColor;
    playerShootGauge.pivot = OFFSET_L;
    playerShootGauge.SetParentRT(player);

    playerShootGaugeFrame.SetLocalPos(Vector2(-50.0f, 60.0f));
    playerShootGaugeFrame.scale = Vector2(100.0f, 20.0f);
    playerShootGaugeFrame.isFilled = false;
    playerShootGaugeFrame.color = basicColor;
    playerShootGaugeFrame.pivot = OFFSET_L;
    playerShootGaugeFrame.SetParentRT(player);

    /*
    float randScale = 0.0f;
    for (auto& star : stars)
    {
        star = new ObStar();
        star->SetWorldPos(Vector2(RANDOM->Float(-1000.0f, 1000.0f), RANDOM->Float(-1000.0f, 1000.0f)));
        star->scale.x = star->scale.y = RANDOM->Float(10.0f, 80.0f);
        star->color = Color(RANDOM->Float(), RANDOM->Float(), RANDOM->Float(), 1.0f);
        star->rotation = RANDOM->Float(0.0f, 360.0f) * ToRadian;
        star->isFilled = true;

        // star->space = SPACE::SCREEN;
    }
    */
}

void Main::Release()
{
    for (auto& star : stars)
    {
        SafeDelete(star);
    }
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


    if (INPUT->KeyPress('W'))
    {
        // player.MoveWorldPos(player.GetUp() * 400.0f * DELTA);
        player.MoveWorldPos(UP * 600.0f * DELTA);
        // CAM->position += UP * 300.0f * DELTA;
    }
    else if (INPUT->KeyPress('S'))
    {
        // player.MoveWorldPos(-player.GetUp() * 400.0f * DELTA);
        player.MoveWorldPos(DOWN * 600.0f * DELTA);
        // CAM->position += DOWN * 300.0f * DELTA;
    }

    if (INPUT->KeyPress('A'))
    {
        // player.MoveWorldPos(-player.GetRight() * 400.0f * DELTA);
        player.MoveWorldPos(LEFT * 600.0f * DELTA);
        // CAM->position += LEFT * 300.0f * DELTA;
    }
    else if (INPUT->KeyPress('D'))
    {
        // player.MoveWorldPos(player.GetRight() * 400.0f * DELTA);
        player.MoveWorldPos(RIGHT * 600.0f * DELTA);
        // CAM->position += RIGHT * 300.0f * DELTA;
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

    for (int i = 0; i < MAX; i++) bullets[i].Update(player);
    playerShootGauge.Update();
    playerShootGaugeFrame.Update();
    firePos.Update();

    // for (auto& star : stars) star->Update();
}

void Main::LateUpdate()
{

    float scaleX = bg->scale.x / 2 - 50.0f;
    float scaleY = bg->scale.y / 2 - 25.0f;
    player.SetWorldPosX(Utility::Saturate(player.GetWorldPos().x, -scaleX, scaleX));
    player.SetWorldPosY(Utility::Saturate(player.GetWorldPos().y, -scaleY, scaleY));
    
    // CAM->position.x = Utility::Saturate(CAM->position.x, -scaleX + app.GetHalfWidth(), scaleX - app.GetHalfWidth());
    // CAM->position.y = Utility::Saturate(CAM->position.y, -scaleY + app.GetHalfHeight(), scaleY - app.GetHalfHeight());
    CAM->position.x = (x - app.GetWidth()) * player.GetWorldPos().x / x;
    CAM->position.y = (y - app.GetHeight()) * player.GetWorldPos().y / y;

    
    // Vector2 velocity = player.GetWorldPos() - CAM->position;
    // CAM->position += velocity * 3.0f * DELTA;

    cout << "CAM Pos: (" << CAM->position.x << ',' << CAM->position.y << ")\n";


    // player.rotation = Utility::Saturate(player.rotation, 0.0f, PI);
    // player.Update();



    for (auto& bullet : bullets) bullet.LateUpdate();

    ImGui::SliderAngle("Angle", &player.rotation);
    float playerX = player.GetWorldPos().x;
    float playerY = player.GetWorldPos().y;
    ImGui::SliderFloat("Player X", &playerX, -x / 2, x / 2);
    ImGui::SliderFloat("Player Y", &playerY, -y / 2, y / 2);
    ImGui::SliderFloat("Camera X", &CAM->position.x, -x / 2, x / 2);
    ImGui::SliderFloat("Camera Y", &CAM->position.y, -y / 2, y / 2);
}

void Main::Render()
{
    bg->Render();
    // for (auto& star : stars) star->Render();
    xAxis.Render();
    yAxis.Render();
    player.Render();
    pet.Render();
    playerShootGauge.Render();
    playerShootGaugeFrame.Render();
    for (int i = 0; i < MAX; i++) bullets[i].Render();
    firePos.Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"유재준 Game1");
    app.SetInstance(instance);
    app.InitWidthHeight(1280.0f, 720.0f);
    Main* main = new Main();
    int wParam = (int)WIN->Run(main);
    WIN->DeleteSingleton();     // 창이 없어지고 난 후 
    SafeDelete(main);           // 메모리 해제
    return wParam;
}