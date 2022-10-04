#include "stdafx.h"

namespace Gungeon
{
    Scene02::Scene02()
    {
        Init();
    }

    Scene02::~Scene02()
    {
        mapObj->Release();
        player->Release();
        for (auto& elem : enemy) elem->Release();
        boss->Release();
    }

    void Scene02::Init()
    {
        LIGHT->light.radius = 2000.0f;

        SOUND->Stop("SCENE01");
        //SOUND->AddSound("15051562_MotionElements_8-bit-arcade-swordsman.wav", "SCENE02", true);
        SOUND->Play("SCENE02");

        // 맵 오브젝트
        mapObj = new MapObject;

        // 플레이어
        player = new Player;

        InitEnemy();
        InitBoss();
        InitMapObject();

        mapBasic.resize(1);
        mapBasic[0] = new ObImage(L"EnterTheGungeon/Level/Map_Basic.png");
        mapBasic[0]->scale = Vector2(1405.0f, 1432.0f);

        Spawn();
    }

    void Scene02::InitEnemy()
    {
        int idx = 0;
        float enemyScaleCoef = 3.0f;

        for (auto& elem : enemy)
        {
            elem = new Enemy;
            elem->col = new ObCircle;
            elem->col->scale.x = 16.0f * enemyScaleCoef;
            elem->col->scale.y = 16.0f * enemyScaleCoef;
            elem->col->color = Color(1.0f, 1.0f, 1.0f);
            elem->col->isFilled = false;
            elem->col->zOrder = ZOrder::object;

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
                elem2->zOrder = ZOrder::object;
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
                elem2->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
                elem2->SetParentRT(*elem->col);
                elem2->zOrder = ZOrder::object;
                idx++;
            }

            elem->hit = new ObImage(L"EnterTheGungeon/Enemy_0/Hit.png");
            elem->hit->isVisible = false;
            elem->hit->maxFrame.x = 1;
            elem->hit->scale.x = 16.0f * enemyScaleCoef;
            elem->hit->scale.y = 24.0f * enemyScaleCoef;
            elem->hit->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
            elem->hit->SetParentRT(*elem->col);
            elem->hit->zOrder = ZOrder::object;

            elem->die = new ObImage(L"EnterTheGungeon/Enemy_0/Die.png");
            elem->die->isVisible = false;
            elem->die->maxFrame.x = 5;
            elem->die->scale.x = 110.0f / 5.0f * enemyScaleCoef;
            elem->die->scale.y = 22.0f * enemyScaleCoef;
            elem->die->SetParentRT(*elem->col);
            elem->die->zOrder = ZOrder::object;


            float enemyWeaponScaleCoef = 1.5f;
            elem->weapon.resize(1);
            for (auto& weaponElem : elem->weapon)
            {
                weaponElem = new Weapon;
                weaponElem->col = new ObRect;
                weaponElem->col->isVisible = false;
                weaponElem->col->isFilled = false;
                weaponElem->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
                weaponElem->col->pivot = OFFSET_LB;
                weaponElem->col->scale.x = 29.0f * enemyWeaponScaleCoef;
                weaponElem->col->scale.y = 21.0f * enemyWeaponScaleCoef;
                weaponElem->col->SetParentRT(*elem->col);
                weaponElem->col->SetLocalPos(Vector2(10.0f, -15.0f));

                weaponElem->idle = new ObImage(L"EnterTheGungeon/Enemy_0/Weapon_0.png");
                weaponElem->idle->pivot = OFFSET_LB;
                weaponElem->idle->scale.x = 29.0f * enemyWeaponScaleCoef;
                weaponElem->idle->scale.y = 21.0f * enemyWeaponScaleCoef;
                weaponElem->idle->SetParentRT(*weaponElem->col);
                weaponElem->idle->zOrder = ZOrder::weapon;

                weaponElem->firePos = new GameObject;
                weaponElem->firePos->SetParentRT(*weaponElem->col);
                weaponElem->firePos->SetLocalPos(Vector2(weaponElem->col->scale.x / 2.0f, 0.0f));
                weaponElem->firePos->zOrder = ZOrder::none;

                float enemyWeaponEffectScaleCoef = 3.0f;
                weaponElem->fireEffect = new Effect;
                weaponElem->fireEffect->idle = new ObImage(L"EnterTheGungeon/Enemy_0/Effect_Fire_Weapon_0.png");
                weaponElem->fireEffect->idle->isVisible = false;
                weaponElem->fireEffect->idle->maxFrame.x = 3;
                weaponElem->fireEffect->idle->scale = Vector2(45.0f / 3.0f, 11.0f) * enemyWeaponEffectScaleCoef;
                weaponElem->fireEffect->idle->SetParentRT(*weaponElem->firePos);
                weaponElem->fireEffect->idle->zOrder = ZOrder::none;
                weaponElem->fireEffect->intervalDie = 0.2f;

                weaponElem->pivotDefault = Vector2(0.4f, 0.25f);
                weaponElem->localPosDefault = Vector2(18.0f, -15.0f);
                weaponElem->localFirePosDefault = Vector2(40.0f, 12.0f);
                weaponElem->Equip();
            }

            elem->shadow = new ObImage(L"EnterTheGungeon/Enemy_0/Shadow_1.png");
            elem->shadow->scale.x = 12.0f * enemyScaleCoef;
            elem->shadow->scale.y = 4.0f * enemyScaleCoef;
            elem->shadow->SetParentRT(*elem->col);
            elem->shadow->SetWorldPosY(-35.0f);
            elem->shadow->zOrder = ZOrder::shadow;
        }
    }

    void Scene02::InitBoss()
    {
        // 보스
        float bossScaleCoef = 3.0f;

        boss = new Boss;
        boss->curHp = boss->maxHp = 30;

        boss->col = new ObCircle;
        boss->col->isFilled = false;
        boss->col->scale.x = 25.0f * bossScaleCoef;
        boss->col->scale.y = 25.0f * bossScaleCoef;
        boss->col->color = Color(1.0f, 1.0f, 1.0f);
        boss->col->zOrder = ZOrder::object;

        boss->idle[dirB] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Front.png");
        boss->idle[dirL] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Front.png");
        boss->idle[dirR] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Front.png");
        boss->idle[dirLB] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Front.png");
        boss->idle[dirRB] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Front.png");
        boss->idle[dirT] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Back.png");
        boss->idle[dirLT] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Back.png");
        boss->idle[dirRT] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Back.png");

        int idx = 0;
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
            elem->zOrder = ZOrder::object;
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
            elem->maxFrame.x = 6;
            elem->scale.x = 180.0f / 6.0f * bossScaleCoef;
            elem->scale.y = 40.0f * bossScaleCoef;
            elem->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
            elem->SetParentRT(*boss->col);
            elem->zOrder = ZOrder::object;
            idx++;
        }

        boss->hit = new ObImage(L"EnterTheGungeon/Boss_0/Hit.png");
        boss->hit->isVisible = false;
        boss->hit->maxFrame.x = 1;
        boss->hit->scale.x = 32.0 * 1.0f * bossScaleCoef;
        boss->hit->scale.y = 40.0f * bossScaleCoef;
        boss->hit->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
        boss->hit->SetParentRT(*boss->col);
        boss->hit->zOrder = ZOrder::object;

        boss->die = new ObImage(L"EnterTheGungeon/Boss_0/Die.png");
        boss->die->isVisible = false;
        boss->die->maxFrame.x = 8;
        boss->die->scale.x = 320.0f / 8.0f * bossScaleCoef;
        boss->die->scale.y = 40.0f * bossScaleCoef;
        boss->die->SetParentRT(*boss->col);
        boss->die->zOrder = ZOrder::object;

        float bossWeaponScaleCoef = 2.0f;
        boss->weapon.resize(1);

        for (auto& elem : boss->weapon)
        {
            elem = new Weapon;
            elem->col = new ObRect;
            elem->col->isVisible = false;
            elem->col->isFilled = false;
            elem->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
            elem->col->pivot = OFFSET_LB;
            elem->col->scale.x = 29.0f * bossWeaponScaleCoef;
            elem->col->scale.y = 21.0f * bossWeaponScaleCoef;
            elem->col->SetParentRT(*boss->col);
            elem->col->SetLocalPos(Vector2(10.0f, -15.0f));

            elem->idle = new ObImage(L"EnterTheGungeon/Boss_0/Weapon_0.png");
            elem->idle->pivot = OFFSET_LB;
            elem->idle->scale.x = 43.0f * bossWeaponScaleCoef;
            elem->idle->scale.y = 11.0f * bossWeaponScaleCoef;
            elem->idle->SetParentRT(*elem->col);
            elem->idle->zOrder = ZOrder::weapon;

            elem->firePos = new GameObject;
            elem->firePos->SetParentRT(*elem->col);
            elem->firePos->SetLocalPos(Vector2(elem->col->scale.x / 2.0f, 0.0f));
            elem->firePos->zOrder = ZOrder::none;

            float bossWeaponEffectScaleCoef = 2.0f;
            elem->fireEffect = new Effect;
            elem->fireEffect->idle = new ObImage(L"EnterTheGungeon/Boss_0/Effect_Fire_Weapon_0.png");
            elem->fireEffect->idle->isVisible = false;
            elem->fireEffect->idle->maxFrame.x = 3;
            elem->fireEffect->idle->scale = Vector2(45.0f / 3.0f, 11.0f) * bossWeaponEffectScaleCoef;
            elem->fireEffect->idle->SetParentRT(*elem->firePos);
            elem->fireEffect->idle->zOrder = ZOrder::none;
            elem->fireEffect->intervalDie = 0.2f;

            elem->imgReloading = new ObImage(L"EnterTheGungeon/Boss_0/Weapon_0_reloading.png");
            elem->imgReloading->isVisible = false;
            elem->imgReloading->pivot = Vector2(0.4f, 0.25f);
            elem->imgReloading->maxFrame.x = 2;
            elem->imgReloading->scale.x = 42.0f / 2.0f * bossWeaponScaleCoef;
            elem->imgReloading->scale.y = 22.0f * bossWeaponScaleCoef;
            elem->imgReloading->SetParentRT(*elem->col);
            elem->imgReloading->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
            elem->imgReloading->zOrder = ZOrder::UI;

            elem->pivotDefault = Vector2(0.6f, 0.25f);
            elem->localPosDefault = Vector2(18.0f, -15.0f);
            elem->localFirePosDefault = Vector2(70.0f, 12.0f);
            elem->Equip();


            elem->uiBulletFrame = new UI;
            elem->uiBulletFrame->img = new ObImage(L"EnterTheGungeon/Boss_0/UI_Magazine.png");
            elem->uiBulletFrame->img->scale = Vector2(28.0f, 99.0f);
            elem->uiBulletFrame->anchor = Anchor::rightBottom;
            elem->uiBulletFrame->Spawn(-40.0f, 80.0f);
            elem->uiBulletFrame->img->space = Space::screen;
            elem->uiBulletFrame->img->zOrder = ZOrder::UI;
            elem->uiBulletFrame->img->isVisible = false;

            elem->bulletCount = 10;
            elem->uiBullet.resize(elem->bulletCount);

            int uiBulletIdx = 0;
            for (auto& elem : elem->uiBullet)
            {
                elem = new UI;
                elem->img = new ObImage(L"EnterTheGungeon/Boss_0/UI_Bullet.png");
                elem->img->scale = Vector2(12.0f, 4.0f);
                elem->anchor = Anchor::rightBottom;
                elem->Spawn(-40.0f, 104.0f - uiBulletIdx * 12.0f);
                elem->img->space = Space::screen;
                elem->img->isVisible = false;
                uiBulletIdx++;
            }

            elem->uiWeapon = new UI;
            elem->uiWeapon->img = new ObImage(L"EnterTheGungeon/Boss_0/UI_Weapon.png");
            elem->uiWeapon->img->pivot = Vector2(0.4f, 0.25f);
            elem->uiWeapon->img->scale.x = 60.0f;
            elem->uiWeapon->img->scale.y = 48.0f;
            elem->uiWeapon->anchor = Anchor::rightBottom;
            elem->uiWeapon->Spawn(-190.0f, 60.0f);
            elem->uiWeapon->img->space = Space::screen;
            elem->uiWeapon->img->zOrder = ZOrder::UI;
            elem->uiWeapon->img->isVisible = false;

            elem->uiBulletCount = new UI;
            elem->uiBulletCount->img = new ObImage(L"EnterTheGungeon/Boss_0/UI_BulletCount.png");
            elem->uiBulletCount->img->pivot = Vector2(0.4f, 0.25f);
            elem->uiBulletCount->img->scale.x = 60.0f;
            elem->uiBulletCount->img->scale.y = 28.0f;
            elem->uiBulletCount->anchor = Anchor::rightBottom;
            elem->uiBulletCount->Spawn(-140.0f, 150.0f);
            elem->uiBulletCount->img->space = Space::screen;
            elem->uiBulletCount->img->zOrder = ZOrder::UI;
            elem->uiBulletCount->img->isVisible = false;
        }


        float hpGuageCoef = 1.5f;

        boss->hpGuageBar = new UI;
        boss->hpGuageBar->img = new ObImage(L"EnterTheGungeon/Boss_0/Hp_GuageBar.png");
        boss->hpGuageBar->img->scale.x = 400.0f * hpGuageCoef;
        boss->hpGuageBar->img->scale.y = 30.0f * hpGuageCoef;
        boss->hpGuageBar->img->SetWorldPosX(-boss->hpGuageBar->img->scale.x / 2.0f);
        boss->hpGuageBar->img->SetWorldPosY(-app.GetHalfHeight() + 40.0f);
        boss->hpGuageBar->img->pivot = OFFSET_L;
        boss->hpGuageBar->img->space = Space::screen;
        boss->hpGuageBar->img->zOrder = ZOrder::UI;

        boss->hpGuage = new UI;
        boss->hpGuage->img = new ObImage(L"EnterTheGungeon/Boss_0/Hp_Guage.png");
        boss->hpGuage->imgSize.x = 330.0f * hpGuageCoef;
        boss->hpGuage->imgSize.y = 16.0f * hpGuageCoef;
        boss->hpGuage->img->scale.x = boss->hpGuage->imgSize.x;
        boss->hpGuage->img->scale.y = boss->hpGuage->imgSize.y;
        boss->hpGuage->img->SetWorldPosX(-boss->hpGuage->img->scale.x / 2.0f);
        boss->hpGuage->img->SetWorldPosY(-app.GetHalfHeight() + 40.0f);
        boss->hpGuage->img->pivot = OFFSET_L;
        boss->hpGuage->img->space = Space::screen;
        boss->hpGuage->img->zOrder = ZOrder::UI;

        boss->shadow = new ObImage(L"EnterTheGungeon/Boss_0/Shadow_1.png");
        boss->shadow->scale.x = 12.0f * bossScaleCoef * 2.0f;
        boss->shadow->scale.y = 4.0f * bossScaleCoef * 2.0f;
        boss->shadow->SetParentRT(*boss->col);
        boss->shadow->SetWorldPosY(-55.0f);
        boss->shadow->zOrder = ZOrder::shadow;
    }

    void Scene02::InitMapObject()
    {
        float doorOpenScaleCoef = 2.5f;

        int idx = 0;
        for (auto& elem : mapObj->doorOpenUp)
        {
            elem = new Obstacle;
            elem->col = new ObRect;
            elem->col->isFilled = false;
            elem->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
            elem->col->scale.x = 88.0f / 4.0f * doorOpenScaleCoef;
            elem->col->scale.y = 50.0f * doorOpenScaleCoef;
            elem->SetPosX(200.0f + idx * elem->col->scale.x);
            elem->SetPosY(0.0f);
            elem->col->collider = Collider::rect;
            elem->col->zOrder = ZOrder::object;

            elem->idle = new ObImage(L"EnterTheGungeon/Level/Door_Open_Up.png");
            elem->idle->maxFrame.x = 4;
            elem->idle->scale.x = 88.0f / 4.0f * doorOpenScaleCoef;
            elem->idle->scale.y = 50.0f * doorOpenScaleCoef;
            elem->idle->SetParentRT(*elem->col);
            elem->idle->ChangeAnim(ANIMSTATE::STOP, 0.1f);
            elem->idle->zOrder = ZOrder::object;

            if (idx & 1)
            {
                elem->idle->reverseLR = true;
            }

            elem->col->Update();

            idx++;
        }

        idx = 0;
        for (auto& elem : mapObj->doorOpenDown)
        {
            elem = new Obstacle;
            elem->col = new ObRect;
            elem->col->isVisible = false;   //
            elem->col->isFilled = false;
            elem->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
            elem->col->scale.x = 88.0f / 4.0f * doorOpenScaleCoef;
            elem->col->scale.y = 50.0f * doorOpenScaleCoef;
            elem->SetPosX(200.0f + idx * elem->col->scale.x);
            elem->SetPosY(0.0f);
            elem->col->collider = Collider::rect;
            elem->col->zOrder = ZOrder::object;

            elem->idle = new ObImage(L"EnterTheGungeon/Level/Door_Open_Down.png");
            elem->idle->isVisible = false;  //
            elem->idle->maxFrame.x = 4;
            elem->idle->scale.x = 88.0f / 4.0f * doorOpenScaleCoef;
            elem->idle->scale.y = 50.0f * doorOpenScaleCoef;
            elem->idle->SetParentRT(*elem->col);
            elem->idle->ChangeAnim(ANIMSTATE::STOP, 0.1f);
            elem->idle->zOrder = ZOrder::object;

            if (idx & 1)
            {
                elem->idle->reverseLR = true;
            }

            elem->col->Update();

            idx++;
        }

        float doorClosedScaleCoef = 2.5f;

        idx = 0;
        for (auto& elem : mapObj->doorClosed)
        {
            elem = new Obstacle;
            elem->col = new ObRect;
            elem->col->isVisible = true;
            elem->col->isFilled = false;
            elem->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
            elem->col->scale.x = 68.0f / 2.0f * doorClosedScaleCoef;
            elem->col->scale.y = 41.0f * doorClosedScaleCoef;
            elem->SetPosX(200.0f + idx * elem->col->scale.x);
            elem->SetPosY(200.0f);
            elem->col->collider = Collider::rect;
            elem->col->zOrder = ZOrder::object;

            elem->idle = new ObImage(L"EnterTheGungeon/Level/Door_Closed.png");
            elem->idle->maxFrame.x = 2;
            elem->idle->scale.x = 68.0f / 2.0f * doorClosedScaleCoef;
            elem->idle->scale.y = 41.0f * doorClosedScaleCoef;
            elem->idle->SetParentRT(*elem->col);
            elem->idle->ChangeAnim(ANIMSTATE::LOOP, 2.0f);
            elem->idle->zOrder = ZOrder::object;

            if (idx & 1)
            {
                elem->idle->reverseLR = true;
            }

            elem->col->Update();

            idx++;
        }
    }

    void Scene02::Spawn()
    {
        if (!mapGen) return;
        if (mapGen->roomsSelected.empty() == false)
        {
            room0Pos = mapGen->roomsSelected[0]->col->GetWorldPos();
        }

        CAM->position = room0Pos;
        CAM->coefScale = Vector3(1.0f, 1.0f, 1.0f);

        player->SetPosX(room0Pos.x - 10.0f);
        player->SetPosY(room0Pos.y + 0.0f);

        for (auto& elem : enemy)
        {
            elem->SetPosX(room0Pos.x + RANDOM->Float(-200.0f, 200.0f));
            elem->SetPosY(room0Pos.y + RANDOM->Float(-200.0f, 200.0f));
        }

        boss->SetPosX(room0Pos.x + 0.0f);
        boss->SetPosY(room0Pos.y + 200.0f);
    }

    void Scene02::Release()
    {
        mapObj->Release();
        for (auto& elem : enemy) elem->Release();
        player->Release();
        boss->Release();
    }

    void Scene02::Update()
    {
        if (INPUT->KeyDown('R'))
        {
            Release();
            Init();
        }

        if (mapGen)
        {
            mapGen->Update();
        }

        mapObj->Update();

        player->Update();

        for (auto& elem : enemy)
        {
            if (elem->state != State::die)
            {
                elem->targetPos = player->Pos();
                // elem->FindPath();
            }
            elem->Update();
        }

        if (boss->state != State::die)
        {
            boss->targetPos = player->Pos();
            boss->weapon[boss->curWeaponIdx]->col->rotation = Utility::DirToRadian(player->Pos());
        }
        boss->Update();

        if (INPUT->KeyDown('1'))
        {
            SCENE->ChangeScene("Scene01");
        }

        for(auto& elem : mapBasic) if (elem) elem->Update();
    }

    void Scene02::LateUpdate()
    {
        //for (auto& elem : mapGen->walls)
        //{
        //    if (elem &&
        //        elem->col->GetWorldPos().x > CAM->position.x - 1000.0f &&
        //        elem->col->GetWorldPos().x < CAM->position.x + 1000.0f &&
        //        elem->col->GetWorldPos().y > CAM->position.y - 1000.0f &&
        //        elem->col->GetWorldPos().y < CAM->position.y + 1000.0f)
        //    {
        //        if (elem->col->Intersect(player->col))
        //        {
        //            player->StepBack();
        //        }

        //        for (auto& enemyElem : enemy)
        //        {
        //            if (elem->col->Intersect(enemyElem->col))
        //            {
        //                enemyElem->StepBack();
        //            }
        //        }

        //        if (elem->col->Intersect(boss->col))
        //        {
        //            boss->StepBack();
        //        }
        //    }
        //}

        if (mapGen)
        {
            mapGen->LateUpdate();
        }

        int idx = 0;

        // 플레이어
        //if (CheckGrid(player->Pos()))
        //{
        //    player->StepBack();
        //}

        // 플레이어 총알
        for (auto& bulletElem : player->bullet)
        {
            for (auto& enemyElem : enemy)
            {
                if (enemyElem->state != State::die &&
                    bulletElem->col->Intersect(enemyElem->col))
                {
                    Vector2 dir = enemyElem->col->GetWorldPos() - bulletElem->col->GetWorldPos();
                    dir.Normalize();
                    enemyElem->Hit(bulletElem->damage, dir);
                    bulletElem->Hit(1);
                }
            }

            if (boss->state != State::die &&
                bulletElem->col->Intersect(boss->col))
            {
                boss->Hit(bulletElem->damage);
                bulletElem->Hit(1);
            }

            //if (CheckGrid(bulletElem->Pos()))
            //{
            //    bulletElem->Reload();
            //}
        }


        // 적
        for (auto& enemyElem : enemy)
        {
            if (false == player->godMode)
            {
                if (enemyElem->state != State::die &&
                    enemyElem->col->Intersect(player->col))
                {
                    player->Hit(1);
                }

                //if (CheckGrid(enemyElem->Pos()))
                //{
                //    enemyElem->StepBack();
                //}

                // 적 총알
                for (auto& bulletElem : enemyElem->bullet)
                {
                    if (bulletElem->col->Intersect(player->col))
                    {
                        player->Hit(bulletElem->damage);
                        bulletElem->Hit(1);
                    }

                    //if (CheckGrid(bulletElem->Pos()))
                    //{
                    //    bulletElem->Reload();
                    //}
                }
            }

            if (enemyElem->dropItem->col->Intersect(player->col))
            {
                enemyElem->dropItem->Hit();
                player->PlusMoney(1);
            }

            enemyElem->LateUpdate();
        }


        // 보스
        if (false == player->godMode)
        {
            if (boss->state != State::die &&
                boss->col->Intersect(player->col))
            {
                player->Hit(1);
            }

            //if (CheckGrid(boss->Pos()))
            //{
            //    boss->StepBack();
            //}

            // 보스 총알
            for (auto& bulletElem : boss->bullet)
            {
                if (bulletElem->col->Intersect(player->col))
                {
                    player->Hit(bulletElem->damage);
                    bulletElem->Hit(1);
                }

                //if (CheckGrid(bulletElem->Pos()))
                //{
                //    bulletElem->Reload();
                //}
            }
        }

        if (boss->dropItem->col->Intersect(player->col))
        {
            boss->dropItem->Hit();
            player->PlusMoney(1);
        }

        Weapon* bossWeapon = boss->weapon[boss->curWeaponIdx];
        if (bossWeapon->state != State::die &&
            bossWeapon->col->Intersect(player->col))
        {
            bossWeapon->Hit();
            player->EquipWeapon(bossWeapon);
        }

        boss->LateUpdate();


        // 맵 오브젝트
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

        player->LateUpdate();
    }

    void Scene02::Render()
    {
        if (mapGen)
        {
            mapGen->Render();
        }
        for (auto& elem : mapBasic) if (elem) elem->Render();

        player->shadow->Render();
        for (auto& elem : enemy) elem->shadow->Render();
        boss->shadow->Render();

        mapObj->Render();
        for (auto& elem : enemy) elem->Render();
        player->Render();
        boss->Render();

        // 최적화 이슈로 zorder 주석
        /*
        int size = RENDER->pq.size();
        while (false == RENDER->pq.empty())
        {
            RENDER->pq.top()->Render();
            RENDER->pq.pop();
        }
        */
    }

    void Scene02::ResizeScreen()
    {
        mapGen->ResizeScreen();

        player->ResizeScreen();

        boss->ResizeScreen();
    }

    //bool Scene02::CheckGrid(Vector2 wpos)
    //{
    //    int coef = gridMax / 2;
    //    int x = wpos.x + coef;
    //    int y = wpos.y + coef;
    //    return false == mapGen->grid[x][y];
    //}
}