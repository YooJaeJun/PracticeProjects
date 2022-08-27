#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    restartKey = 'R';
    gameState = eGameState::process;
    for (auto& line : endingLines)
    {
        line = new ObLine;
        line->scale.x = 100.0f;
        line->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
    }
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

    ball = new ObCircle();
    ball->SetWorldPos(Vector2(0.0f, -270.0f));
    ball->scale = Vector2(20.0f, 20.0f);
    ball->rotation = 90.0f * ToRadian;
    ball->color = Color(0.0f, 0.9f, 0.7f, 1.0f);
    ball->collider = COLLIDER::CIRCLE;
    ballFireDir = ball->GetUp();
    ballScalar = 600.0f;

    bar = new ObRect();
    bar->SetWorldPos(Vector2(0.0f, -300.0f));
    bar->scale = Vector2(100.0f, 15.0f);
    bar->color = Color(0.2f, 0.9f, 0.7f, 1.0f);
    bar->collider = COLLIDER::RECT;
    barScalar = 500.0f;
    barDir = Vector2(0.0f, 0.0f);

    int idx = 0;
    for (int r = 0; r < brickRow; r++)
    {
        for (int c = 0; c < brickCol; c++)
        {
            bricks[idx] = new ObRect();
            bricks[idx]->scale = Vector2(80.0f, 40.0f);
            bricks[idx]->collider = COLLIDER::RECT;
            brickHitTime[idx] = 0.0f;
            brickState[idx] = eState::idle;

            bricks[idx]->SetWorldPos(Vector2(
                -200.0f + 80.0f * c,
                300.0f - 40.0f * r));

            if (r == 0)
            {
                bricks[idx]->color = Color(0.7f, 0.9f, 0.3f, 1.0f);
                brickLife[idx] = 3;
            }
            else if (r == 1 or r == 3)
            {
                bricks[idx]->color = Color(0.9f, 0.7f, 0.3f, 1.0f);
                brickLife[idx] = 2;
            }
            else
            {
                bricks[idx]->color = Color(0.9f, 0.4f, 0.3f, 1.0f);
                brickLife[idx] = 1;
            }
            idx++;
        }
    }

    for (auto& wall : walls)
    {
        wall = new ObRect();
        bar->collider = COLLIDER::RECT;
    }
    walls[0]->SetWorldPos(Vector2(0.0f, -480.0f));
    walls[1]->SetWorldPos(Vector2(0.0f, 480.0f));
    walls[2]->SetWorldPos(Vector2(300.0f, 0.0f));
    walls[3]->SetWorldPos(Vector2(-300.0f, 0.0f));
    walls[0]->scale = Vector2(600.0f, 10.0f);
    walls[1]->scale = Vector2(600.0f, 10.0f);
    walls[2]->scale = Vector2(10.0f, 960.0f);
    walls[3]->scale = Vector2(10.0f, 960.0f);
    walls[0]->color = Color(0.0f, 0.0f, 0.0f, 1.0f);
    walls[1]->color = Color(0.0f, 0.0f, 0.0f, 1.0f);
    walls[2]->color = Color(0.0f, 0.0f, 0.0f, 1.0f);
    walls[3]->color = Color(0.0f, 0.0f, 0.0f, 1.0f);

    itemBullet = new ObRect;
    itemBullet->SetWorldPos(Vector2(180.0f, -50.0f));
    itemBullet->scale = Vector2(100.0f, 50.0f);
    itemBullet->color = Color(0.2f, 0.9f, 0.7f, 1.0f);
    itemBullet->collider = COLLIDER::RECT;

    idx = 0;
    for (auto& bullet : bullets)
    {
        bullet = new ObCircle;
        bullet->SetWorldPos(Vector2(3000.0f, 3000.0f));
        bullet->scale = Vector2(20.0f, 20.0f);
        bullet->color = Color(0.2f, 0.8f, 0.8f, 1.0f);
        bullet->collider = COLLIDER::CIRCLE;
        bullet->isVisible = false;
        bulletFired[idx] = false;
        idx++;
    }
    bulletFireCnt = 0;
}

void Main::Release()
{
    for (auto& line : endingLines) delete line;
    delete ball;
    delete bar;
    for (auto& brick : bricks) delete brick;
    for (auto& wall : walls) delete wall;
    delete itemBullet;
    for (auto& bullet : bullets) delete bullet;
}

