#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    restartKey = 'R';
    gameState = eGameState::process;
    for (auto& endingLine : endingLines)
    {
        endingLine = new ObLine;
        endingLine->scale.x = 100.0f;
        endingLine->color = Color(1.0f, 1.0f, 1.0f);
        endingLine->isVisible = false;
    }
    // 끗
    endingLines[0]->SetWorldPos(Vector2(-100.0f, 120.0f));
    endingLines[1]->SetWorldPos(Vector2(0.0f, 120.0f));
    endingLines[1]->rotation = -90.0f * ToRadian;
    endingLines[2]->SetWorldPos(Vector2(0.0f, 120.0f));
    endingLines[3]->SetWorldPos(Vector2(100.0f, 120.0f));
    endingLines[3]->rotation = -90.0f * ToRadian;

    endingLines[4]->SetWorldPos(Vector2(-120.0f, 0.0f));
    endingLines[4]->scale.x = 240.0f;

    endingLines[5]->SetWorldPos(Vector2(0.0f, -20.0f));
    endingLines[5]->rotation = -120.0f * ToRadian;
    endingLines[6]->SetWorldPos(Vector2(0.0f, -20.0f));
    endingLines[6]->rotation = -60.0f * ToRadian;


    ball = new Ball;
    ball->obj = new ObCircle();
    ball->obj->SetWorldPos(Vector2(0.0f, -270.0f));
    ball->obj->scale = Vector2(20.0f, 20.0f);
    ball->obj->rotation = 90.0f * ToRadian;
    ball->obj->color = Color(0.0f, 0.9f, 0.7f);
    ball->obj->isVisible = true;
    ball->obj->collider = COLLIDER::CIRCLE;
    ball->dir = ball->obj->GetUp();
    ball->scalar = 500.0f;


    bar = new Bar;
    bar->Init();


    for (auto& wall : walls)
    {
        wall = new NonMover;
        wall->obj = new ObRect();
        wall->obj->isVisible = true;
        wall->obj->collider = COLLIDER::RECT;
        wall->obj->color = Color(0.0f, 0.0f, 0.0f);
    }
    walls[0]->obj->SetWorldPos(Vector2(0.0f, -480.0f));
    walls[1]->obj->SetWorldPos(Vector2(0.0f, 480.0f));
    walls[2]->obj->SetWorldPos(Vector2(300.0f, 0.0f));
    walls[3]->obj->SetWorldPos(Vector2(-300.0f, 0.0f));
    walls[0]->obj->scale = Vector2(600.0f, 10.0f);
    walls[1]->obj->scale = Vector2(600.0f, 10.0f);
    walls[2]->obj->scale = Vector2(10.0f, 960.0f);
    walls[3]->obj->scale = Vector2(10.0f, 960.0f);


    int idx = 0;
    for (int r = 0; r < brickRow; r++)
    {
        for (int c = 0; c < brickCol; c++)
        {
            bricks[idx] = new Brick;
            bricks[idx]->obj = new ObRect();
            bricks[idx]->obj->scale = Vector2(80.0f, 40.0f);
            bricks[idx]->obj->isVisible = true;
            bricks[idx]->obj->collider = COLLIDER::RECT;
            bricks[idx]->obj->SetWorldPos(Vector2(
                -200.0f + 80.0f * c,
                300.0f - 40.0f * r));
            bricks[idx]->hitTime = 0.0f;
            bricks[idx]->state = Unit::eState::idle;


            if (r == 0)
            {
                bricks[idx]->obj->color = Color(0.7f, 0.9f, 0.3f);
                bricks[idx]->life = 3;
            }
            else if (r & 1)
            {
                bricks[idx]->obj->color = Color(0.9f, 0.7f, 0.3f);
                bricks[idx]->life = 2;
            }
            else
            {
                bricks[idx]->obj->color = Color(0.9f, 0.4f, 0.3f);
                bricks[idx]->life = 1;
            }
            idx++;
        }
    }

    bulletBrick = new Item;
    bulletBrick->obj = new ObRect;
    bulletBrick->obj->SetWorldPos(Vector2(180.0f, -50.0f));
    bulletBrick->obj->scale = Vector2(100.0f, 50.0f);
    bulletBrick->obj->color = Color(0.2f, 0.7f, 0.9f);
    bulletBrick->obj->isVisible = true;
    bulletBrick->obj->collider = COLLIDER::RECT;
    bulletBrick->trigger = false;
    bulletBrick->fireTime = 0.0f;

    for (auto& bullet : bullets)
    {
        bullet = new Ball;
        bullet->obj = new ObCircle;
        bullet->obj->SetWorldPos(Vector2(3000.0f, 3000.0f));
        bullet->obj->scale = Vector2(20.0f, 20.0f);
        bullet->obj->color = Color(0.2f, 0.8f, 0.8f);
        bullet->obj->isVisible = false;
        bullet->obj->collider = COLLIDER::CIRCLE;
        bullet->dir = UP;
        bullet->scalar = 500.0f;
    }

    starStormBrick = new Item;
    starStormBrick->obj = new ObRect;
    starStormBrick->obj->SetWorldPos(Vector2(-180.0f, -50.0f));
    starStormBrick->obj->scale = Vector2(100.0f, 50.0f);
    starStormBrick->obj->color = Color(0.8f, 0.8f, 0.8f);
    starStormBrick->obj->isVisible = true;
    starStormBrick->obj->collider = COLLIDER::RECT;
    starStormBrick->trigger = false;
    starStormBrick->fireTime = 0.0f;
    starStormBrick->end = false;

    idx = 0;
    for (auto& starStorm : starStorms)
    {
        starStorm = new Ball;
        starStorm->obj = new ObStar;
        starStorm->obj->SetWorldPos(Vector2(3000.0f, 3000.0f));
        starStorm->obj->scale = Vector2(20.0f, 20.0f);
        starStorm->obj->isVisible = false;
        starStorm->obj->collider = COLLIDER::CIRCLE;
        starStorm->SpawnStorm();
        idx++;
    }
}

