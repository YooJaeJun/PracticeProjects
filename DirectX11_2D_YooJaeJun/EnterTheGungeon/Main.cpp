#include "stdafx.h"
#include "Main.h"
using namespace std;

void Main::Init()
{
    int idx = 0;

    LIGHT->light.radius = 2000.0f;
    tilemap = new ObTileMap;
    tilemap->file = "EnterTheGungeon.txt";
    tilemap->Load();
    tilemap->CreateTileCost();

    mapObj = new MapObject;

    // 플레이어
    float playerScaleCoef = 3.0f;

    player = new Player;
    player->col = new ObCircle;
    player->col->isFilled = false;
    player->col->scale.x = 12.0f * playerScaleCoef;
    player->col->scale.y = 12.0f * playerScaleCoef;

    Int2 on;
    if (tilemap->WorldPosToTileIdx(Vector2(-5.0f, 0.0f), on))
    {
        player->Spawn(tilemap->TileIdxToWorldPos(on));
    }

    player->col->color = Color(1.0f, 1.0f, 1.0f);

    player->idle[dirB] = new ObImage(L"EnterTheGungeon/Player_0/Idle_Front.png");
    player->idle[dirL] = new ObImage(L"EnterTheGungeon/Player_0/Idle_Side.png");
    player->idle[dirR] = new ObImage(L"EnterTheGungeon/Player_0/Idle_Side.png");
    player->idle[dirLB] = new ObImage(L"EnterTheGungeon/Player_0/Idle_Side.png");
    player->idle[dirRB] = new ObImage(L"EnterTheGungeon/Player_0/Idle_Side.png");
    player->idle[dirT] = new ObImage(L"EnterTheGungeon/Player_0/Idle_Back.png");
    player->idle[dirLT] = new ObImage(L"EnterTheGungeon/Player_0/Idle_BackDiag.png");
    player->idle[dirRT] = new ObImage(L"EnterTheGungeon/Player_0/Idle_BackDiag.png");

    idx = 0;
    for (auto& elem : player->idle)
    {
        if (idx == dirL || idx == dirLB || idx == dirLT)
        {
            elem->reverseLR = true;
        }
        elem->maxFrame.x = 4;
        elem->scale.x = 72.0 / 4.0f * playerScaleCoef;
        elem->scale.y = 20.0f * playerScaleCoef;
        elem->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
        elem->SetParentRT(*player->col);
        idx++;
    }

    player->walk[dirB] = new ObImage(L"EnterTheGungeon/Player_0/Walk_Front.png");
    player->walk[dirL] = new ObImage(L"EnterTheGungeon/Player_0/Walk_Side.png");
    player->walk[dirR] = new ObImage(L"EnterTheGungeon/Player_0/Walk_Side.png");
    player->walk[dirLB] = new ObImage(L"EnterTheGungeon/Player_0/Walk_Side.png");
    player->walk[dirRB] = new ObImage(L"EnterTheGungeon/Player_0/Walk_Side.png");
    player->walk[dirT] = new ObImage(L"EnterTheGungeon/Player_0/Walk_Back.png");
    player->walk[dirLT] = new ObImage(L"EnterTheGungeon/Player_0/Walk_BackDiag.png");
    player->walk[dirRT] = new ObImage(L"EnterTheGungeon/Player_0/Walk_BackDiag.png");

    idx = 0;
    for (auto& elem : player->walk)
    {
        if (idx == dirL || idx == dirLB || idx == dirLT)
        {
            elem->reverseLR = true;
        }
        elem->isVisible = false;
        elem->maxFrame.x = 6;
        elem->scale.x = 102.0f / 6.0f * playerScaleCoef;
        elem->scale.y = 24.0f * playerScaleCoef;
        elem->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
        elem->SetParentRT(*player->col);
        idx++;
    }

    player->roll[dirB] = new ObImage(L"EnterTheGungeon/Player_0/Roll_Front.png");
    player->roll[dirL] = new ObImage(L"EnterTheGungeon/Player_0/Roll_Side.png");
    player->roll[dirR] = new ObImage(L"EnterTheGungeon/Player_0/Roll_Side.png");
    player->roll[dirLB] = new ObImage(L"EnterTheGungeon/Player_0/Roll_Side.png");
    player->roll[dirRB] = new ObImage(L"EnterTheGungeon/Player_0/Roll_Side.png");
    player->roll[dirT] = new ObImage(L"EnterTheGungeon/Player_0/Roll_Back.png");
    player->roll[dirLT] = new ObImage(L"EnterTheGungeon/Player_0/Roll_BackDiag.png");
    player->roll[dirRT] = new ObImage(L"EnterTheGungeon/Player_0/Roll_BackDiag.png");

    idx = 0;
    for (auto& elem : player->roll)
    {
        if (idx == dirL || idx == dirLB || idx == dirLT)
        {
            elem->reverseLR = true;
        }
        elem->isVisible = false;
        elem->maxFrame.x = 9;
        elem->scale.x = 180.0f / 9.0f * playerScaleCoef;
        elem->scale.y = 24.0f * playerScaleCoef;
        elem->uv = Vector4(0.0f, 0.0f, 1.0f / 9.0f, 1.0f);
        elem->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
        elem->SetParentRT(*player->col);
        idx++;
    }

    player->hit = nullptr;

    player->fall = new ObImage(L"EnterTheGungeon/Player_0/Fall.png");
    player->fall->isVisible = false;
    player->fall->maxFrame.x = 3;
    player->fall->scale.x = 48.0f / 3.0f * playerScaleCoef;
    player->fall->scale.y = 22.0f * playerScaleCoef;
    player->fall->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
    player->fall->SetParentRT(*player->col);

    player->die = new ObImage(L"EnterTheGungeon/Player_0/Die.png");
    player->die->isVisible = false;
    player->die->maxFrame.x = 3;
    player->die->scale.x = 48.0f / 3.0f * playerScaleCoef;
    player->die->scale.y = 22.0f * playerScaleCoef;
    player->die->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
    player->die->SetParentRT(*player->col);

    player->respawn = new ObImage(L"EnterTheGungeon/Player_0/Respawn.png");
    player->respawn->isVisible = false;
    player->respawn->maxFrame.x = 3;
    player->respawn->scale.x = 48.0f / 3.0f * playerScaleCoef;
    player->respawn->scale.y = 22.0f * playerScaleCoef;
    player->respawn->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
    player->respawn->SetParentRT(*player->col);

    player->kick = new ObImage(L"EnterTheGungeon/Player_0/Kick.png");
    player->kick->isVisible = false;
    player->kick->maxFrame.x = 3;
    player->kick->scale.x = 48.0f / 3.0f * playerScaleCoef;
    player->kick->scale.y = 22.0f * playerScaleCoef;
    player->kick->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
    player->kick->SetParentRT(*player->col);

    player->obtain = new ObImage(L"EnterTheGungeon/Player_0/Obtatin.png");
    player->obtain->isVisible = false;
    player->obtain->maxFrame.x = 3;
    player->obtain->scale.x = 48.0f / 3.0f * playerScaleCoef;
    player->obtain->scale.y = 22.0f * playerScaleCoef;
    player->obtain->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
    player->obtain->SetParentRT(*player->col);


    float playerWeaponScaleCoef = 1.5f;

    player->weapon = new Weapon;
    player->weapon->col = new ObRect;
    player->weapon->col->isVisible = false;
    player->weapon->col->isFilled = false;
    player->weapon->col->pivot = Vector2(0.4f, 0.25f);
    player->weapon->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
    player->weapon->col->scale.x = 30.0f * playerWeaponScaleCoef;
    player->weapon->col->scale.y = 22.0f * playerWeaponScaleCoef;
    player->weapon->col->SetParentT(*player->col);
    player->weapon->col->SetLocalPosX(18.0f);
    player->weapon->col->SetLocalPosY(-15.0f);
    player->weapon->idle = new ObImage(L"EnterTheGungeon/Player_0/Weapon_0.png");
    player->weapon->idle->pivot = Vector2(0.4f, 0.25f);
    player->weapon->idle->scale.x = 30.0f * playerWeaponScaleCoef;
    player->weapon->idle->scale.y = 22.0f * playerWeaponScaleCoef;
    player->weapon->idle->SetParentRT(*player->weapon->col);

    player->firePos = new GameObject;
    player->firePos->SetParentRT(*player->weapon->col);
    player->firePos->SetLocalPos(Vector2(50.0f, 0.0f));

    player->shadow = new ObImage(L"EnterTheGungeon/Player_0/Shadow.png");
    player->shadow->scale.x = 16.0f * playerScaleCoef;
    player->shadow->scale.y = 5.0f * playerScaleCoef;
    player->shadow->SetParentRT(*player->col);
    player->shadow->SetWorldPosY(-28.0f);

    player->uiReload = new UI;
    player->uiReload->img = new ObImage(L"EnterTheGungeon/Player_0/UI_Reload.png");
    player->uiReload->img->isVisible = false;
    player->uiReload->img->scale = Vector2(144.0f, 20.0f);
    player->uiReload->img->SetParentT(*player->col);
    player->uiReload->img->SetLocalPosX(0.0f);
    player->uiReload->img->SetLocalPosY(60.0f);

    player->uiReloadBar = new UI;
    player->uiReloadBar->img = new ObImage(L"EnterTheGungeon/Player_0/UI_ReloadBar.png");
    player->uiReloadBar->img->isVisible = false;
    player->uiReloadBar->img->scale = Vector2(4.0f, 20.0f);
    player->uiReloadBar->img->SetParentT(*player->col);
    player->uiReloadBar->img->SetLocalPosX(-60.0f);
    player->uiReloadBar->img->SetLocalPosY(60.0f);

    player->uiMagazine = new UI;
    player->uiMagazine->img = new ObImage(L"EnterTheGungeon/Player_0/UI_Magazine.png");
    player->uiMagazine->img->scale = Vector2(28.0f, 99.0f);
    player->uiMagazine->img->SetWorldPos(Vector2(app.GetHalfWidth() - 40.0f, -app.GetHalfHeight() + 80.0f));
    player->uiMagazine->img->space = Space::screen;

    idx = 0;
    for (auto& elem : player->uiBullet)
    {
        elem = new UI;
        elem->img = new ObImage(L"EnterTheGungeon/Player_0/UI_Bullet.png");
        elem->img->scale = Vector2(12.0f, 4.0f);
        elem->img->SetWorldPos(Vector2(app.GetHalfWidth() - 40.0f, -app.GetHalfHeight() + 104.0f - idx * 12.0f));
        elem->img->space = Space::screen;
        idx++;
    }

    player->uiWeaponFrame = new UI;
    player->uiWeaponFrame->img = new ObImage(L"EnterTheGungeon/Player_0/UI_GunFrame.png");
    player->uiWeaponFrame->img->pivot = Vector2(0.4f, 0.25f);
    player->uiWeaponFrame->img->scale.x = 188.0f;
    player->uiWeaponFrame->img->scale.y = 116.0f;
    player->uiWeaponFrame->img->SetWorldPos(Vector2(app.GetHalfWidth() - 240.0f, -app.GetHalfHeight() + 50.0f));
    player->uiWeaponFrame->img->space = Space::screen;

    player->uiWeapon = new UI;
    player->uiWeapon->img = new ObImage(L"EnterTheGungeon/Player_0/UI_Weapon.png");
    player->uiWeapon->img->pivot = Vector2(0.4f, 0.25f);
    player->uiWeapon->img->scale.x = 60.0f;
    player->uiWeapon->img->scale.y = 48.0f;
    player->uiWeapon->img->SetWorldPos(Vector2(app.GetHalfWidth() - 190.0f, -app.GetHalfHeight() + 60.0f));
    player->uiWeapon->img->space = Space::screen;

    player->uiBulletCount = new UI;
    player->uiBulletCount->img = new ObImage(L"EnterTheGungeon/Player_0/UI_BulletCount.png");
    player->uiBulletCount->img->pivot = Vector2(0.4f, 0.25f);
    player->uiBulletCount->img->scale.x = 60.0f;
    player->uiBulletCount->img->scale.y = 28.0f;
    player->uiBulletCount->img->SetWorldPos(Vector2(app.GetHalfWidth() - 140.0f, -app.GetHalfHeight() + 150.0f));
    player->uiBulletCount->img->space = Space::screen;


    player->weaponReloading = new Weapon;
    player->weaponReloading->idle = new ObImage(L"EnterTheGungeon/Player_0/Weapon_0_reloading.png");
    player->weaponReloading->idle->isVisible = false;
    player->weaponReloading->idle->pivot = Vector2(0.4f, 0.25f);
    player->weaponReloading->idle->maxFrame.x = 2;
    player->weaponReloading->idle->scale.x = 42.0f / 2.0f * playerWeaponScaleCoef;
    player->weaponReloading->idle->scale.y = 22.0f * playerWeaponScaleCoef;
    player->weaponReloading->idle->SetParentRT(*player->weapon->col);
    player->weaponReloading->idle->ChangeAnim(ANIMSTATE::LOOP, 0.1f);


    // 적
    float enemyScaleCoef = 3.0f;

    for (auto& elem : enemy)
    {
        elem = new Enemy;
        elem->col = new ObCircle;
        elem->col->scale.x = 16.0f * enemyScaleCoef;
        elem->col->scale.y = 16.0f * enemyScaleCoef;
        elem->SetPosX(RANDOM->Float(-200.0f, 200.0f));
        elem->SetPosY(RANDOM->Float(-200.0f, 200.0f));
        elem->col->color = Color(1.0f, 1.0f, 1.0f);
        elem->col->isFilled = false;

        elem->idle[dirB] = new ObImage(L"EnterTheGungeon/Enemy_0/Idle_Front.png");
        elem->idle[dirL] = new ObImage(L"EnterTheGungeon/Enemy_0/Idle_Side.png");
        elem->idle[dirR] = new ObImage(L"EnterTheGungeon/Enemy_0/Idle_Side.png");
        elem->idle[dirLB] = new ObImage(L"EnterTheGungeon/Enemy_0/Idle_Side.png");
        elem->idle[dirRB] = new ObImage(L"EnterTheGungeon/Enemy_0/Idle_Side.png");
        elem->idle[dirT] = new ObImage(L"EnterTheGungeon/Enemy_0/Idle_Back.png");
        elem->idle[dirLT] = new ObImage(L"EnterTheGungeon/Enemy_0/Idle_Back.png");
        elem->idle[dirRT] = new ObImage(L"EnterTheGungeon/Enemy_0/Idle_Back.png");

        idx = 0;
        for (auto& elem2 : elem->idle)
        {
            if (idx == dirR || idx == dirRB || idx == dirRT)
            {
                elem2->reverseLR = true;
            }
            elem2->maxFrame.x = 2;
            elem2->scale.x = 28.0f / 2.0f * enemyScaleCoef;
            elem2->scale.y = 24.0f * enemyScaleCoef;
            elem2->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
            elem2->SetParentRT(*elem->col);
            idx++;
        }

        elem->walk[dirB] = new ObImage(L"EnterTheGungeon/Enemy_0/Walk_Front.png");
        elem->walk[dirL] = new ObImage(L"EnterTheGungeon/Enemy_0/Walk_Side.png");
        elem->walk[dirR] = new ObImage(L"EnterTheGungeon/Enemy_0/Walk_Side.png");
        elem->walk[dirLB] = new ObImage(L"EnterTheGungeon/Enemy_0/Walk_Side.png");
        elem->walk[dirRB] = new ObImage(L"EnterTheGungeon/Enemy_0/Walk_Side.png");
        elem->walk[dirT] = new ObImage(L"EnterTheGungeon/Enemy_0/Walk_Back.png");
        elem->walk[dirLT] = new ObImage(L"EnterTheGungeon/Enemy_0/Walk_Back.png");
        elem->walk[dirRT] = new ObImage(L"EnterTheGungeon/Enemy_0/Walk_Back.png");

        idx = 0;
        for (auto& elem2 : elem->walk)
        {
            if (idx == dirR || idx == dirRB || idx == dirRT)
            {
                elem2->reverseLR = true;
            }
            elem2->isVisible = false;
            elem2->maxFrame.x = 6;
            elem2->scale.x = 96.0f / 6.0f * enemyScaleCoef;
            elem2->scale.y = 24.0f * enemyScaleCoef;
            elem2->SetParentRT(*elem->col);
            idx++;
        }

        elem->hit = new ObImage(L"EnterTheGungeon/Enemy_0/Hit.png");
        elem->hit->isVisible = false;
        elem->hit->maxFrame.x = 1;
        elem->hit->scale.x = 16.0f * enemyScaleCoef;
        elem->hit->scale.y = 24.0f * enemyScaleCoef;
        elem->hit->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
        elem->hit->SetParentRT(*elem->col);

        elem->die = new ObImage(L"EnterTheGungeon/Enemy_0/Die.png");
        elem->die->isVisible = false;
        elem->die->maxFrame.x = 2;
        elem->die->scale.x = 24.0f / 2.0f * enemyScaleCoef;
        elem->die->scale.y = 24.0f * enemyScaleCoef;
        elem->die->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
        elem->die->SetParentRT(*elem->col);

        float enemyWeaponScaleCoef = 1.5f;

        elem->weapon = new Weapon;
        elem->weapon->col = new ObRect;
        elem->weapon->col->isVisible = false;
        elem->weapon->col->isFilled = false;
        elem->weapon->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        elem->weapon->col->pivot = OFFSET_LB;
        elem->weapon->col->scale.x = 29.0f * enemyWeaponScaleCoef;
        elem->weapon->col->scale.y = 21.0f * enemyWeaponScaleCoef;
        elem->weapon->col->SetParentRT(*elem->col);
        elem->weapon->col->SetLocalPosX(10.0f);
        elem->weapon->col->SetLocalPosY(-15.0f);
        elem->weapon->idle = new ObImage(L"EnterTheGungeon/Enemy_0/Weapon_0.png");
        elem->weapon->idle->pivot = OFFSET_LB;
        elem->weapon->idle->scale.x = 29.0f * enemyWeaponScaleCoef;
        elem->weapon->idle->scale.y = 21.0f * enemyWeaponScaleCoef;
        elem->weapon->idle->SetParentRT(*elem->weapon->col);

        elem->firePos = new GameObject;
        elem->firePos->SetParentRT(*elem->weapon->col);
        elem->firePos->SetLocalPos(Vector2(50.0f, 0.0f));

        elem->shadow = new ObImage(L"EnterTheGungeon/Enemy_0/Shadow_1.png");
        elem->shadow->scale.x = 12.0f * enemyScaleCoef;
        elem->shadow->scale.y = 4.0f * enemyScaleCoef;
        elem->shadow->SetParentRT(*elem->col);
        elem->shadow->SetWorldPosY(-35.0f);
    }


    // 보스
    float bossScaleCoef = 3.0f;

    boss = new Boss;
    boss->curHp = boss->maxHp = 30;

    boss->col = new ObCircle;
    boss->col->isFilled = false;
    boss->col->scale.x = 25.0f * bossScaleCoef;
    boss->col->scale.y = 25.0f * bossScaleCoef;
    boss->SetPosX(0.0f);
    boss->SetPosY(200.0f);
    boss->col->color = Color(1.0f, 1.0f, 1.0f);

    boss->idle[dirB] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Front.png");
    boss->idle[dirL] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Front.png");
    boss->idle[dirR] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Front.png");
    boss->idle[dirLB] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Front.png");
    boss->idle[dirRB] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Front.png");
    boss->idle[dirT] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Back.png");
    boss->idle[dirLT] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Back.png");
    boss->idle[dirRT] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Back.png");

    idx = 0;
    for (auto& elem : boss->idle)
    {
        if (idx == dirL || idx == dirLB || idx == dirLT)
        {
            elem->reverseLR = true;
        }
        elem->maxFrame.x = 4;
        elem->scale.x = 104.0f / 4.0f * bossScaleCoef;
        elem->scale.y = 40.0f * bossScaleCoef;
        elem->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
        elem->SetParentRT(*boss->col);
        idx++;
    }

    boss->walk[dirB] = new ObImage(L"EnterTheGungeon/Boss_0/Walk_Front.png");
    boss->walk[dirL] = new ObImage(L"EnterTheGungeon/Boss_0/Walk_Front.png");
    boss->walk[dirR] = new ObImage(L"EnterTheGungeon/Boss_0/Walk_Front.png");
    boss->walk[dirLB] = new ObImage(L"EnterTheGungeon/Boss_0/Walk_Front.png");
    boss->walk[dirRB] = new ObImage(L"EnterTheGungeon/Boss_0/Walk_Front.png");
    boss->walk[dirT] = new ObImage(L"EnterTheGungeon/Boss_0/Walk_Back.png");
    boss->walk[dirLT] = new ObImage(L"EnterTheGungeon/Boss_0/Walk_Back.png");
    boss->walk[dirRT] = new ObImage(L"EnterTheGungeon/Boss_0/Walk_Back.png");

    idx = 0;
    for (auto& elem : boss->walk)
    {
        if (idx == dirL || idx == dirLB || idx == dirLT)
        {
            elem->reverseLR = true;
        }
        elem->isVisible = false;
        elem->maxFrame.x = 2;
        elem->scale.x = 40.0f / 2.0f * bossScaleCoef;
        elem->scale.y = 40.0f * bossScaleCoef;
        elem->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
        elem->SetParentRT(*boss->col);
        idx++;
    }

    boss->hit = new ObImage(L"EnterTheGungeon/Boss_0/Hit.png");
    boss->hit->isVisible = false;
    boss->hit->maxFrame.x = 1;
    boss->hit->scale.x = 32.0 * 1.0f * bossScaleCoef;
    boss->hit->scale.y = 40.0f * bossScaleCoef;
    boss->hit->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
    boss->hit->SetParentRT(*boss->col);

    boss->die = new ObImage(L"EnterTheGungeon/Boss_0/Die.png");
    boss->die->isVisible = false;
    boss->die->maxFrame.x = 2;
    boss->die->scale.x = 40.0f / 2.0f * enemyScaleCoef;
    boss->die->scale.y = 40.0f * enemyScaleCoef;
    boss->die->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
    boss->die->SetParentRT(*boss->col);

    float bossWeaponScaleCoef = 2.0f;

    boss->weapon = new Weapon;
    boss->weapon->col = new ObRect;
    boss->weapon->col->isVisible = false;
    boss->weapon->col->isFilled = false;
    boss->weapon->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
    boss->weapon->col->pivot = OFFSET_LB;
    boss->weapon->col->scale.x = 29.0f * bossWeaponScaleCoef;
    boss->weapon->col->scale.y = 21.0f * bossWeaponScaleCoef;
    boss->weapon->col->SetParentRT(*boss->col);
    boss->weapon->col->SetLocalPosX(10.0f);
    boss->weapon->col->SetLocalPosY(-15.0f);
    boss->weapon->idle = new ObImage(L"EnterTheGungeon/Boss_0/Weapon_0.png");
    boss->weapon->idle->pivot = OFFSET_LB;
    boss->weapon->idle->scale.x = 29.0f * bossWeaponScaleCoef;
    boss->weapon->idle->scale.y = 21.0f * bossWeaponScaleCoef;
    boss->weapon->idle->SetParentRT(*boss->weapon->col);

    boss->hpGuageBar = new UI;
    boss->hpGuageBar->img = new ObImage(L"EnterTheGungeon/Boss_0/Hp_GuageBar.png");
    boss->hpGuageBar->imgSize.x = 400.0f;
    boss->hpGuageBar->imgSize.y = 30.0f;
    boss->hpGuageBar->img->scale.x = boss->hpGuageBar->imgSize.x;
    boss->hpGuageBar->img->scale.y = boss->hpGuageBar->imgSize.y;
    boss->hpGuageBar->img->SetWorldPosX(-boss->hpGuageBar->img->scale.x / 2.0f);
    boss->hpGuageBar->img->SetWorldPosY(-app.GetHalfHeight() + 40.0f);
    boss->hpGuageBar->img->pivot = OFFSET_L;
    boss->hpGuageBar->img->space = Space::screen;

    boss->hpGuage = new UI;
    boss->hpGuage->img = new ObImage(L"EnterTheGungeon/Boss_0/Hp_Guage.png");
    boss->hpGuage->imgSize.x = 330.0f;
    boss->hpGuage->imgSize.y = 16.0f;
    boss->hpGuage->img->scale.x = boss->hpGuage->imgSize.x;
    boss->hpGuage->img->scale.y = boss->hpGuage->imgSize.y;
    boss->hpGuage->img->SetWorldPosX(-boss->hpGuage->img->scale.x / 2.0f);
    boss->hpGuage->img->SetWorldPosY(-app.GetHalfHeight() + 40.0f);
    boss->hpGuage->img->pivot = OFFSET_L;
    boss->hpGuage->img->space = Space::screen;

    boss->shadow = new ObImage(L"EnterTheGungeon/Boss_0/Shadow_1.png");
    boss->shadow->scale.x = 12.0f * bossScaleCoef * 2.0f;
    boss->shadow->scale.y = 4.0f * bossScaleCoef * 2.0f;
    boss->shadow->SetParentRT(*boss->col);
    boss->shadow->SetWorldPosY(-55.0f);
}

