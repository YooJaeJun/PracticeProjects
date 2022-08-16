#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    for (auto& platform : platforms)
    {
        platform = make_shared<Platform>();
        platform->Init();
    }
    platforms[1]->hitbox->SetWorldPos(Vector2(200.0f, -app.GetHalfHeight() + platforms[1]->hitbox->scale.y));
    platforms[2]->hitbox->scale = Vector2(100.0f, 400.0f);
    platforms[2]->hitbox->SetWorldPos(Vector2(-50.0f, 0.0f));


    player = make_shared<Player>();
    player->hitbox->SetWorldPos(Vector2(-500.0f, 0.0f));
    player->name = "1p";

    enemy = make_shared<Player>();
    enemy->hitbox->SetWorldPos(Vector2(500.0f, 0.0f));
    enemy->hitbox->rotationY = 180.0f * ToRadian;
    enemy->name = "2p";

    for (auto& bullet : bullets)
    {
        bullet = make_shared<Bullet>();
    }


    for (auto& line : lines)
    {
        line.scale.x = 100.0f;
        line.color = Color(1.0f, 1.0f, 1.0f, 1.0f);
    }

    for (auto& star : stars)
    {
        star.scale = Vector2(25.0f, 25.0f);
        star.isVisible = true;
        star.isFilled = true;
        star.color = Color(RANDOM->Float(0.5f, 0.9f), RANDOM->Float(0.4f, 0.8f), RANDOM->Float(0.4f, 0.6f));
        star.rotation = RANDOM->Float(0.0f, 359.0f) * ToRadian;
    }
    for (int i = 0; i < starCount / 2; i++)
    {
        stars[i].SetWorldPos(Vector2(RANDOM->Float(-app.GetHalfWidth(), 0.0f), RANDOM->Float(100.0f, app.GetHalfHeight())));
    }
    for (int i = starCount / 2; i < starCount; i++)
    {
        stars[i].SetWorldPos(Vector2(RANDOM->Float(0.0f, app.GetHalfWidth()), RANDOM->Float(100.0f, app.GetHalfHeight())));
    }


    for (int i = 0; i < particleCount; i++)
    {
        particles[i] = make_shared<Particle>();
        particles[i]->Init(i);
    }


    lines[0].SetWorldPos(Vector2(-100.0f, 120.0f));
    lines[1].SetWorldPos(Vector2(0.0f, 120.0f));
    lines[1].rotation = -90.0f * ToRadian;
    lines[2].SetWorldPos(Vector2(0.0f, 120.0f));
    lines[3].SetWorldPos(Vector2(100.0f, 120.0f));
    lines[3].rotation = -90.0f * ToRadian;

    lines[4].SetWorldPos(Vector2(-120.0f, 0.0f));
    lines[4].scale.x = 240.0f;

    lines[5].SetWorldPos(Vector2(0.0f, -20.0f));
    lines[5].rotation = -120.0f * ToRadian;
    lines[6].SetWorldPos(Vector2(0.0f, -20.0f));
    lines[6].rotation = -60.0f * ToRadian;


    state = (int)estate::run;
    turn = (int)eturn::player;
    cout << "\n------\n";
    cout << "스따뚜 (재시작은 R키임) \n";
    cout << "------\n\n";
    cout << "1p 턴 \n";

}

void Main::Release()
{
}

void Main::Update()
{
    if (INPUT->KeyDown('R'))
    {
        Init();
        state = (int)estate::run;
        player->Init();
        enemy->Init();
        enemy->hitbox->rotationY = 180.0f * ToRadian;
        player->hitbox->SetWorldPos(Vector2(-500.0f, 0.0f));
        enemy->hitbox->SetWorldPos(Vector2(500.0f, 0.0f));

        for (auto& bullet : bullets)
        {
            bullet->Init();
        }
        for (int i = 0; i < particleCount; i++)
        {
            particles[i]->Init(i);
        }
    }
    if (state == (int)estate::end)
    {
        for (auto& line : lines) line.Update();
        return;
    }

    if      (turn == (int)eturn::player) Act(player);
    else if (turn == (int)eturn::enemy)  Act(enemy);


    player->Update();
    enemy->Update();

    for (auto& bullet : bullets)
    {
        bullet->Update();
    }

    for (auto& platform : platforms)
    {
        platform->Update();
    }

    for (auto& star : stars)
    {
        star.Update();
    }

    for (auto& particle : particles)
    {
        particle->Update();
    }
}

