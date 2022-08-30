#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    player1 = new Character;
    player1->obj = new ObCircle;
    player1->Init();
    player1->scalar = 350.0f;
    player1->obj->collider = COLLIDER::CIRCLE;
    player1->type = Character::eType::p1;
    player1->obj->scale = Vector2(50.0f, 50.0f);
    player1->obj->color = Color(0.5f, 0.5f, 0.5f);
    player1->score = 0;

    player2 = new Character;
    player2->obj = new ObCircle;
    player2->Init();
    player2->scalar = 350.0f;
    player2->obj->collider = COLLIDER::CIRCLE;
    player2->type = Character::eType::p2;
    player2->obj->scale = Vector2(50.0f, 50.0f);
    player2->obj->color = Color(0.5f, 0.5f, 0.5f);
    player2->score = 0;

    ball = new Character;
    ball->obj = new ObCircle;
    ball->obj->scale = Vector2(30.0f, 30.0f);
    ball->obj->collider = COLLIDER::CIRCLE;
    ball->type = Character::eType::ball;

    Spawn();


    line = new Character;
    line->obj = new ObRect;
    line->obj->SetWorldPos(Vector2(0.0f, 0.0f));
    line->obj->scale = Vector2(400.0f, 1.0f);
    line->obj->collider = COLLIDER::RECT;
    line->obj->color = Color(0.0f, 0.0f, 0.0f);


    goalPost1 = new Character;
    goalPost1->obj = new ObRect;
    goalPost1->obj->SetWorldPos(Vector2(0.0f, 385.0f));
    goalPost1->obj->scale = Vector2(150.0f, 30.0f);
    goalPost1->obj->collider = COLLIDER::RECT;
    goalPost1->type = Character::eType::post;

    goalPost2 = new Character;
    goalPost2->obj = new ObRect;
    goalPost2->obj->SetWorldPos(Vector2(0.0f, -385.0f));
    goalPost2->obj->scale = Vector2(150.0f, 30.0f);
    goalPost2->obj->collider = COLLIDER::RECT;
    goalPost2->type = Character::eType::post;


    for (auto& wall : walls)
    {
        wall = new Character;
        wall->obj = new ObRect;
        wall->obj->isVisible = true;
        wall->obj->collider = COLLIDER::RECT;
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
    ball->Init();
    ball->scalar = 0.0f;
    ball->obj->SetWorldPos(Vector2(0.0f, 0.0f));
    player1->obj->SetWorldPos(Vector2(0.0f, 200.0f));
    player2->obj->SetWorldPos(Vector2(0.0f, -200.0f));
}

void Main::Release()
{
    delete player1;
    delete player2;
    delete ball;
    delete line;
    for (auto& wall : walls) delete wall;
}

void Main::Update()
{
    if (INPUT->KeyDown('R'))
    {
        Spawn();
    }
    player1->Update();
    player2->Update();
    ball->Update();
    line->Update();
    goalPost1->Update();
    goalPost2->Update();
    for (auto& wall : walls) wall->Update();
}

void Main::LateUpdate()
{
    ball->Update();   // 위치 먼저 갱신

    intersectPos = ball->obj->Intersect(player1->obj);
    if (intersectPos)
    {
        ball->Bounce(intersectPos, player1, Character::eType::p1);
    }

    intersectPos = ball->obj->Intersect(player2->obj);
    if (intersectPos)
    {
        ball->Bounce(intersectPos, player2, Character::eType::p2);
    }

    player1->LateUpdate();
    player2->LateUpdate();
    

    for (auto& wall : walls)
    {
        intersectPos = ball->obj->Intersect(wall->obj);
        if (intersectPos)
        {
            ball->Bounce(intersectPos, wall);
        }
    }


    if (ball->obj->Intersect(goalPost1->obj))
    {
        Spawn();
        player2->score++;
        goalPost1->state = Character::eState::hit;
    }
    if (ball->obj->Intersect(goalPost2->obj))
    {
        Spawn();
        player1->score++;
        goalPost2->state = Character::eState::hit;
    }
    ball->LateUpdate();


    player1->lastPos = player1->obj->GetWorldPos();
    player2->lastPos = player2->obj->GetWorldPos();
    ball->lastPos = ball->obj->GetWorldPos();


    ImGui::Begin("Timer");
    ImGui::Text("FPS : %d", TIMER->GetFramePerSecond());
    ImGui::Text("WorldTime : %f", TIMER->GetWorldTime());
    ImGui::Text("DeltaTime : %f", TIMER->GetDeltaTime());
    ImGui::End();

    ImGui::Begin("Score");
    ImGui::Text("p1 score : %d", player1->score);
    ImGui::Text("p2 score : %d", player2->score);
    ImGui::Text("Restart : R");
    ImGui::End();

    ImGui::SliderFloat("Ball Speed", &ball->scalar, 0.0f, 500.0f);
}

void Main::Render()
{
    line->Render();
    for (auto& wall : walls) wall->Render();
    goalPost1->Render();
    goalPost2->Render();
    player1->Render();
    player2->Render();
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