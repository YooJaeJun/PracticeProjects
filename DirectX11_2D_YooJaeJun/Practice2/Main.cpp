#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    trailTimer = 0.3f;
    trailNum = 10;
    trailDuration = trailTimer * (float)trailNum;
    trailNumBefore = trailNum;

    player = new ObRect;
    player->scale = Vector2(100.0f, 100.0f);
    player->SetWorldPos(Vector2(0.0f, 0.0f));
    player->collider = COLLIDER::RECT;
}

void Main::Release()
{
    SafeDelete(player);
}

void Main::Update()
{
    if (trailNumBefore != trailNum)
    {
        while (trails.empty() == false) trails.pop_back();
        trailSpawnTimer = 0.0f;
        trailDestroyStartTimer = 0.0f;
        trailNumBefore = trailNum;
    }

    ImGui::SliderFloat("trailTimer", &trailTimer, 0.0f, 2.0f);
    ImGui::Text("trailDuration: %f", trailDuration);
    ImGui::SliderInt("trailNum", &trailNum, 1, 30);
    ImGui::Text("Tracer: R");
    for (auto& trail : trails) trail.Update();



    if (INPUT->KeyDown('R'))
    {
        while (trails.size() > 1) trails.pop_back();
        player->SetWorldPos(trails[0].GetWorldPos());
        player->rotation = trails[0].rotation;
        player->Update();
        trailSpawnTimer = 0.0f;
        trailDestroyStartTimer = 0.0f;
    }

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

    player->Update();

    if (trailNum != 0) trailDuration = trailTimer * (float)trailNum;



    trailSpawnTimer += 1.0f * DELTA;
    if (trailSpawnTimer >= trailTimer)
    {
        trailSpawnTimer = 0.0f;
        ObRect trail;
        trail.SetWorldPos(player->GetWorldPos());
        trail.rotation = player->rotation;
        trail.scale = player->scale;
        trails.push_back(trail);
    }
    for (auto& trail : trails) trail.Update();



    trailDestroyStartTimer += 1.0f * DELTA;
    if (trailDestroyStartTimer >= trailDuration)
    {
        trailDestroyTimer += 1.0f * DELTA;
        if (trailDestroyTimer >= trailTimer)
        {
            trailDestroyTimer = 0.0f;
            trails.pop_front();
        }
    }
    for (auto& trail : trails) trail.Update();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
    for (auto& trail : trails) trail.Render();
    player->Render();
}

void Main::ResizeScreen()
{
}


void Main::SetTrailNum(const int size)
{
    trails.resize(size);
    for (auto& trail : trails)
    {
        trail.scale = Vector2(100.0f, 100.0f);
        trail.isVisible = false;
    }
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