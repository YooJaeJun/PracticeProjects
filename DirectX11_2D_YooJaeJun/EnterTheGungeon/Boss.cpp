#include "stdafx.h"

namespace Gungeon
{
    Boss::Boss()
    {
        Init();
    }

    void Boss::Init()
    {
        InitVar();
        InitSelf();
        InitWeapon();
        InitBullet();
        InitItem();
    }

    void Boss::InitVar()
    {
        pattern = BossPattern::string;

        col = new ObCircle;

        curHp = maxHp = 30;
        moveDir = Vector2(0.0f, 0.0f);
        scalar = 120.0f;
        timeFire = 0.0f;
        timeHit = 0.0f;
        isHit = false;
        isHitAnim = false;
        timeHitAnim = 0.0f;
        timeSpiral = 0.0f;
        flagSpiralRespawn = false;
        timeCluster = 0.0f;
        timeWave = 0.0f;
    }

    void Boss::InitSelf()
    {
        float bossScaleCoef = 3.0f;

        col->isFilled = false;
        col->scale.x = 25.0f * bossScaleCoef;
        col->scale.y = 25.0f * bossScaleCoef;
        col->color = Color(1.0f, 1.0f, 1.0f);
        col->zOrder = ZOrder::object;

        idle[dirB] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Front.png");
        idle[dirL] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Front.png");
        idle[dirR] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Front.png");
        idle[dirLB] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Front.png");
        idle[dirRB] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Front.png");
        idle[dirT] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Back.png");
        idle[dirLT] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Back.png");
        idle[dirRT] = new ObImage(L"EnterTheGungeon/Boss_0/Idle_Back.png");

        int idx = 0;
        for (auto& elem : idle)
        {
            if (idx == dirL || idx == dirLB || idx == dirLT)
            {
                elem->reverseLR = true;
            }
            elem->maxFrame.x = 4;
            elem->scale.x = 104.0f / 4.0f * bossScaleCoef;
            elem->scale.y = 40.0f * bossScaleCoef;
            elem->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
            elem->SetParentRT(*col);
            elem->zOrder = ZOrder::object;
            idx++;
        }

        walk[dirB] = new ObImage(L"EnterTheGungeon/Boss_0/Walk_Front.png");
        walk[dirL] = new ObImage(L"EnterTheGungeon/Boss_0/Walk_Front.png");
        walk[dirR] = new ObImage(L"EnterTheGungeon/Boss_0/Walk_Front.png");
        walk[dirLB] = new ObImage(L"EnterTheGungeon/Boss_0/Walk_Front.png");
        walk[dirRB] = new ObImage(L"EnterTheGungeon/Boss_0/Walk_Front.png");
        walk[dirT] = new ObImage(L"EnterTheGungeon/Boss_0/Walk_Back.png");
        walk[dirLT] = new ObImage(L"EnterTheGungeon/Boss_0/Walk_Back.png");
        walk[dirRT] = new ObImage(L"EnterTheGungeon/Boss_0/Walk_Back.png");

        idx = 0;
        for (auto& elem : walk)
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
            elem->SetParentRT(*col);
            elem->zOrder = ZOrder::object;
            idx++;
        }

        hit = new ObImage(L"EnterTheGungeon/Boss_0/Hit.png");
        hit->isVisible = false;
        hit->maxFrame.x = 1;
        hit->scale.x = 32.0 * 1.0f * bossScaleCoef;
        hit->scale.y = 40.0f * bossScaleCoef;
        hit->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
        hit->SetParentRT(*col);
        hit->zOrder = ZOrder::object;

        die = new ObImage(L"EnterTheGungeon/Boss_0/Die.png");
        die->isVisible = false;
        die->maxFrame.x = 8;
        die->scale.x = 320.0f / 8.0f * bossScaleCoef;
        die->scale.y = 40.0f * bossScaleCoef;
        die->SetParentRT(*col);
        die->zOrder = ZOrder::object;

        colTile = new ObRect;
        colTile->scale = Vector2(col->scale.x, col->scale.y / 2.0f);
        colTile->SetParentRT(*col);
        colTile->SetLocalPosY(col->GetWorldPos().y - col->scale.y / 2.0f);
        colTile->isFilled = false;
        colTile->color = Color(1.0f, 1.0f, 1.0f, 1.0f);


        float hpGuageCoef = 1.5f;

