#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    player = new ObRect;
    player->scale = Vector2(100.0f, 100.0f);

    trailTimer = 0.3f;
    trailNum = 10;
    trailSpawnTimer = 0.0f;

    trails.resize(trailNum);

    for (auto& trail : trails)
    {
        trail = new ObRect;
        trail->isVisible = false;
        trail->scale = Vector2(100.0f, 100.0f);
    }
}

void Main::Release()
{
    SafeDelete(player);
    for (auto& trail : trails) SafeDelete(trail);
}

void Main::Update()
{
    ImGui::SliderFloat("trailTimer", &trailTimer, 0.0f, 2.0f);
    ImGui::Text("trailDuration: %f", trailDuration);
    ImGui::Text("Tracer: R");
    trailDuration = trailTimer * (float)trailNum;


    if (ImGui::SliderInt("trailNum", &trailNum, 1, 30))
    {
        for (auto& trail : trails) SafeDelete(trail);

        trails.resize(trailNum);

        for (auto& trail : trails)
        {
            trail = new ObRect;
            trail->isVisible = false;
            trail->scale = Vector2(100.0f, 100.0f);
            trailSpawnTimer = 0.0f;
        }
    }

    for (auto& trail : trails) trail->Update();


    if (INPUT->KeyPress(VK_LEFT))
    {
        player->rotation += 200.0f * ToRadian * DELTA;
    }
    else if (INPUT->KeyPress(VK_RIGHT))
    {
        player->rotation -= 200.0f * ToRadian * DELTA;
    }

    if (INPUT->KeyPress(VK_UP))
    {
        player->MoveWorldPos(player->GetRight() * 250.0f * DELTA);
    }
    else if (INPUT->KeyPress(VK_DOWN))
    {
        player->MoveWorldPos(-player->GetRight() * 250.0f * DELTA);
    }

    if (INPUT->KeyDown('R'))
    {
        player->SetWorldPos(trails[0]->GetWorldPos());
        player->rotation = trails[0]->rotation;
        player->Update();
        trailSpawnTimer = 0.0f;
        for (auto& trail : trails)
        {
            trail->isVisible = false;
            trail->SetWorldPos(player->GetWorldPos());
            trail->rotation = player->rotation;
        }
    }

    if (TIMER->GetTick(trailSpawnTimer, trailTimer))
    {
        trails[0]->isVisible = true;
        trails[0]->SetWorldPos(player->GetWorldPos());
        trails[0]->rotation = player->rotation;
        trails.push_back(trails[0]);
        trails.pop_front();
    }

    player->Update();

    for (auto& trail : trails) trail->Update();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
    for (auto& trail : trails) trail->Render();
    player->Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"유재준 잔상");
    app.SetInstance(instance);
    app.InitWidthHeight(1280.0f, 720.0f);
    Main* main = new Main();
    int wParam = (int)WIN->Run(main);
    WIN->DeleteSingleton();     // 창이 없어지고 난 후 
    SafeDelete(main);           // 메모리 해제
    return wParam;
}