void Main::Update()
{
    if (INPUT->KeyDown(restartKey)) Init();
    if (gameState == eGameState::end)
    {
        for (auto& line : endingLines) line->Update();
        return;
    }


    Vector2 velocity = ballFireDir * ballScalar * DELTA;
    ball->MoveWorldPos(velocity);

    if (INPUT->KeyPress(VK_LEFT))
    {
        barDir = -bar->GetRight();
        Vector2 velocity = barDir * barScalar * DELTA;
        bar->MoveWorldPos(velocity);
    }
    else if (INPUT->KeyPress(VK_RIGHT))
    {
        barDir = bar->GetRight();
        Vector2 velocity = barDir * barScalar * DELTA;
        bar->MoveWorldPos(velocity);
    }

    ball->Update();
    bar->Update();
    for (auto& wall : walls) wall->Update();

    int idx = 0;
    for (int r = 0; r < brickRow; r++)
    {
        for (int c = 0; c < brickCol; c++)
        {
            if (brickState[idx] == eState::hit)
            {
                bricks[idx]->color = Color(RANDOM->Float(0.6f, 1.0f), 0.0f, 0.0f);
                brickHitTime[idx] += 100.0f * DELTA;
                if (brickHitTime[idx] > 30.0f)
                {
                    if (brickLife[idx] == 2)
                    {
                        bricks[idx]->color = Color(0.9f, 0.7f, 0.0f, 1.0f);
                    }
                    else if (brickLife[idx] == 1)
                    {
                        bricks[idx]->color = Color(0.9f, 0.4f, 0.3f, 1.0f);
                    }
                    brickHitTime[idx] = 0.0f;
                    brickState[idx] = eState::idle;
                }
            }
            bricks[idx]->Update();
            idx++;
        }
    }

    // ºæ·¿ ¹ß»çÁÖ±â ¼¼ÆÃ
    itemBullet->Update();
    if (bulletFireCnt > 0)
    {
        bulletFireTime += 100.0f * DELTA;
        if (bulletFireTime > 80.0f)
        {
            idx = 0;
            for (auto& bullet : bullets)
            {
                if (bulletFired[idx] == false)
                {
                    bullet->SetWorldPos(bar->GetWorldPos());
                    bullet->isVisible = true;
                    bulletFired[idx] = true;
                    bulletFireCnt--;
                    bulletFireTime = 0.0f;
                    break;
                }
                idx++;
            }
        }
    }
    idx = 0;
    // ¹ß»ç
    for (auto& bullet : bullets)
    {
        if (bulletFired[idx])
        {
            Vector2 velocity = UP * 500.0f * DELTA;
            bullet->MoveWorldPos(velocity);
        }
        idx++;
    }
    for (auto& bullet : bullets) bullet->Update();
}