        hpGuageBar = new UI;
        hpGuageBar->img = new ObImage(L"EnterTheGungeon/Boss_0/Hp_GuageBar.png");
        hpGuageBar->img->scale.x = 400.0f * hpGuageCoef;
        hpGuageBar->img->scale.y = 30.0f * hpGuageCoef;
        hpGuageBar->img->SetWorldPosX(-hpGuageBar->img->scale.x / 2.0f);
        hpGuageBar->img->SetWorldPosY(-app.GetHalfHeight() + 40.0f);
        hpGuageBar->img->pivot = OFFSET_L;
        hpGuageBar->img->space = Space::screen;
        hpGuageBar->img->zOrder = ZOrder::UI;

        hpGuage = new UI;
        hpGuage->img = new ObImage(L"EnterTheGungeon/Boss_0/Hp_Guage.png");
        hpGuage->imgSize.x = 330.0f * hpGuageCoef;
        hpGuage->imgSize.y = 16.0f * hpGuageCoef;
        hpGuage->img->scale.x = hpGuage->imgSize.x;
        hpGuage->img->scale.y = hpGuage->imgSize.y;
        hpGuage->img->SetWorldPosX(-hpGuage->img->scale.x / 2.0f);
        hpGuage->img->SetWorldPosY(-app.GetHalfHeight() + 40.0f);
        hpGuage->img->pivot = OFFSET_L;
        hpGuage->img->space = Space::screen;
        hpGuage->img->zOrder = ZOrder::UI;