void Main::Release()
{
    for (auto& endingLine : endingLines) delete endingLine;
    delete ball;
    delete bar;
    for (auto& wall : walls) delete wall;
    for (auto& brick : bricks) delete brick;
    delete bulletBrick;
    delete starStormBrick;
    for (auto& bullet : bullets) delete bullet;
    for (auto& starStorm : starStorms) delete starStorm;
}

void Main::Update()
{
    if (INPUT->KeyDown(restartKey)) Init();
    if (gameState == eGameState::end)
    {
        for (auto& endingLine : endingLines)
        {
            endingLine->isVisible = true;
            endingLine->Update();
        }
        return;
    }

    ball->Move();
    ball->Update();


    if (INPUT->KeyPress(VK_LEFT))
    {
        bar->SetDir(-bar->obj->GetRight());
        bar->Move();
    }
    else if (INPUT->KeyPress(VK_RIGHT))
    {
        bar->SetDir(bar->obj->GetRight());
        bar->Move();
    }
    bar->Update();


    for (auto& wall : walls) wall->Update();


    int idx = 0;
    for (int r = 0; r < brickRow; r++)
    {
        for (int c = 0; c < brickCol; c++)
        {
            bricks[idx]->HitEffect();
            bricks[idx]->Update();
            idx++;
        }
    }


    // 아이템 뷸렛 발사주기 세팅
    if (bulletBrick->trigger)
    {
        bulletBrick->fireTime += 100.0f * DELTA;
        if (bulletBrick->fireTime > 80.0f)
        {
            for (auto& bullet : bullets)
            {
                if (bullet->fired == false)
                {
                    bullet->Ready(bar->obj->GetWorldPos());
                    bulletBrick->fireTime = 0.0f;
                    break;
                }
            }
        }
        // 발사
        for (auto& bullet : bullets)
        {
            if (bullet->fired)
            {
                bullet->Move();
                bullet->Update();
            }
        }
    }
    bulletBrick->Update();

    starStormBrick->colorTime += 100.0f * DELTA;
    if (starStormBrick->colorTime > 30.0f)
    {
        starStormBrick->obj->color = Color(RANDOM->Float(), RANDOM->Float(), RANDOM->Float(), 1.0f);
        starStormBrick->colorTime = 0.0f;
    }


    // 아이템 스톰 발사주기 세팅
    if (starStormBrick->trigger)
    {
        // 준비
        for (auto& starStorm : starStorms)
        {
            starStorm->Ready();
        }
        starStormBrick->fireTime += 100.0f * DELTA;
        if (starStormBrick->fireTime > 400.0f)
        {
            starStormBrick->fireTime = 0.0f;
            starStormBrick->trigger = false;
            starStormBrick->end = true;    // 후에 벽과 충돌하면 제거
        }
    }
    // 발사
    for (auto& starStorm : starStorms)
    {
        if (starStorm->fired)
        {
            starStorm->Move();
            starStorm->Update();
        }
    }
    starStormBrick->Update();
}


