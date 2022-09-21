#include "stdafx.h"
#include "Main.h"
using namespace std;

void Main::Init()
{
    int idx = 0;

    bg = new UI;
    bg->img = new ObImage(L"EnterTheGungeon/Background.jpg");
    bg->img->scale.x = 700.0f * 2.0f;
    bg->img->scale.y = 370.0f * 2.0f;


    // 플레이어
    float playerScaleCoef = 3.0f;
    float playerWeaponScaleCoef = 1.5f;

    player = new Player;
    player->col = new ObCircle;
    player->col->scale.x = 12.0f * playerScaleCoef;
    player->col->scale.y = 12.0f * playerScaleCoef;
    player->col->SetWorldPosX(0.0f);
    player->col->SetWorldPosY(0.0f);
    player->col->color = Color(1.0f, 1.0f, 1.0f);
    player->col->isFilled = false;

    player->idle[front] = new ObImage(L"EnterTheGungeon/Player_0/Idle_Front.png");
    player->idle[leftSide] = new ObImage(L"EnterTheGungeon/Player_0/Idle_Side.png");
    player->idle[rightSide] = new ObImage(L"EnterTheGungeon/Player_0/Idle_Side.png");
    player->idle[leftDiag] = new ObImage(L"EnterTheGungeon/Player_0/Idle_Side.png");
    player->idle[rightDiag] = new ObImage(L"EnterTheGungeon/Player_0/Idle_Side.png");
    player->idle[back] = new ObImage(L"EnterTheGungeon/Player_0/Idle_Back.png");
    player->idle[backLeftDiag] = new ObImage(L"EnterTheGungeon/Player_0/Idle_BackDiag.png");
    player->idle[backRightDiag] = new ObImage(L"EnterTheGungeon/Player_0/Idle_BackDiag.png");

    idx = 0;
    for (auto& elem : player->idle)
    {
        elem->maxFrame.x = 4;
        elem->scale.x = 72.0 / 4.0f * playerScaleCoef;
        elem->scale.y = 20.0f * playerScaleCoef;
        elem->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
        elem->SetParentRT(*player->col);
        idx++;
    }

    player->walk[front] = new ObImage(L"EnterTheGungeon/Player_0/Walk_Front.png");
    player->walk[front]->scale.x = 96.0f / 6.0f * playerScaleCoef;
    player->walk[front]->scale.y = 24.0f * playerScaleCoef;

    player->walk[leftSide] = new ObImage(L"EnterTheGungeon/Player_0/Walk_Side.png");
    player->walk[leftSide]->scale.x = 96.0f / 6.0f * playerScaleCoef;
    player->walk[leftSide]->scale.y = 24.0f * playerScaleCoef;

    player->walk[rightSide] = new ObImage(L"EnterTheGungeon/Player_0/Walk_Side.png");
    player->walk[rightSide]->scale.x = 96.0f / 6.0f * playerScaleCoef;
    player->walk[rightSide]->scale.y = 24.0f * playerScaleCoef;

    player->walk[leftDiag] = new ObImage(L"EnterTheGungeon/Player_0/Walk_Side.png");
    player->walk[leftDiag]->scale.x = 96.0f / 6.0f * playerScaleCoef;
    player->walk[leftDiag]->scale.y = 24.0f * playerScaleCoef;

    player->walk[rightDiag] = new ObImage(L"EnterTheGungeon/Player_0/Walk_Side.png");
    player->walk[rightDiag]->scale.x = 96.0f / 6.0f * playerScaleCoef;
    player->walk[rightDiag]->scale.y = 24.0f * playerScaleCoef;

    player->walk[back] = new ObImage(L"EnterTheGungeon/Player_0/Walk_Back.png");
    player->walk[back]->scale.x = 84.0f / 6.0f * playerScaleCoef;
    player->walk[back]->scale.y = 24.0f * playerScaleCoef;

    player->walk[backLeftDiag] = new ObImage(L"EnterTheGungeon/Player_0/Walk_BackDiag.png");
    player->walk[backLeftDiag]->scale.x = 102.0f / 6.0f * playerScaleCoef;
    player->walk[backLeftDiag]->scale.y = 28.0f * playerScaleCoef;

    player->walk[backRightDiag] = new ObImage(L"EnterTheGungeon/Player_0/Walk_BackDiag.png");
    player->walk[backRightDiag]->scale.x = 102.0f / 6.0f * playerScaleCoef;
    player->walk[backRightDiag]->scale.y = 28.0f * playerScaleCoef;

    idx = 0;
    for (auto& elem : player->walk)
    {
        elem->maxFrame.x = 6;
        elem->isVisible = false;
        elem->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
        elem->SetParentRT(*player->col);
        idx++;
    }

    player->roll[front] = new ObImage(L"EnterTheGungeon/Player_0/Roll_Front.png");
    player->roll[leftSide] = new ObImage(L"EnterTheGungeon/Player_0/Roll_Side.png");
    player->roll[rightSide] = new ObImage(L"EnterTheGungeon/Player_0/Roll_Side.png");
    player->roll[leftDiag] = new ObImage(L"EnterTheGungeon/Player_0/Roll_Side.png");
    player->roll[rightDiag] = new ObImage(L"EnterTheGungeon/Player_0/Roll_Side.png");
    player->roll[back] = new ObImage(L"EnterTheGungeon/Player_0/Roll_Back.png");
    player->roll[backLeftDiag] = new ObImage(L"EnterTheGungeon/Player_0/Roll_BackDiag.png");
    player->roll[backRightDiag] = new ObImage(L"EnterTheGungeon/Player_0/Roll_BackDiag.png");

    idx = 0;
    for (auto& elem : player->roll)
    {
        elem->maxFrame.x = 9;
        elem->scale.x = 234.0 / 9.0f * playerScaleCoef;
        elem->scale.y = 28.0f * playerScaleCoef;
        elem->uv = Vector4(0.0f, 0.0f, 1.0f / 9.0f, 1.0f);
        elem->isVisible = false;
        elem->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
        elem->SetParentRT(*player->col);
        idx++;
    }


    player->hit = new ObImage(L"EnterTheGungeon/Player_0/Hit.png");
    player->hit->maxFrame.x = 3;
    player->hit->scale.x = 48.0f / 3.0f * playerScaleCoef;
    player->hit->scale.y = 22.0f * playerScaleCoef;
    player->hit->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
    player->hit->SetParentRT(*player->col);
    player->hit->isVisible = false;

    player->die = new ObImage(L"EnterTheGungeon/Player_0/Die.png");
    player->die->maxFrame.x = 3;
    player->die->scale.x = 48.0f / 3.0f * playerScaleCoef;
    player->die->scale.y = 22.0f * playerScaleCoef;
    player->die->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
    player->die->SetParentRT(*player->col);
    player->die->isVisible = false;

    player->respawn = new ObImage(L"EnterTheGungeon/Player_0/Respawn.png");
    player->respawn->maxFrame.x = 3;
    player->respawn->scale.x = 48.0f / 3.0f * playerScaleCoef;
    player->respawn->scale.y = 22.0f * playerScaleCoef;
    player->respawn->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
    player->respawn->SetParentRT(*player->col);
    player->respawn->isVisible = false;

    player->weapon = new Weapon;
    player->weapon->col = new ObRect;
    player->weapon->col->isFilled = false;
    player->weapon->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
    player->weapon->col->pivot = OFFSET_LB;
    player->weapon->col->scale.x = 29.0f * playerWeaponScaleCoef;
    player->weapon->col->scale.y = 21.0f * playerWeaponScaleCoef;
    player->weapon->col->SetParentT(*player->col);
    player->weapon->col->SetLocalPosX(18.0f);
    player->weapon->col->SetLocalPosY(-15.0f);
    player->weapon->col->pivot = Vector2(0.4f, 0.25f);
    player->weapon->idle = new ObImage(L"EnterTheGungeon/Player_0/Weapon_0.png");
    player->weapon->idle->pivot = Vector2(0.4f, 0.25f);
    player->weapon->idle->scale.x = 29.0f * playerWeaponScaleCoef;
    player->weapon->idle->scale.y = 21.0f * playerWeaponScaleCoef;
    player->weapon->idle->SetParentRT(*player->weapon->col);

    player->firePos = new GameObject;
    player->firePos->SetParentRT(*player->weapon->col);
    player->firePos->SetLocalPos(Vector2(50.0f, 0.0f));


    // 적
    float enemyScaleCoef = 3.0f;
    float enemyWeaponScaleCoef = 1.5f;

    for (auto& elem : enemy)
    {
        elem = new Enemy;
        elem->col = new ObCircle;
        elem->col->scale.x = 16.0f * enemyScaleCoef;
        elem->col->scale.y = 16.0f * enemyScaleCoef;
        elem->col->SetWorldPosX(RANDOM->Float(-400.0f, 400.0f));
        elem->col->SetWorldPosY(RANDOM->Float(-400.0f, 400.0f));
        elem->col->color = Color(1.0f, 1.0f, 1.0f);
        elem->col->isFilled = false;

        elem->idle[front] = new ObImage(L"EnterTheGungeon/Enemy_0/Idle_Front.png");
        elem->idle[leftSide] = new ObImage(L"EnterTheGungeon/Enemy_0/Idle_Side.png");
        elem->idle[rightSide] = new ObImage(L"EnterTheGungeon/Enemy_0/Idle_Side.png");
        elem->idle[leftDiag] = new ObImage(L"EnterTheGungeon/Enemy_0/Idle_Side.png");
        elem->idle[rightDiag] = new ObImage(L"EnterTheGungeon/Enemy_0/Idle_Side.png");
        elem->idle[back] = new ObImage(L"EnterTheGungeon/Enemy_0/Idle_Back.png");
        elem->idle[backLeftDiag] = new ObImage(L"EnterTheGungeon/Enemy_0/Idle_Back.png");
        elem->idle[backRightDiag] = new ObImage(L"EnterTheGungeon/Enemy_0/Idle_Back.png");

        idx = 0;
        for (auto& elem2 : elem->idle)
        {
            if (idx == leftSide || idx == leftDiag || idx == backLeftDiag)
            {
                elem2->rotationY = PI;
            }
            elem2->maxFrame.x = 2;
            elem2->scale.x = 29.0f / 2.0f * enemyScaleCoef;
            elem2->scale.y = 23.0f * enemyScaleCoef;
            elem2->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
            elem2->SetParentRT(*elem->col);
            idx++;
        }

        elem->walk[front] = new ObImage(L"EnterTheGungeon/Enemy_0/Walk_Front.png");
        elem->walk[leftSide] = new ObImage(L"EnterTheGungeon/Enemy_0/Walk_Side.png");
        elem->walk[rightSide] = new ObImage(L"EnterTheGungeon/Enemy_0/Walk_Side.png");
        elem->walk[leftDiag] = new ObImage(L"EnterTheGungeon/Enemy_0/Walk_Side.png");
        elem->walk[rightDiag] = new ObImage(L"EnterTheGungeon/Enemy_0/Walk_Side.png");
        elem->walk[back] = new ObImage(L"EnterTheGungeon/Enemy_0/Walk_Back.png");
        elem->walk[backLeftDiag] = new ObImage(L"EnterTheGungeon/Enemy_0/Walk_Back.png");
        elem->walk[backRightDiag] = new ObImage(L"EnterTheGungeon/Enemy_0/Walk_Back.png");

        idx = 0;
        for (auto& elem2 : elem->walk)
        {
            if (idx == leftSide || idx == leftDiag || idx == backLeftDiag)
            {
                elem2->rotationY = PI;
            }
            elem2->maxFrame.x = 2;
            elem2->scale.x = 29.0f / 2.0f * enemyScaleCoef;
            elem2->scale.y = 23.0f * enemyScaleCoef;
            elem2->isVisible = false;
            elem2->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
            elem2->SetParentRT(*elem->col);
            idx++;
        }

        elem->hit = new ObImage(L"EnterTheGungeon/Enemy_0/Hit.png");
        elem->hit->maxFrame.x = 13;
        elem->hit->scale.x = 238.0f / 13.0f * enemyScaleCoef;
        elem->hit->scale.y = 24.0f * enemyScaleCoef;
        elem->hit->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
        elem->hit->SetParentRT(*elem->col);
        elem->hit->isVisible = false;

        elem->die = new ObImage(L"EnterTheGungeon/Enemy_0/Die.png");
        elem->die->maxFrame.x = 2;
        elem->die->scale.x = 24.0f / 2.0f * enemyScaleCoef;
        elem->die->scale.y = 24.0f * enemyScaleCoef;
        elem->die->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
        elem->die->SetParentRT(*elem->col);
        elem->die->isVisible = false;

        elem->weapon = new Weapon;
        elem->weapon->col = new ObRect;
        elem->weapon->col->isFilled = false;
        elem->weapon->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        elem->weapon->col->pivot = OFFSET_LB;
        elem->weapon->col->scale.x = 29.0f * playerWeaponScaleCoef;
        elem->weapon->col->scale.y = 21.0f * playerWeaponScaleCoef;
        elem->weapon->col->SetParentRT(*elem->col);
        elem->weapon->col->SetLocalPosX(10.0f);
        elem->weapon->col->SetLocalPosY(-15.0f);
        elem->weapon->idle = new ObImage(L"EnterTheGungeon/Enemy_0/Weapon_0.png");
        elem->weapon->idle->pivot = OFFSET_LB;
        elem->weapon->idle->scale.x = 29.0f * playerWeaponScaleCoef;
        elem->weapon->idle->scale.y = 21.0f * playerWeaponScaleCoef;
        elem->weapon->idle->SetParentRT(*elem->weapon->col);

        elem->firePos = new GameObject;
        elem->firePos->SetParentRT(*elem->weapon->col);
        elem->firePos->SetLocalPos(Vector2(50.0f, 0.0f));
    }


    // 보스
    float bossScaleCoef = 3.0f;
    float bossWeaponScaleCoef = 2.0f;

    for (auto& elem : boss)
    {
        elem = new Boss;
        elem->curHp = elem->maxHp = 30;

        elem->col = new ObCircle;
        elem->col->scale.x = 25.0f * enemyScaleCoef;
        elem->col->scale.y = 25.0f * enemyScaleCoef;
        elem->col->SetWorldPosX(0.0f);
        elem->col->SetWorldPosY(400.0f);
        elem->col->color = Color(1.0f, 1.0f, 1.0f);
        elem->col->isFilled = false;

        elem->idle[front] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Front.png");
        elem->idle[leftSide] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Side.png");
        elem->idle[rightSide] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Side.png");
        elem->idle[leftDiag] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Side.png");
        elem->idle[rightDiag] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Side.png");
        elem->idle[back] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Back.png");
        elem->idle[backLeftDiag] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Back.png");
        elem->idle[backRightDiag] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Back.png");

        idx = 0;
        for (auto& elem2 : elem->idle)
        {
            if (idx == leftSide || idx == leftDiag || idx == backLeftDiag)
            {
                elem2->rotationY = PI;
            }
            elem2->maxFrame.x = 2;
            elem2->scale.x = 40.0f / 2.0f * enemyScaleCoef;
            elem2->scale.y = 40.0f * enemyScaleCoef;
            elem2->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
            elem2->SetParentRT(*elem->col);
            idx++;
        }

        elem->walk[front] = new ObImage(L"EnterTheGungeon/Boss_0/Walk_Front.png");
        elem->walk[leftSide] = new ObImage(L"EnterTheGungeon/Boss_0/Walk_Side.png");
        elem->walk[rightSide] = new ObImage(L"EnterTheGungeon/Boss_0/Walk_Side.png");
        elem->walk[leftDiag] = new ObImage(L"EnterTheGungeon/Boss_0/Walk_Side.png");
        elem->walk[rightDiag] = new ObImage(L"EnterTheGungeon/Boss_0/Walk_Side.png");
        elem->walk[back] = new ObImage(L"EnterTheGungeon/Boss_0/Walk_Back.png");
        elem->walk[backLeftDiag] = new ObImage(L"EnterTheGungeon/Boss_0/Walk_Back.png");
        elem->walk[backRightDiag] = new ObImage(L"EnterTheGungeon/Boss_0/Walk_Back.png");

        idx = 0;
        for (auto& elem2 : elem->walk)
        {
            if (idx == leftSide || idx == leftDiag || idx == backLeftDiag)
            {
                elem2->rotationY = PI;
            }
            elem2->maxFrame.x = 2;
            elem2->scale.x = 40.0f / 2.0f * enemyScaleCoef;
            elem2->scale.y = 40.0f * enemyScaleCoef;
            elem2->isVisible = false;
            elem2->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
            elem2->SetParentRT(*elem->col);
            idx++;
        }

        elem->hit = new ObImage(L"EnterTheGungeon/Boss_0/Hit.png");
        elem->hit->maxFrame.x = 13;
        elem->hit->scale.x = 238.0f / 13.0f * enemyScaleCoef;
        elem->hit->scale.y = 40.0f * enemyScaleCoef;
        elem->hit->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
        elem->hit->SetParentRT(*elem->col);
        elem->hit->isVisible = false;

        elem->die = new ObImage(L"EnterTheGungeon/Boss_0/Die.png");
        elem->die->maxFrame.x = 2;
        elem->die->scale.x = 40.0f / 2.0f * enemyScaleCoef;
        elem->die->scale.y = 40.0f * enemyScaleCoef;
        elem->die->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
        elem->die->SetParentRT(*elem->col);
        elem->die->isVisible = false;

        elem->weapon = new Weapon;
        elem->weapon->col = new ObRect;
        elem->weapon->col->isFilled = false;
        elem->weapon->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        elem->weapon->col->pivot = OFFSET_LB;
        elem->weapon->col->scale.x = 29.0f * playerWeaponScaleCoef;
        elem->weapon->col->scale.y = 21.0f * playerWeaponScaleCoef;
        elem->weapon->col->SetParentRT(*elem->col);
        elem->weapon->col->SetLocalPosX(10.0f);
        elem->weapon->col->SetLocalPosY(-15.0f);
        elem->weapon->idle = new ObImage(L"EnterTheGungeon/Boss_0/Weapon_0.png");
        elem->weapon->idle->pivot = OFFSET_LB;
        elem->weapon->idle->scale.x = 29.0f * playerWeaponScaleCoef;
        elem->weapon->idle->scale.y = 21.0f * playerWeaponScaleCoef;
        elem->weapon->idle->SetParentRT(*elem->weapon->col);

        elem->hpGuage = new UI;
        elem->hpGuage->img = new ObImage(L"Cookie/Time.png");
        elem->hpGuage->imgSize.x = 242.0f * 3.0f;
        elem->hpGuage->imgSize.y = 86.0f;
        elem->hpGuage->img->scale.x = elem->hpGuage->imgSize.x * 0.5f;
        elem->hpGuage->img->scale.y = elem->hpGuage->imgSize.y * 0.5f;
        elem->hpGuage->img->SetWorldPosX(-elem->hpGuage->imgSize.x * 0.5f);
        elem->hpGuage->img->SetWorldPosY(app.GetHalfHeight() - elem->hpGuage->imgSize.y * 0.5f);
        elem->hpGuage->img->pivot = OFFSET_L;
        elem->hpGuage->img->space = SPACE::SCREEN;
    }
}