        shadow = new ObImage(L"EnterTheGungeon/Boss_0/Shadow_1.png");
        shadow->scale.x = 12.0f * bossScaleCoef * 2.0f;
        shadow->scale.y = 4.0f * bossScaleCoef * 2.0f;
        shadow->SetParentRT(*col);
        shadow->SetWorldPosY(-55.0f);
        shadow->zOrder = ZOrder::shadow;
    }

    void Boss::InitWeapon()
    {
        weapon = new WeaponData;
        w = weapon->data[1];

        w->col->SetParentRT(*col);
        w->col->SetLocalPos(Vector2(10.0f, -15.0f));

        w->idle->SetParentRT(*w->col);

        w->firePos->SetLocalPos(Vector2(w->col->scale.x / 2.0f, 0.0f));

        w->fireEffect->idle->SetParentRT(*w->firePos);

        w->imgReloading->SetParentRT(*w->col);

        w->Equip();
    }

    void Boss::InitBullet()
    {
        switch (pattern)
        {
        case Gungeon::BossPattern::circular:
            InitCircular();
            break;
        case Gungeon::BossPattern::string:
            InitString();
            break;
        case Gungeon::BossPattern::shield:
            InitShield();
            break;
        case Gungeon::BossPattern::spiral:
            InitSpiral();
            break;
        case Gungeon::BossPattern::cluster:
            InitCluster();
            break;
        case Gungeon::BossPattern::wave:
            InitWave();
            break;
        }//switch
    }

    void Boss::InitItem()
    {
        float itemCoef = 0.5f;
        dropItem = new Item;
        dropItem->col = new ObCircle;
        dropItem->col->scale = Vector2(40.0f, 40.0f) * itemCoef;
        dropItem->col->isVisible = false;
        dropItem->col->isFilled = false;
        dropItem->col->SetWorldPos(DEFAULTSPAWN);
        dropItem->idle = new ObImage(L"EnterTheGungeon/Player_0/UI_Gold.png");
        dropItem->idle->scale = Vector2(40.0f, 40.0f) * itemCoef;
        dropItem->idle->SetParentRT(*dropItem->col);
        dropItem->idle->isVisible = false;
    }

    void Boss::Release()
    {
        Unit::Release();
        w->Release();
        SafeDelete(hpGuage);
        SafeDelete(hpGuageBar);
    }

    void Boss::Update()
    {
        Unit::Update();

        int curPattern = static_cast<int>(pattern);
        if (ImGui::SliderInt("Boss Pattern", &curPattern, 0, patternMax))
        {
            ChangePattern(curPattern);
            InitBullet();
        }
        
        Weapon* w = weapon->data[1];
        bulletSpawnPos = w->firePos->GetWorldPos();
        bulletSpawnDir = w->moveDir;

        switch (state)
        {
        case State::idle:
            Idle();
            for (auto& elem : bullet) elem->Update();
            break;
        case State::walk:
            Walk();
            for (auto& elem : bullet) elem->Update();
            break;
        case State::die:
            Die();
            break;
        }

        w->Update();
        hpGuageBar->Update();
        hpGuage->Update();
        dropItem->Update();
    }

    void Boss::LateUpdate()
    {
    }

    void Boss::Render()
    {
        Unit::Render();
        switch (state)
        {
        case State::idle:
            for (auto& elem : bullet) elem->Render();
            break;
        case State::walk:
            for (auto& elem : bullet) elem->Render();
            break;
        case State::die:
            break;
        }

        w->Render();
        hpGuageBar->Render();
        hpGuage->Render();
        dropItem->Render();
    }

    void Boss::ResizeScreen()
    {
        hpGuageBar->img->SetWorldPosX(-hpGuageBar->img->scale.x / 2.0f);
        hpGuageBar->img->SetWorldPosY(-app.GetHalfHeight() + 40.0f);
        hpGuage->img->SetWorldPosX(-hpGuage->img->scale.x / 2.0f);
        hpGuage->img->SetWorldPosY(-app.GetHalfHeight() + 40.0f);
    }

    void Boss::Idle()
    {
        Unit::SetTarget(w);

        if (false == isHit)
        {
            StartWalk();
        }

        Hitting();
        UpdateBullet();
    }

    void Boss::Walk()
    {
        Unit::SetTarget(w);

        if (false == isHit)
        {
            StartIdle();
        }

        Hitting();
        UpdateBullet();
    }

    void Boss::Die()
    {
        Unit::Die();

        for (auto& elem : bullet)
        {
            elem->col->colOnOff = false;
            elem->col->isVisible = false;
            elem->idle->colOnOff = false;
            elem->idle->isVisible = false;
        }
    }

    void Boss::StartWalk()
    {
        if (almostEqualVector2(lastPos, col->GetWorldPos()))
        {
            idle[curTargetDirState]->isVisible = true;
            for (auto& elem : walk) elem->isVisible = false;
        }
        else
        {
            state = State::walk;
            for (auto& elem : idle) elem->isVisible = false;
            walk[curTargetDirState]->isVisible = true;
        }
    }

    void Boss::StartIdle()
    {
        if (almostEqualVector2(lastPos, col->GetWorldPos()))
        {
            state = State::idle;
            idle[curTargetDirState]->isVisible = true;
            for (auto& elem : walk) elem->isVisible = false;
        }
        else
        {
            for (auto& elem : idle) elem->isVisible = false;
            walk[curTargetDirState]->isVisible = true;
        }
    }

    void Boss::Hit(const int damage, const Vector2& dir)
    {
        pushedDir = dir;

        Unit::Hit(damage);

        hit->ChangeAnim(ANIMSTATE::ONCE, 0.1f);

        if (pushedDir.x < 0.0f)
        {
            hit->reverseLR = true;
        }
        else
        {
            hit->reverseLR = false;
        }
    }

    void Boss::Hitting()
    {
        if (isHit)
        {
            if (curHp <= 0.0f)
            {
                curHp = 0.0f;
                hpGuageBar->img->isVisible = false;
                hpGuage->img->isVisible = false;
                StartDie();
            }
            else
            {
                hpGuage->img->scale.x = (float)curHp / maxHp * hpGuage->imgSize.x;
                hpGuage->img->uv.z = hpGuage->img->scale.x / hpGuage->imgSize.x;
            }

            if (TIMER->GetTick(timeHit, 0.01f))
            {
                isHit = false;
            }
        }

        if (isHitAnim)
        {
            Color c = Color(RANDOM->Float(0.6f, 1.0f), 0.5f, 0.5f, RANDOM->Float(0.2f, 1.0f));
            for (auto& elem : idle) elem->color = c;
            for (auto& elem : walk) elem->color = c;
            hit->color = c;

            SetPosX(Pos().x + RANDOM->Float(-1.0f, 1.0f));
            SetPosY(Pos().y + RANDOM->Float(-1.0f, 1.0f));

            for (auto& elem : idle) elem->isVisible = false;
            for (auto& elem : walk) elem->isVisible = false;
            hit->isVisible = true;

            if (TIMER->GetTick(timeHitAnim, 0.4f))
            {
                Color c = Color(0.5f, 0.5f, 0.5f, 1.0f);
                for (auto& elem : idle) elem->color = c;
                for (auto& elem : walk) elem->color = c;
                hit->color = c;
                die->color = c;

                walk[curTargetDirState]->isVisible = true;
                hit->isVisible = false;

                isHitAnim = false;

                pushedDir = Vector2(0.0f, 0.0f);
            }
        }
        else
        {
            idle[curTargetDirState]->color.w = 1.0f;
            walk[curTargetDirState]->color.w = 1.0f;
            hit->isVisible = false;
        }
    }

    void Boss::StartDie()
    {
        Unit::StartDie();

        w->col->isVisible = false;
        w->idle->isVisible = false;
        w->firePos->isVisible = false;

        hpGuageBar->img->isVisible = false;
        hpGuage->img->isVisible = false;

        for (auto& elem : bullet)
        {
            elem->col->colOnOff = false;
            elem->idle->colOnOff = false;
            elem->hitBomb->idle->colOnOff = false;
        }

        // drop
        dropItem->Spawn(Vector2(Pos().x - 10.0f, Pos().y - 10.0f));
        dropItem->col->isVisible = true;
        dropItem->idle->isVisible = true;
        dropItem->state = State::idle;

        w->Spawn(Pos());
        w->col->isVisible = true;
        w->idle->isVisible = true;
        w->state = State::idle;
    }


    /// <summary>
    /// Pattern
    /// </summary>

    void Boss::ChangePattern(const int curPattern)
    {
        pattern = static_cast<BossPattern>(curPattern);
        for (auto& elem : bullet)
        {
            elem->moveDir = Vector2(0.0f, 0.0f);
            elem->scalar = 120.0f;
            elem->col->rotation = 0.0f;
            elem->col->rotation2 = 0.0f;
            elem->col->SetWorldPos(DEFAULTSPAWN);
            elem->idle->color = Color(0.5f, 0.5f, 0.5f);
        }
    }

    void Boss::InitCircular()
    {
        bullet.resize(circularMax);

        int idx = 0;
        for (auto& elem : bullet)
        {
            if (nullptr == elem) elem = new BossBullet;
            elem->moveDir.x = cos(idx * 360.0f / circularMax * ToRadian);
            elem->moveDir.y = sin(idx * 360.0f / circularMax * ToRadian);
            elem->scalar = 250.0f;
            idx++;
        }
    }

    void Boss::InitString()
    {
        if (stringBullet.inputString == "")
        {
            stringBullet.inputString = "Yoo Jae Jun";
        }
        stringBullet.coefMidForTarget = 0.0f;
        stringBullet.SetStringBullet();
        bullet.resize(stringBullet.inputString.size() * 25);

        int size = stringBullet.inputString.size();
        float coefAngle = w->col->rotation - stringBullet.coefMidForTarget;

        for (int r = 0; r < 5; r++)
        {
            for (int c = 0; c < 5; c++)
            {
                for (int i = 0; i < size; i++)
                {
                    int idx = i * 25 + r * 5 + c;
                    if (nullptr == bullet[idx]) bullet[idx] = new BossBullet;

                    if (stringBullet.outputAlphbets[i][r][c])
                    {
                        bullet[idx]->scalar = 200.0f + (r + 10.0f) * 15.0f;
                        bullet[idx]->angle = PI * 2 * (c + 1) / 5;
                    }
                }
            }
        }
    }

    void Boss::InitShield()
    {
        bullet.resize(shieldMax);

        int idx = 0;
        for (auto& elem : bullet)
        {
            if (nullptr == elem) elem = new BossBullet;
            elem->col->SetLocalPos(Vector2(80.0f + idx * 2.0f, 80.0f + idx * 2.0f));
            elem->scalar = (idx + 1) * 3.0f;
            elem->idle->color = Color(1.0f, 0.7f, 0.0f);
            idx++;
        }
    }

    void Boss::InitSpiral()
    {
        curSpiralIdx = 0;
        bullet.resize(spiralMax);

        int idx = 0;
        for (auto& elem : bullet)
        {
            if (nullptr == elem) elem = new BossBullet;
            elem->scalar = 100.0f + (idx + 10.0f) * 5.0f;
            elem->moveDir = Vector2(cos(idx * 360.0f / spiralMax * ToRadian), sin(idx * 360.0f / spiralMax * ToRadian));
            idx++;
        }
    }

    void Boss::InitCluster()
    {
        bullet.resize(clusterMax);

        int idx = 0;
        for (auto& elem : bullet)
        {
            if (nullptr == elem) elem = new BossBullet;
            elem->scalar = 200.0f;
            idx++;
        }
    }

    void Boss::InitWave()
    {
        bullet.resize(waveMax);

        int idx = 0;
        for (auto& elem : bullet)
        {
            if (nullptr == elem) elem = new BossBullet;
            elem->col->SetLocalPos(Vector2(80.0f + idx * 2.0f, 80.0f + idx * 2.0f));
            elem->scalar = (idx + 1) * 3.0f;
            elem->moveDir = Vector2(cos(idx * 6.0f * ToRadian), sin(idx * 6.0f * ToRadian));
            idx++;
        }
    }


    void Boss::UpdateBullet()
    {
        switch (pattern)
        {
        case Gungeon::BossPattern::circular:
            UpdateCircular();
            break;
        case Gungeon::BossPattern::string:
            UpdateString();
            break;
        case Gungeon::BossPattern::shield:
            UpdateShield();
            break;
        case Gungeon::BossPattern::spiral:
            UpdateSpiral();
            break;
        case Gungeon::BossPattern::cluster:
            UpdateCluster();
            break;
        case Gungeon::BossPattern::wave:
            UpdateWave();
            break;
        }
    }

    void Boss::UpdateCircular()
    {
        if (TIMER->GetTick(timeFire, 2.0f))
        {
            for (auto& elem : bullet)
            {
                elem->Spawn(bulletSpawnPos);
            }
        }
    }

    void Boss::UpdateString()
    {
        int size = stringBullet.inputString.size();
        char* s = const_cast<char*>(stringBullet.inputString.c_str());

        if (ImGui::InputText("String Danmaku", s, 26))
        {
            stringBullet.inputString = s;
            size = stringBullet.inputString.size();
            bullet = vector<Bullet*>(size * 25);
            InitBullet();
            stringBullet.SetStringBullet();
        }

        float coefAngle = w->col->rotation - stringBullet.coefMidForTarget;
        for (int r = 0; r < 5; r++)
        {
            for (int c = 0; c < 5; c++)
            {
                for (int i = 0; i < size; i++)
                {
                    if (stringBullet.outputAlphbets[i][r][c])
                    {
                        int idx = i * 25 + r * 5 + c;
                        bullet[idx]->atkAngle = (bullet[idx]->angle / 60.0f) + (0.2f * i) + coefAngle;
                        bullet[idx]->moveDir = Vector2(cos(bullet[idx]->atkAngle), sin(bullet[idx]->atkAngle));
                    }
                }
            }
        }

        if (TIMER->GetTick(timeFire, 1.5f))
        {
            for (auto& elem : bullet)
            {
                if (elem->moveDir.x == 0.0f && elem->moveDir.y == 0.0f) continue;

                elem->Spawn(bulletSpawnPos);
            }
        }
    }

    void Boss::UpdateShield()
    {
        int idx = 0;
        for (auto& elem : bullet)
        {
            // 테스트 때문에 임시로 Update에 넣음. 최초 패턴 설정 시 init 시기에 col이 없어서.
            if (col && nullptr == elem->col->GetParent())
            {
                elem->col->SetParentRT(*col);
            }
            elem->col->SetLocalPos(Vector2(80.0f + idx * 2.0f, 80.0f + idx * 2.0f));
            elem->col->rotation += 3.0f * idx * ToRadian * DELTA;
            elem->col->rotation2 += 3.0f * idx * ToRadian * DELTA;
            idx++;
        }
    }

    void Boss::UpdateSpiral()
    {
        int idx = 0;
        bullet[curSpiralIdx]->Spawn(bulletSpawnPos);

        if (TIMER->GetTick(timeSpiral, 0.05f))
        {
            curSpiralIdx++;
            if (curSpiralIdx >= spiralMax)
            {
                curSpiralIdx = 0;
            }
        }
    }

    void Boss::UpdateCluster()
    {
        if (TIMER->GetTick(timeCluster, 1.0f))
        {
            for (auto& elem : bullet)
            {
                elem->moveDir.x = min(targetDir.x + RANDOM->Float(0.0f, 0.1f), 1.0f);
                elem->moveDir.y = min(targetDir.y + RANDOM->Float(0.0f, 0.1f), 1.0f);
                elem->Spawn(bulletSpawnPos);
            }
        }

        for (auto& elem : bullet)
        {
            elem->scalar = RANDOM->Float(200.0f, 700.0f);
        }
    }
    void Boss::UpdateWave()
    {
        if (TIMER->GetTick(timeWave, 2.0f))
        {
            int idx = 0;
            for (auto& elem : bullet)
            {
                elem->Spawn(bulletSpawnPos);
                idx++;
            }
        }
    }
}