void Main::LateUpdate()
{
    if (gameState == eGameState::end) return;
    Vector2 mousePos = INPUT->GetWorldMousePos();


    // 먼저 위치 갱신
    // ball->Update(); 
    
    interPos = ball->obj->Intersect(bar->obj);
    if (interPos)
    {
        ball->Bounce(interPos, true, bar->dir);
    }
    bar->LateUpdate();


    endFlag = true; // 벽돌 다 부숴지면 끝
    for (auto& brick : bricks)
    {
        interPos = ball->obj->Intersect(brick->obj);
        if (interPos)
        {
            ball->Bounce(interPos);
            ball->scalar += 15.0f;
            brick->Hit();
        }

        // 벽돌-뷸렛 충돌
        for (auto& bullet : bullets)
        {
            interPos = bullet->obj->Intersect(brick->obj);
            if (interPos)
            {
                brick->Hit();
                bullet->Destroy();
            }
        }
        // 벽돌-스톰 충돌
        for (auto& starStorm : starStorms)
        {
            interPos = starStorm->obj->Intersect(brick->obj);
            if (interPos)
            {
                brick->Hit();
                if (starStormBrick->end == false)
                {
                    starStorm->SpawnStorm();
                }
                else
                {
                    starStorm->Destroy();
                }
            }
        }

        if (brick->life > 0)
        {
            endFlag = false;
        }

        brick->LateUpdate();
    }

    if (endFlag)
    {
        gameState = eGameState::end;
    }


    for (auto& wall : walls)
    {
        interPos = ball->obj->Intersect(wall->obj);
        if (interPos)
        {
            ball->Bounce(interPos);
        }

        interPos = bar->obj->Intersect(wall->obj);
        if (interPos)
        {
            // 가두기
            bar->Imprison(wall->obj);
        }

        // 벽-뷸렛 충돌
        for (auto& bullet : bullets)
        {
            interPos = bullet->obj->Intersect(wall->obj);
            if (interPos)
            {
                bullet->Destroy(Vector2(3000.0f, 3000.0f));
            }
        }
        // 벽-스톰 충돌
        for (auto& starStorm : starStorms)
        {
            interPos = starStorm->obj->Intersect(wall->obj);
            if (interPos)
            {
                if (starStormBrick->end == false)
                {
                    starStorm->SpawnStorm();
                }
                else
                {
                    starStorm->Destroy();
                }
            }
        }
        wall->LateUpdate();
    }


    // 아이템 뷸렛 트리거
    interPos = ball->obj->Intersect(bulletBrick->obj);
    if (interPos)
    {
        ball->Bounce(interPos);
        bulletBrick->Destroy(Vector2(3000.0f, 3000.0f));
        bulletBrick->trigger = true;
    }
    bulletBrick->LateUpdate();

    // 아이템 스톰 트리거
    interPos = ball->obj->Intersect(starStormBrick->obj);
    if (interPos)
    {
        ball->Bounce(interPos);
        starStormBrick->Destroy(Vector2(3000.0f, 3000.0f));
        starStormBrick->trigger = true;     
    }
    starStormBrick->LateUpdate();

    ball->LastPosUpdate();
}

void Main::Render()
{
    ImGui::SliderFloat("Ball Last Pos X", &ball->lastPos.x, -app.GetHalfWidth(), app.GetHalfWidth());
    ImGui::SliderFloat("Ball Last Pos Y", &ball->lastPos.y, -app.GetHalfHeight(), app.GetHalfHeight());
    ImGui::SliderFloat("Ball Dir X", &ball->dir.x, -1.0f, 1.0f);
    ImGui::SliderFloat("Ball Dir Y", &ball->dir.y, -1.0f, 1.0f);
    ImGui::SliderFloat("Ball Scalar", &ball->scalar, 600.0f, 1200.0f);
    ImGui::Text("Restart: %c", restartKey);

    if (gameState == eGameState::end)
    {
        for (auto& endingLine : endingLines) endingLine->Render();
        return;
    }
    ball->Render();
    bar->Render();
    for (auto& wall : walls) wall->Render();
    for (auto& brick : bricks) brick->Render();
    bulletBrick->Render();
    starStormBrick->Render();
    for (auto& bullet : bullets) bullet->Render();
    for (auto& starStorm : starStorms) starStorm->Render();
}

void Main::ResizeScreen()
{
}


int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"유재준 Alkaloid");
    app.SetInstance(instance);
    app.InitWidthHeight(600.0f, 960.0f);
    app.background = Color(0.1f, 0.1f, 0.1f, 1.0f);
    Main* main = new Main();
    int wParam = (int)WIN->Run(main);
    WIN->DeleteSingleton();
    SafeDelete(main);
    return wParam;
}