void Main::Release()
{
    SafeDelete(bg);
    SafeDelete(player);
    for(auto& elem : enemy) SafeDelete(elem);
}

void Main::Update()
{
    if (INPUT->KeyDown('R'))
    {
        Release();
        Init();
    }

    ImGui::Text("FPS : %d", TIMER->GetFramePerSecond());

    bg->Update();

    player->Update();

    for (auto& elem : enemy)
    {
        elem->dest = player->col->GetWorldPos();
        elem->weapon->col->rotation = Utility::DirToRadian(player->col->GetWorldPos());
        elem->Update();
    }
    for (auto& elem : boss)
    {
        elem->dest = player->col->GetWorldPos();
        elem->weapon->col->rotation = Utility::DirToRadian(player->col->GetWorldPos());
        elem->Update();
    }
}

void Main::LateUpdate()
{
    // 타격
    for (auto& bulletElem : player->bullet)
    {
        for (auto& enemyElem : enemy)
        {
            if (abs(bulletElem->col->GetWorldPos().x - enemyElem->col->GetWorldPos().x) < 100 &&
                abs(bulletElem->col->GetWorldPos().y - enemyElem->col->GetWorldPos().y) < 100)
            {
                if (bulletElem->col->Intersect(enemyElem->col))
                {
                    enemyElem->Hit(1);
                    bulletElem->Hit(1);
                }
            }
        }
        for (auto& bossElem : boss)
        {
            if (abs(bulletElem->col->GetWorldPos().x - bossElem->col->GetWorldPos().x) < 100 &&
                abs(bulletElem->col->GetWorldPos().y - bossElem->col->GetWorldPos().y) < 100)
            {
                if (bulletElem->col->Intersect(bossElem->col))
                {
                    bossElem->Hit(1);
                    bulletElem->Hit(1);
                }
            }
        }
    }

    // 피격
    if (false == player->godMode)
    {
        for (auto& enemyElem : enemy)
        {
            if (abs(enemyElem->col->GetWorldPos().x - player->col->GetWorldPos().x) < 100 &&
                abs(enemyElem->col->GetWorldPos().y - player->col->GetWorldPos().y) < 100)
            {
                if (enemyElem->col->Intersect(player->col))
                {
                    player->Hit(1.0f);
                }
            }

            for (auto& bulletElem : enemyElem->bullet)
            {
                if (abs(bulletElem->col->GetWorldPos().x - player->col->GetWorldPos().x) < 100 &&
                    abs(bulletElem->col->GetWorldPos().y - player->col->GetWorldPos().y) < 100)
                {
                    if (bulletElem->col->Intersect(player->col))
                    {
                        player->Hit(1);
                        bulletElem->Hit(1);
                    }
                }
            }
            enemyElem->LateUpdate();
        }
        for (auto& bossElem : boss)
        {
            if (abs(bossElem->col->GetWorldPos().x - player->col->GetWorldPos().x) < 100 &&
                abs(bossElem->col->GetWorldPos().y - player->col->GetWorldPos().y) < 100)
            {
                if (bossElem->col->Intersect(player->col))
                {
                    player->Hit(1.0f);
                }
            }

            for (auto& bulletElem : bossElem->bullet)
            {
                if (abs(bulletElem->col->GetWorldPos().x - player->col->GetWorldPos().x) < 100 &&
                    abs(bulletElem->col->GetWorldPos().y - player->col->GetWorldPos().y) < 100)
                {
                    if (bulletElem->col->Intersect(player->col))
                    {
                        player->Hit(1);
                        bulletElem->Hit(1);
                    }
                }
            }
            bossElem->LateUpdate();
        }
    }

    player->LateUpdate();
}

void Main::Render()
{
    bg->Render();
    player->Render();
    for (auto& elem : enemy) elem->Render();
    for (auto& elem : boss) elem->Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"Enter the Gungeon by 유재준");
    app.SetInstance(instance);
    app.InitWidthHeight(1400.0f, 740.0f);
    Main* main = new Main();
    int wParam = (int)WIN->Run(main);
    WIN->DeleteSingleton();     // 창이 없어지고 난 후 
    SafeDelete(main);           // 메모리 해제
    return wParam;
}