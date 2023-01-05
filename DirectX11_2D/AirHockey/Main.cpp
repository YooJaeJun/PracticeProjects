#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    for (auto& player : players)
    {
        player = new Character;
        player->obj = new ObCircle;
        player->Init();
        player->scalar = 350.0f;
        player->obj->collider = Collider::circle;
        player->obj->scale = Vector2(50.0f, 50.0f);
        player->score = 0;
    }
    players[0]->type = Character::Type::p1;
    players[0]->obj->color = colorRed;
    players[1]->type = Character::Type::p2;
    players[1]->obj->color = colorBlue;


    ball = new Character;
    ball->obj = new ObCircle;
    ball->obj->scale = Vector2(30.0f, 30.0f);
    ball->obj->collider = Collider::circle;
    ball->type = Character::Type::ball;

    Spawn();


    line = new Character;
    line->obj = new ObRect;
    line->obj->SetWorldPos(Vector2(0.0f, 0.0f));
    line->obj->scale = Vector2(400.0f, 1.0f);
    line->obj->collider = Collider::rect;
    line->obj->color = Color(0.0f, 0.0f, 0.0f);


    for (auto& goalPost : goalPosts)
    {
        goalPost = new Character;
        goalPost->obj = new ObRect;
        goalPost->obj->scale = Vector2(150.0f, 30.0f);
        goalPost->obj->collider = Collider::rect;
        goalPost->type = Character::Type::post;
    }
    goalPosts[0]->obj->SetWorldPos(Vector2(0.0f, 385.0f));
    goalPosts[0]->obj->color = colorRed;
    goalPosts[0]->originColor = colorRed;
    goalPosts[1]->obj->SetWorldPos(Vector2(0.0f, -385.0f));
    goalPosts[1]->obj->color = colorBlue;
    goalPosts[1]->originColor = colorBlue;


    for (auto& wall : walls)
    {
        wall = new Character;
        wall->obj = new ObRect;
        wall->obj->isVisible = true;
        wall->obj->collider = Collider::rect;
        wall->obj->color = Color(0.0f, 0.0f, 0.0f);
    }
    walls[0]->obj->SetWorldPos(Vector2(0.0f, -400.0f));
    walls[1]->obj->SetWorldPos(Vector2(0.0f, 400.0f));
    walls[2]->obj->SetWorldPos(Vector2(200.0f, 0.0f));
    walls[3]->obj->SetWorldPos(Vector2(-200.0f, 0.0f));
    walls[0]->obj->scale = Vector2(400.0f, 2.0f);
    walls[1]->obj->scale = Vector2(400.0f, 2.0f);
    walls[2]->obj->scale = Vector2(2.0f, 800.0f);
    walls[3]->obj->scale = Vector2(2.0f, 800.0f);
}

void Main::Spawn()
{
    players[0]->obj->SetWorldPos(Vector2(0.0f, -200.0f));
    players[1]->obj->SetWorldPos(Vector2(0.0f, 200.0f));
    ball->Init();
    ball->scalar = 0.0f;
    ball->obj->SetWorldPos(Vector2(0.0f, 0.0f));
}

void Main::Release()
{
    for (auto& player : players) SafeDelete(player);
    SafeDelete(ball);
    SafeDelete(line);
    for (auto& goalPost : goalPosts) SafeDelete(goalPost);
    for (auto& wall : walls) SafeDelete(wall);
}

void Main::Update()
{
    if (INPUT->KeyDown('R'))
    {
        Spawn();
    }

    for (auto& player : players) player->Update();  // 위치 먼저 갱신

    float radius = players[0]->obj->scale.x / 2;
    float plx = Utility::Saturate(players[0]->obj->GetWorldPos().x, -200.0f + radius, 200.0f - radius);
    float ply = Utility::Saturate(players[0]->obj->GetWorldPos().y, -400.0f + radius, -radius);
    players[0]->obj->SetWorldPosX(plx);
    players[0]->obj->SetWorldPosY(ply);

    plx = Utility::Saturate(players[1]->obj->GetWorldPos().x, -200.0f + radius, 200.0f - radius);
    ply = Utility::Saturate(players[1]->obj->GetWorldPos().y, radius, 400.0f - radius);
    players[1]->obj->SetWorldPosX(plx);
    players[1]->obj->SetWorldPosY(ply);

    for (auto& player : players) player->Update();

    ball->Update();
    line->Update();
    for (auto& goalPost : goalPosts) goalPost->Update();
    for (auto& wall : walls) wall->Update();
}

void Main::LateUpdate()
{
    ball->Update();   // 위치 먼저 갱신

    intersectPos = ball->obj->Intersect(players[0]->obj);
    if (intersectPos)
    {
        ball->Bounce(intersectPos, players[0], Character::Type::p1);
    }

    ball->Update();   // 위치 먼저 갱신

    intersectPos = ball->obj->Intersect(players[1]->obj);
    if (intersectPos)
    {
        ball->Bounce(intersectPos, players[1], Character::Type::p2);
    }

    for (auto& player : players) player->LateUpdate();
    

    for (auto& wall : walls)
    {
        intersectPos = ball->obj->Intersect(wall->obj);
        if (intersectPos)
        {
            ball->Bounce(intersectPos, wall);
        }
    }


    if (ball->obj->Intersect(goalPosts[0]->obj))
    {
        Spawn();
        players[1]->score++;
        goalPosts[0]->state = Character::State::hit;
    }
    if (ball->obj->Intersect(goalPosts[1]->obj))
    {
        Spawn();
        players[0]->score++;
        goalPosts[1]->state = Character::State::hit;
    }
    ball->LateUpdate();


    players[0]->lastPos = players[0]->obj->GetWorldPos();
    players[1]->lastPos = players[1]->obj->GetWorldPos();
    ball->lastPos = ball->obj->GetWorldPos();


    ImGui::Begin("Timer");
    ImGui::Text("FPS : %d", TIMER->GetFramePerSecond());
    ImGui::Text("WorldTime : %f", TIMER->GetWorldTime());
    ImGui::Text("DeltaTime : %f", TIMER->GetDeltaTime());
    ImGui::End();

    ImGui::Begin("Score");
    ImGui::Text("Blue score : %d", players[0]->score);
    ImGui::Text("Red score : %d", players[1]->score);
    ImGui::Text("Restart : R");
    ImGui::End();

    ImGui::SliderFloat("Ball Speed", &ball->scalar, 0.0f, 500.0f);
}

void Main::Render()
{
    line->Render();
    for (auto& wall : walls) wall->Render();
    for (auto& goalPost : goalPosts) goalPost->Render();
    for (auto& player : players) player->Render();
    ball->Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"유재준 에어하키");
    app.SetInstance(instance);
    app.InitWidthHeight(400.0f, 800.0f);
    Main* main = new Main();
    int wParam = (int)WIN->Run(main);
    WIN->DeleteSingleton();
    SafeDelete(main);
    return wParam;
}