void Main::LateUpdate()
{
    if (state == (int)estate::end) return;

    if (player->LateUpdate() || enemy->LateUpdate())
    {
        End();
    }

    player->onGround = false;
    enemy->onGround = false;
    for (auto& platform : platforms)
    {
        for (auto& wheel : player->wheels)
        {
            if (platform->hitbox->Intersect(&wheel))
            {
                player->onGround = true;
            }
        }
        for (auto& wheel : enemy->wheels)
        {
            if (platform->hitbox->Intersect(&wheel))
            {
                enemy->onGround = true;
            }
        }
    }
    if (false == player->onGround)
    {
        player->Down();
    }
    if (false == enemy->onGround)
    {
        enemy->Down();
    }


    for (auto& bullet : bullets)
    {
        // 충돌 시 턴 변경
        if (bullet->LateUpdate())
        {
            TurnUpdate();
        }

        // 충돌
        if (bullet->hitbox->isVisible)
        {
            bool playerHit = player->hitbox->Intersect(&*bullet->hitbox);
            bool enemyHit = enemy->hitbox->Intersect(&*bullet->hitbox);

            if (playerHit or enemyHit)
            {
                for (auto& particle : particles)
                {
                    particle->Spawn(bullet->lastPos);
                }
                
                if (playerHit)
                {
                    bullet->HitFrom("1p", 999.0f);

                    if (player->HitFrom(bullet->damage))  // true: 사망
                    {
                        End();
                    }
                    else
                    {
                        turn = (int)eturn::player;
                        cout << '\n' << enemy->name << " 턴 \n";
                    }
                }
                else if (enemyHit)
                {
                    bullet->HitFrom("2p", 999.0f);

                    if (enemy->HitFrom(bullet->damage))     // true: 사망
                    {
                        End();
                    }
                    else
                    {
                        turn = (int)eturn::enemy;
                        cout << '\n' << player->name << " 턴 \n";
                    }
                }
            }


            for (auto& platform : platforms)
            {
                if (bullet->hitbox->Intersect(&*platform->hitbox))
                {
                    for (auto& particle : particles)
                    {
                        particle->Spawn(bullet->lastPos);
                    }
                    bullet->HitFrom("벽", 999.0f);
                    TurnUpdate();
                }
            }

        }   // 충돌 종료
    }   // 모든 bullet 탐색 종료
}

void Main::Render()
{
    if (state == (int)estate::end)
    {
        for (auto& line : lines)
        {
            line.Render();
        }
        return;
    }

    player->Render();
    enemy->Render();

    for (auto& bullet : bullets)
    {
        bullet->Render();
    }

    for (auto& platform : platforms)
    {
        platform->Render();
    }

    for (auto& star : stars)
    {
        star.Render();
    }

    for (auto& particle : particles)
    {
        particle->Render();
    }
}

void Main::ResizeScreen()
{
}

void Main::Act(shared_ptr<Player> unit)
{
    unit->Move();
    unit->GaugeUp();

    if (INPUT->KeyUp(VK_SPACE))
    {
        for (auto& bullet : bullets)
        {
            if (bullet->Shoot(
                unit->hitbox,
                unit->shootGauge.scale.x,
                unit->firePos.GetWorldPos()))
                break;
        }

        lastTurn = turn;
        turn = (int)eturn::neutral;
        cout << "... turn 대기 ... \n";
    }
}

void Main::TurnUpdate()
{
    if (lastTurn == (int)eturn::player)
    {
        turn = (int)eturn::enemy;
        cout << '\n' << enemy->name << " 턴 \n";
    }
    else if (lastTurn == (int)eturn::enemy)
    {
        turn = (int)eturn::player;
        cout << '\n' << player->name << " 턴 \n";
    }
}

void Main::End()
{
    state = (int)estate::end;
    cout << "재시작: R \n";
}


int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"윾재준의 신나는 도형 포트리스 ↖^_^↗");
	app.SetInstance(instance);
    app.background = Color(0.2f, 0.2f, 0.2f, 1.0f);
	Main* main = new Main();
    main->width = 1280.0f;
    main->height = 720.0f;
    app.InitWidthHeight(main->width, main->height);
    int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}