void Main::Release()
{
    SafeDelete(tilemap);
    mapObj->Release();
    player->Release();
    for (auto& elem : enemy) elem->Release();
    boss->Release();
}

void Main::Update()
{
    if (INPUT->KeyDown('R'))
    {
        Release();
        Init();
    }

    ImGui::Text("FPS : %d", TIMER->GetFramePerSecond());


    tilemap->Update();

    mapObj->Update();

    player->Update();

    for (auto& elem : enemy)
    {
        elem->targetPos = player->Pos();
        elem->weapon->col->rotation = Utility::DirToRadian(player->Pos());
        // elem->FindPath(tilemap);
        elem->Update();
    }

    boss->targetPos = player->Pos();
    boss->weapon->col->rotation = Utility::DirToRadian(player->Pos());
    boss->Update();
}

void Main::LateUpdate()
{
    CheckIntersect();

    int idx = 0;

    for (auto& bulletElem : player->bullet)
    {
        for (auto& enemyElem : enemy)
        {
            if (bulletElem->col->Intersect(enemyElem->col))
            {
                enemyElem->Hit(bulletElem->damage);
                bulletElem->Hit(1);
            }
        }

        if (bulletElem->col->Intersect(boss->col))
        {
            boss->Hit(bulletElem->damage);
            bulletElem->Hit(1);
        }
    }


    for (auto& enemyElem : enemy)
    {
        if (false == player->godMode)
        {
            if (enemyElem->state != State::die &&
                enemyElem->col->Intersect(player->col))
            {
                player->Hit(1.0f);
            }

            for (auto& bulletElem : enemyElem->bullet)
            {
                if (bulletElem->col->Intersect(player->col))
                {
                    player->Hit(bulletElem->damage);
                    bulletElem->Hit(1);
                }
            }
        }

        for (auto& elem : mapObj->doorOpenUp)
        {
            if (elem->isOpen) continue;

            if (elem->col->Intersect(enemyElem->col))
            {
                enemyElem->StepBack();
            }
        }

        for (auto& elem : mapObj->doorClosed)
        {
            if (elem->col->Intersect(enemyElem->col))
            {
                enemyElem->StepBack();
            }
        }

        enemyElem->LateUpdate();
    }


    if (false == player->godMode)
    {
        if (boss->state != State::die &&
            boss->col->Intersect(player->col))
        {
            player->Hit(1);
        }

        for (auto& bulletElem : boss->bullet)
        {
            if (bulletElem->col->Intersect(player->col))
            {
                player->Hit(bulletElem->damage);
                bulletElem->Hit(1);
            }
        }
    }

    boss->LateUpdate();


    idx = 0;
    for (auto& elem : mapObj->doorOpenUp)
    {
        if (false == elem->isOpen)
        {
            if (elem->col->Intersect(player->col))
            {
                Vector2 dir = elem->Pos() - player->Pos();
                if (dir.y < 0.0f)
                {
                    elem->idle->isVisible = false;
                    mapObj->doorOpenDown[idx]->idle->isVisible = true;
                    mapObj->doorOpenDown[idx]->idle->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
                }
                else
                {
                    elem->idle->isVisible = true;
                    elem->idle->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
                }

                elem->col->isVisible = false;
                elem->isOpen = true;
                mapObj->doorOpenDown[idx]->col->isVisible = false;
                mapObj->doorOpenDown[idx]->isOpen = true;
            }
        }
        idx++;
    }


    for (auto& elem : mapObj->doorClosed)
    {
        if (elem->col->Intersect(player->col))
        {
            Vector2 dir = elem->Pos() - player->Pos();
            dir.Normalize();
            player->SetPos(player->Pos() - dir);
            dir.Normalize();
        }
    }
    

    player->LateUpdate();
}

