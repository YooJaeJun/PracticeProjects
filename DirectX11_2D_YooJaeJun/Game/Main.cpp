#include "stdafx.h"
#include "Main.h"
using namespace std;

void Main::Init()
{
    bg = new UI;
    bg->img = new ObImage(L"EnterTheGungeon/Background.jpg");
    bg->img->scale.x = 700.0f * 2.0f;
    bg->img->scale.y = 370.0f * 2.0f;


    float playerScaleCoef = 3.0f;
    float playerWeaponScaleCoef = 1.5f;

    player = new Player;
    player->col = new ObCircle;
    player->col->scale.x = 15.0f * playerScaleCoef;
    player->col->scale.y = 15.0f * playerScaleCoef;
    player->col->SetWorldPosX(0.0f);
    player->col->SetWorldPosY(0.0f);
    player->col->color = Color(1.0f, 1.0f, 1.0f);
    player->col->isFilled = false;


    player->idle = new ObImage(L"EnterTheGungeon/Player_0_Idle.png");
    player->idle->maxFrame.x = 3;
    player->idle->scale.x = 48.0f / 3.0f * playerScaleCoef;
    player->idle->scale.y = 22.0f * playerScaleCoef;
    player->idle->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
    player->idle->SetParentRT(*player->col);

    player->walk = new ObImage(L"EnterTheGungeon/Player_0_Roll.png");
    player->walk->maxFrame.x = 3;
    player->walk->scale.x = 48.0f / 3.0f * playerScaleCoef;
    player->walk->scale.y = 22.0f * playerScaleCoef;
    player->walk->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
    player->walk->SetParentRT(*player->col);
    player->walk->isVisible = false;

    player->roll = new ObImage(L"EnterTheGungeon/Player_0_Roll.png");
    player->roll->maxFrame.x = 9;
    player->roll->scale.x = 168.0f / 9.0f * playerScaleCoef;
    player->roll->scale.y = 28.0f * playerScaleCoef;
    player->roll->uv = Vector4(0.0f, 0.0f, 1.0f / 9.0f, 1.0f);
    player->roll->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
    player->roll->SetParentRT(*player->col);
    player->roll->isVisible = false;

    player->hit = new ObImage(L"EnterTheGungeon/Player_0_Idle.png");
    player->hit->maxFrame.x = 3;
    player->hit->scale.x = 48.0f / 3.0f * playerScaleCoef;
    player->hit->scale.y = 22.0f * playerScaleCoef;
    player->hit->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
    player->hit->SetParentRT(*player->col);
    player->hit->isVisible = false;

    player->die = new ObImage(L"EnterTheGungeon/Player_0_Idle.png");
    player->die->maxFrame.x = 3;
    player->die->scale.x = 48.0f / 3.0f * playerScaleCoef;
    player->die->scale.y = 22.0f * playerScaleCoef;
    player->die->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
    player->die->SetParentRT(*player->col);
    player->die->isVisible = false;

    player->respawn = new ObImage(L"EnterTheGungeon/Player_0_Idle.png");
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
    player->weapon->col->SetParentRT(*player->col);
    player->weapon->col->SetLocalPosX(10.0f);
    player->weapon->col->SetLocalPosY(-15.0f);
    player->weapon->idle = new ObImage(L"EnterTheGungeon/Weapon_0.png");
    player->weapon->idle->pivot = OFFSET_LB;
    player->weapon->idle->scale.x = 29.0f * playerWeaponScaleCoef;
    player->weapon->idle->scale.y = 21.0f * playerWeaponScaleCoef;
    player->weapon->idle->SetParentRT(*player->weapon->col);


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

        elem->idle = new ObImage(L"EnterTheGungeon/Enemy_0_Idle.png");
        elem->idle->maxFrame.x = 2;
        elem->idle->scale.x = 24.0f / 2.0f * enemyScaleCoef;
        elem->idle->scale.y = 24.0f * enemyScaleCoef;
        elem->idle->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
        elem->idle->SetParentRT(*elem->col);

        elem->walk = new ObImage(L"EnterTheGungeon/Enemy_0_Idle.png");
        elem->walk->maxFrame.x = 2;
        elem->walk->scale.x = 24.0f / 2.0f * enemyScaleCoef;
        elem->walk->scale.y = 24.0f * enemyScaleCoef;
        elem->walk->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
        elem->walk->SetParentRT(*elem->col);
        elem->walk->isVisible = false;

        elem->roll = nullptr;

        elem->hit = new ObImage(L"EnterTheGungeon/Enemy_0_Idle.png");
        elem->hit->maxFrame.x = 2;
        elem->hit->scale.x = 24.0f / 2.0f * enemyScaleCoef;
        elem->hit->scale.y = 24.0f * enemyScaleCoef;
        elem->hit->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
        elem->hit->SetParentRT(*elem->col);
        elem->hit->isVisible = false;

        elem->die = new ObImage(L"EnterTheGungeon/Enemy_0_Idle.png");
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
        elem->weapon->idle = new ObImage(L"EnterTheGungeon/Weapon_0.png");
        elem->weapon->idle->pivot = OFFSET_LB;
        elem->weapon->idle->scale.x = 29.0f * playerWeaponScaleCoef;
        elem->weapon->idle->scale.y = 21.0f * playerWeaponScaleCoef;
        elem->weapon->idle->SetParentRT(*elem->weapon->col);
    }

    float bossScaleCoef = 3.0f;
    float bossWeaponScaleCoef = 2.0f;

    for (auto& elem : boss)
    {
        elem = new Boss;
        elem->curHp = elem->maxHp = 20;

        elem->col = new ObCircle;
        elem->col->scale.x = 30.0f * enemyScaleCoef;
        elem->col->scale.y = 30.0f * enemyScaleCoef;
        elem->col->SetWorldPosX(200.0f);
        elem->col->SetWorldPosY(0.0f);
        elem->col->color = Color(1.0f, 1.0f, 1.0f);
        elem->col->isFilled = false;

        elem->idle = new ObImage(L"EnterTheGungeon/Enemy_0_Idle.png");
        elem->idle->maxFrame.x = 2;
        elem->idle->scale.x = 40.0f / 2.0f * enemyScaleCoef;
        elem->idle->scale.y = 40.0f * enemyScaleCoef;
        elem->idle->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
        elem->idle->SetParentRT(*elem->col);

        elem->walk = new ObImage(L"EnterTheGungeon/Enemy_0_Idle.png");
        elem->walk->maxFrame.x = 2;
        elem->walk->scale.x = 40.0f / 2.0f * enemyScaleCoef;
        elem->walk->scale.y = 40.0f * enemyScaleCoef;
        elem->walk->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
        elem->walk->SetParentRT(*elem->col);
        elem->walk->isVisible = false;

        elem->roll = nullptr;

        elem->hit = new ObImage(L"EnterTheGungeon/Enemy_0_Idle.png");
        elem->hit->maxFrame.x = 2;
        elem->hit->scale.x = 40.0f / 2.0f * enemyScaleCoef;
        elem->hit->scale.y = 40.0f * enemyScaleCoef;
        elem->hit->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
        elem->hit->SetParentRT(*elem->col);
        elem->hit->isVisible = false;

        elem->die = new ObImage(L"EnterTheGungeon/Enemy_0_Idle.png");
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
        elem->weapon->idle = new ObImage(L"EnterTheGungeon/Weapon_0.png");
        elem->weapon->idle->pivot = OFFSET_LB;
        elem->weapon->idle->scale.x = 29.0f * playerWeaponScaleCoef;
        elem->weapon->idle->scale.y = 21.0f * playerWeaponScaleCoef;
        elem->weapon->idle->SetParentRT(*elem->weapon->col);

        elem->hpGuage = new UI;
        elem->hpGuage->img = new ObImage(L"Cookie/Time.png");
        elem->hpGuage->imgSize.x = 242.0f;
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
        elem->Update();
    }

    for (auto& elem : boss) elem->Update();
}

void Main::LateUpdate()
{
    player->LateUpdate();
    for(auto& elem : enemy) elem->LateUpdate();

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
    }

    for (auto& elem : boss) elem->LateUpdate();
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