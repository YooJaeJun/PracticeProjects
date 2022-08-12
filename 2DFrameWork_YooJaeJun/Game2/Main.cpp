#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
    player = make_shared<Unit>();
    player->hitbox.SetWorldPos(Vector2(-500.0f, -250.0f));
    player->name = "1p";
    
    enemy = make_shared<Unit>();
    enemy->hitbox.SetWorldPos(Vector2(500.0f, -250.0f));
    enemy->name = "2p";

    for (int i = 0; i < bulletMax; i++) 
    {
        bullet[i] = make_shared<Bullet>();
    }

    ground = make_shared<ObRect>();
    ground->scale = Vector2(width, 70.0f);
    ground->pivot = OFFSET_LT;
    ground->SetWorldPos(Vector2(-app.GetHalfWidth(), -app.GetHalfHeight() + ground->scale.y));

    turn = (int)eturn::player;
    cout << "\n-----\n";
    cout << "시작 \n";
    cout << "-----\n\n";
    cout << "1p 턴 \n";
}

void Main::Release()
{
}

void Main::Act(shared_ptr<Unit> unit)
{
    unit->Move();

    if (INPUT->KeyDown(VK_SPACE))
    {
        unit->shootGauge.scale.x = 0.0f;
    }

    if (INPUT->KeyPress(VK_SPACE))
    {
        unit->shootGauge.scale.x += 100.0f * DELTA;

        if (unit->shootGauge.scale.x > 100.0f)
        {
            unit->shootGauge.scale.x = 0.0f;
        }
    }

    if (INPUT->KeyUp(VK_SPACE))
    {
        for (int i = 0; i < bulletMax; i++)
        {
            if (bullet[i]->Shoot(
                unit->hitbox,
                unit->shootGauge.scale.x,
                unit->firePos.GetWorldPos()))
            {
                break;
            }
        }

        lastTurn = turn;
        turn = (int)eturn::neutral;
        cout << "... turn 대기 ... \n";
    }
}

void Main::Update()
{
    if (INPUT->KeyDown('R'))
    {
        state = (int)estate::run;
        Init();
        player->Init(Vector2(-500.0f, -250.0f));
        enemy->Init(Vector2(500.0f, -250.0f));
        for (auto& elem : bullet)
        {
            elem->Init();
        }
    }
    if (state == (int)estate::end) return;

    if      (turn == (int)eturn::player) Act(player);
    else if (turn == (int)eturn::enemy)  Act(enemy);

    player->Update();
    enemy->Update();

    for (int i = 0; i < bulletMax; i++)
    {
        bullet[i]->Update(player->hitbox);
    }

    ground->Update();
}

void Main::LateUpdate()
{
    if (state == (int)estate::end) return;

    player->LateUpdate();
    enemy->LateUpdate();

    for (int i = 0; i < bulletMax; i++)
    {
        // 턴 변경
        if (bullet[i]->LateUpdate())
        {
            if (lastTurn == (int)eturn::player)
            {
                turn = (int)eturn::enemy;
                cout << "2p 턴 \n";
            }
            else if (lastTurn == (int)eturn::enemy)
            {
                turn = (int)eturn::player;
                cout << "1p 턴 \n";
            }
        }

        // 충돌
        if (bullet[i]->hitbox.isVisible)
        {
            bool playerHit = player->hitbox.Intersect(&bullet[i]->hitbox);
            bool enemyHit = enemy->hitbox.Intersect(&bullet[i]->hitbox);

            if (playerHit or enemyHit)
            {
                bullet[i]->hitbox.isVisible = false;
                bullet[i]->hitbox.SetWorldPos(Vector2(2000.0f, 2000.0f));

                if (playerHit)
                {
                    if (player->HitFrom(30))  // true: 사망
                    {
                        state = (int)estate::end;
                        cout << "재시작: R \n";
                    }
                    turn = (int)eturn::player;
                }
                else if (enemyHit)
                {
                    if (enemy->HitFrom(30))     // true: 사망
                    {
                        state = (int)estate::end;
                        cout << "재시작: R \n";
                    }
                    turn = (int)eturn::enemy;
                }
            }
        } // 충돌 종료
    }// 모든 bullet 탐색 종료
}

void Main::Render()
{
    player->Render();
    enemy->Render();

    for (int i = 0; i < bulletMax; i++)
    {
        bullet[i]->Render();
    }

    ground->Render();
}

void Main::ResizeScreen()
{
}



int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"윾재준의 신나는 도형 포트리스 ↖^_^↗");
	app.SetInstance(instance);
    app.background = Color(0.3f, 0.3f, 0.3f, 1.0f);
	Main* main = new Main();
    main->width = 1280.0f;
    main->height = 720.0f;
    app.InitWidthHeight(main->width, main->height);
    int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}