void Main::Render()
{
    tilemap->Render();
    mapObj->Render();
    player->Render();
    for (auto& elem : enemy) elem->Render();
    boss->Render();
}

void Main::ResizeScreen()
{
    player->uiMagazine->img->SetWorldPos(Vector2(app.GetHalfWidth() - 40.0f, -app.GetHalfHeight() + 80.0f));
    player->uiWeaponFrame->img->SetWorldPos(Vector2(app.GetHalfWidth() - 240.0f, -app.GetHalfHeight() + 50.0f));
    player->uiWeapon->img->SetWorldPos(Vector2(app.GetHalfWidth() - 190.0f, -app.GetHalfHeight() + 60.0f));
    player->uiBulletCount->img->SetWorldPos(Vector2(app.GetHalfWidth() - 140.0f, -app.GetHalfHeight() + 150.0f));
    int idx = 0;
    for (auto& elem : player->uiBullet)
    {
        elem->img->SetWorldPos(Vector2(app.GetHalfWidth() - 40.0f, -app.GetHalfHeight() + 104.0f - idx * 12.0f));
        idx++;
    }

    boss->hpGuageBar->img->SetWorldPosX(-boss->hpGuageBar->img->scale.x / 2.0f);
    boss->hpGuageBar->img->SetWorldPosY(-app.GetHalfHeight() + 40.0f);
    boss->hpGuage->img->SetWorldPosX(-boss->hpGuage->img->scale.x / 2.0f);
    boss->hpGuage->img->SetWorldPosY(-app.GetHalfHeight() + 40.0f);
}

void Main::CheckIntersect()
{
    /*
    grid.clear();

    int idx = 0;

    Int2 on;
    if (tilemap->WorldPosToTileIdx(player->Pos(), on))
    {
        ImGui::Text("TileState %d", tilemap->GetTileState(on));

        if (tilemap->GetTileState(on) == TileState::wall)
        {
            player->StepBack();
        }

        if (grid[on].size())
        {
            for (auto& elem : grid[on])
            {
                if (elem->col->Intersect(player->col))
                {

                }
            }
        }
        else
        {
            grid[on].push_back(player);
        }
    }
    mapObj;
    player;
    enemy[enemyMax];
    boss;
    */
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