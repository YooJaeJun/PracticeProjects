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
        InitBullet();
        InitItem();
    }

    void Boss::InitVar()
    {
        pattern = BossPattern::string;

        curHp = maxHp = 1;
        scalar = 30.0f;
        timeFire = 0.0f;
        timeHit = 0.0f;
        isHit = false;
        isHitAnim = false;
        timeHitAnim = 0.0f;
        timeTornado = 0.0f;
        timeTornadoOne = 0.0f;
        flagTornadoRespawn = false;
        timeRand = 0.0f;
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
        case Gungeon::BossPattern::storm:
            InitStorm();
            break;
        case Gungeon::BossPattern::tornado:
            InitTornado();
            break;
        case Gungeon::BossPattern::rand:
            InitRand();
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
        SafeDelete(hpGuage);
        SafeDelete(hpGuageBar);
    }

    void Boss::Update()
    {
        Unit::Update();

        int tempPattern = static_cast<int>(pattern);
        if (ImGui::SliderInt("Boss Pattern", &tempPattern, 0, patternMax))
        {
            pattern = static_cast<BossPattern>(tempPattern);
            InitBullet();
        }

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
        for (auto& elem : bullet) elem->Render();
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
        Unit::SetTarget();

        if (false == isHit)
        {
            StartWalk();
        }

        Hitting();
        UpdateBullet();
    }

    void Boss::Walk()
    {
        Unit::SetTarget();

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
        if (moveDir.x == 0.0f && moveDir.y == 0.0f)
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
        if (moveDir.x == 0.0f && moveDir.y == 0.0f)
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

    void Boss::Hit(const int damage)
    {
        Unit::Hit(damage);
        if (false == isHit)
        {
            hit->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
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

        hpGuageBar->img->isVisible = false;
        hpGuage->img->isVisible = false;

        for (auto& elem : bullet)
        {
            elem->col->colOnOff = false;
            elem->col->isVisible = false;
            elem->idle->colOnOff = false;
            elem->idle->isVisible = false;
            elem->hitBomb->idle->isVisible = false;
        }

        // drop
        dropItem->Spawn(Vector2(Pos().x - 10.0f, Pos().y - 10.0f));
        dropItem->col->isVisible = true;
        dropItem->idle->isVisible = true;
        dropItem->state = State::idle;

        weapon[curWeaponIdx]->Spawn(Pos());
        weapon[curWeaponIdx]->col->isVisible = true;
        weapon[curWeaponIdx]->idle->isVisible = true;
        weapon[curWeaponIdx]->state = State::idle;
    }


    /// <summary>
    /// Pattern
    /// </summary>

    void Boss::InitCircular()
    {
        moveDir = Vector2(0.0f, 0.0f);

        bullet.resize(circularMax);

        int idx = 0;
        for (auto& elem : bullet)
        {
            elem = new BossBullet;
            elem->col = new ObCircle;
            InitBulletOne(elem);
            elem->moveDir.x = cos(idx * 360.0f / circularMax * ToRadian);
            elem->moveDir.y = sin(idx * 360.0f / circularMax * ToRadian);
            idx++;
        }
    }

    void Boss::InitString()
    {
        moveDir = Vector2(0.0f, 0.0f);

        if (stringBullet.inputString == "")
        {
            stringBullet.inputString = "abcdefghijklmnopqrstuvwxyz";
        }
        stringBullet.coefMidForTarget = 0.0f;
        stringBullet.SetStringBullet();
        bullet.resize(stringBullet.inputString.size() * 25);

        for (auto& elem : bullet)
        {
            elem = new BossBullet;
            elem->col = new ObCircle;
            InitBulletOne(elem);
        }
    }

    void Boss::InitStorm()
    {
        bullet.resize(stormMax);
        scalar = 100.0f;

        int idx = 0;
        for (auto& elem : bullet)
        {
            elem = new BossBullet;
            elem->col = new ObCircle;
            InitBulletOne(elem);
            elem->col->SetLocalPos(Vector2(80.0f + idx * 2.0f, 80.0f + idx * 2.0f));
            elem->scalar = (idx + 1) * 3.0f;
            idx++;
        }
    }

    void Boss::InitTornado()
    {
        moveDir = Vector2(0.0f, 0.0f);

        bullet.resize(tornadoMax);
        scalar = 300.0f;

        int idx = 0;
        for (auto& elem : bullet)
        {
            elem = new BossBullet;
            elem->col = new ObCircle;
            InitBulletOne(elem);
            elem->scalar = 100.0f + (idx + 10.0f) * 5.0f;
            elem->moveDir = Vector2(cos(idx * 6.0f * ToRadian), sin(idx * 6.0f * ToRadian));
            idx++;
        }
    }

    void Boss::InitRand()
    {
        moveDir = Vector2(0.0f, 0.0f);

        bullet.resize(randMax);
        scalar = 300.0f;

        int idx = 0;
        for (auto& elem : bullet)
        {
            elem = new BossBullet;
            elem->col = new ObCircle;
            InitBulletOne(elem);
            elem->scalar = 200.0f;
            idx++;
        }
    }

    void Boss::InitBulletOne(BossBullet* elem)
    {
        float bulletCoef = 4.0f;
        elem->col->scale = Vector2(8.0f * bulletCoef, 8.0f * bulletCoef);
        elem->col->isFilled = false;
        elem->col->SetWorldPos(DEFAULTSPAWN);
        elem->idle = new ObImage(L"EnterTheGungeon/Boss_0/Bullet_0.png");
        elem->idle->scale = elem->col->scale;
        elem->idle->SetParentRT(*elem->col);
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
        case Gungeon::BossPattern::storm:
            UpdateStorm();
            break;
        case Gungeon::BossPattern::tornado:
            UpdateTornado();
            break;
        case Gungeon::BossPattern::rand:
            UpdateRand();
            break;
        }
    }

    void Boss::UpdateCircular()
    {
        if (TIMER->GetTick(timeFire, 3.0f))
        {
            for (auto& elem : bullet)
            {
                elem->Spawn(weapon[curWeaponIdx]->firePos->GetWorldPos());
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
            bullet = vector<BossBullet*>(size * 25);
            InitBullet();
            stringBullet.SetStringBullet();
        }

        if (TIMER->GetTick(timeFire, 1.5f))
        {
            for (int r = 0; r < 5; r++)
            {
                for (int c = 0; c < 5; c++)
                {
                    for (int i = 0; i < size; i++)
                    {
                        if (stringBullet.outputAlphbets[i][r][c])
                        {
                            float angle = PI * 2 * (c + 1) / 5;
                            float atkAngle = (angle / 60.0f) + (0.2f * i) +
                                weapon[curWeaponIdx]->col->rotation - stringBullet.coefMidForTarget;
                            int idx = i * 25 + r * 5 + c;
                            bullet[idx]->moveDir = Vector2(cos(atkAngle), sin(atkAngle));
                            bullet[idx]->scalar = 250.0f + (r + 10.0f) * 10.0f;
                        }
                    }
                }
            }

            for (auto& elem : bullet)
            {
                if (elem->moveDir.x == 0.0f && elem->moveDir.y == 0.0f) continue;

                elem->Spawn(weapon[curWeaponIdx]->firePos->GetWorldPos());
            }
        }
    }

    void Boss::UpdateStorm()
    {
        moveDir = targetDir;
        SetMoveDirState();
        col->MoveWorldPos(moveDir * scalar * DELTA);

        int idx = 0;
        for (auto& elem : bullet)
        {
            if (col && nullptr == elem->col->GetParent())
            {
                elem->col->SetParentRT(*col);
            }
            elem->col->rotation += 3.0f * idx * ToRadian * DELTA;
            elem->col->rotation2 += 3.0f * idx * ToRadian * DELTA;
            idx++;
        }
    }

    void Boss::UpdateTornado()
    {
        if (TIMER->GetTick(timeTornadoOne, 0.05f))
        {
            flagTornadoRespawn = true;
            int idx = 0;
            for (auto& elem : bullet)
            {
                if (false == elem->isFired)
                {
                    elem->Spawn(weapon[curWeaponIdx]->firePos->GetWorldPos());
                    flagTornadoRespawn = false;
                    break;
                }
                idx++;
            }

            if (flagTornadoRespawn)
            {
                if (TIMER->GetTick(timeTornado, 0.1f))
                {
                    for (auto& elem : bullet)
                    {
                        elem->isFired = false;
                        elem->SetPos(DEFAULTSPAWN);
                    }
                }
            }
        }
    }

    void Boss::UpdateRand()
    {
        if (TIMER->GetTick(timeRand, 2.0f))
        {
            for (auto& elem : bullet)
            {
                elem->moveDir.x = min(targetDir.x + RANDOM->Float(0.0f, 0.1f), 1.0f);
                elem->moveDir.y = min(targetDir.y + RANDOM->Float(0.0f, 0.1f), 1.0f);
                elem->Spawn(weapon[curWeaponIdx]->firePos->GetWorldPos());
            }
        }

        for (auto& elem : bullet)
        {
            elem->scalar = RANDOM->Float(200.0f, 700.0f);
        }
    }
}