void Main::LateUpdate()
{
    if (gameState == eGameState::end) return;
    Vector2 mousePos = INPUT->GetWorldMousePos();

    // ¸ÕÀú À§Ä¡ °»½Å
    // ball->Update(); 

    auto bounce = [&](GameObject* ob, bool isIntersectBar = 0)
    {
        Vector2 direction = ball->GetWorldPos() - ballLastPos;
        direction.Normalize();

        if (interPos == IntersectPos::leftRight)
        {
            ballFireDir.x = -direction.x;
            ball->SetWorldPos(ballLastPos);
        }
        else if (interPos == IntersectPos::topBottom)
        {
            ballFireDir.y = -direction.y;
            ball->SetWorldPos(ballLastPos);
        }
        else if (interPos == IntersectPos::edge)
        {
            ballFireDir = -direction;
            ball->SetWorldPos(ballLastPos);
        }

        // ÁÂ¿ì
        //if (ballLastPos.x <= ob->GetWorldPos().x - ob->scale.x / 2 - ball->scale.x / 2 or
        //    ballLastPos.x >= ob->GetWorldPos().x + ob->scale.x / 2 + ball->scale.x / 2)
        //{
        //    ballFireDir.x = -direction.x;
        //}
        //// »óÇÏ
        //else if (ballLastPos.y <= ob->GetWorldPos().y - ob->scale.y / 2 - ball->scale.y / 2 or
        //         ballLastPos.y >= ob->GetWorldPos().y + ob->scale.y / 2 + ball->scale.y / 2)
        //{
        //    ballFireDir.y = -direction.y;
        //}
        // ¸ð¼­¸®
        // else
        // {
        //     ballFireDir = -direction;
        // }

        if (isIntersectBar)
        {
            ballFireDir.x = barDir.x;
        }
    };
    
    bar->Update();
    interPos = ball->Intersect(bar);
    if (interPos)
    {
        bounce(bar, true);
    }

    int idx = 0;
    endFlag = true;
    for (auto& brick : bricks)
    {
        brick->Update();
        interPos = ball->Intersect(brick);
        if (interPos)
        {
            bounce(brick);
            brickLife[idx]--;
            brickState[idx] = eState::hit;
            ballScalar += 10.0f;
        }
        if (brickLife[idx] <= 0)
        {
            brick->SetWorldPos(Vector2(2000.0f, 2000.0f));
        }

        // º®µ¹-ºæ·¿ Ãæµ¹
        for (auto& bullet : bullets)
        {
            interPos = bullet->Intersect(brick);
            if (interPos)
            {
                brickLife[idx]--;
                brickState[idx] = eState::hit;
                bullet->SetWorldPos(Vector2(2000.0f, 2000.0f));
                bullet->isVisible = false;
            }
        }

        if (brickLife[idx] > 0)
        {
            endFlag = false;
        }
        idx++;
    }
    if (endFlag)
    {
        gameState = eGameState::end;
    }

    for (auto& wall : walls)
    {
        wall->Update();
        interPos = ball->Intersect(wall);
        if (interPos)
        {
            bounce(wall);
        }

        interPos = bar->Intersect(wall);
        if (interPos)
        {
            // ÁÂ
            if (bar->GetWorldPos().x > wall->GetWorldPos().x)
            {
                bar->SetWorldPosX(wall->GetWorldPos().x + wall->scale.x / 2 + bar->scale.x / 2);
            }
            // ¿ì
            else
            {
                bar->SetWorldPosX(wall->GetWorldPos().x - wall->scale.x / 2 - bar->scale.x / 2);
            }
        }

        // º®-ºæ·¿ Ãæµ¹
        idx = 0;
        for (auto& bullet : bullets)
        {
            interPos = bullet->Intersect(wall);
            if (interPos)
            {
                bullet->SetWorldPos(Vector2(3000.0f, 3000.0f));
                bullet->isVisible = false;
            }
            idx++;
        }
    }

    // ºæ·¿ Æ®¸®°Å
    interPos = ball->Intersect(itemBullet);
    if (interPos)
    {
        bounce(itemBullet);
        itemBullet->SetWorldPos(Vector2(3000.0f, 3000.0f));
        bulletFireCnt = bulletMax;
    }


    ballLastPos = ball->GetWorldPos();
}

void Main::Render()
{
    ImGui::SliderFloat("Ball Last Pos X", &ballLastPos.x, -app.GetHalfWidth(), app.GetHalfWidth());
    ImGui::SliderFloat("Ball Last Pos Y", &ballLastPos.y, -app.GetHalfHeight(), app.GetHalfHeight());
    ImGui::SliderFloat("Ball Dir X", &ballFireDir.x, -1.0f, 1.0f);
    ImGui::SliderFloat("Ball Dir Y", &ballFireDir.y, -1.0f, 1.0f);
    ImGui::SliderFloat("Ball Scalar", &ballScalar, 600.0f, 1200.0f);
    ImGui::Text("Restart: %c", restartKey);

    if (gameState == eGameState::end)
    {
        for (auto& line : endingLines) line->Render();
        return;
    }
    ball->Render();
    bar->Render();
    for (auto& brick : bricks) brick->Render();
    for (auto& wall : walls) wall->Render();
    itemBullet->Render();
    for (auto& bullet : bullets) bullet->Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"À¯ÀçÁØ Alkaloid");
    app.SetInstance(instance);
    app.InitWidthHeight(600.0f, 960.0f);
    app.background = Color(0.1f, 0.1f, 0.1f, 1.0f);
    Main* main = new Main();
    int wParam = (int)WIN->Run(main);
    WIN->DeleteSingleton();
    SafeDelete(main);
    return wParam;
}