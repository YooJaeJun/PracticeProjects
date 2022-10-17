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
        InitBullet();
        InitItem();
    }

    void Boss::InitVar()
    {
        pattern = BossPattern::string;

        curHp = maxHp = 30;
        scalar = 120.0f;

        intervalIdle = 0.5f;
        intervalWalk = 0.5f;
        intervalAttack = 0.2f;
        intervalHit = 0.2f;
        intervalDie = 0.2f;
    }

    void Boss::InitSelf()
    {
        state = State::die;

        float scaleFactor = 3.0f;
        col = new ObCircle;
        col->isFilled = false;
        col->scale = Vector2(25.0f, 25.0f) * scaleFactor;
        col->color = Color(1.0f, 1.0f, 1.0f);
        SetPos(DEFAULTSPAWN);

        colTile = new ObRect;
        colTile->scale = Vector2(col->scale.x, col->scale.y / 2.0f);
        colTile->SetParentRT(*col);
        colTile->SetLocalPosY(col->GetWorldPos().y - col->scale.y / 2.0f);
        colTile->isFilled = false;
        colTile->color = Color(1.0f, 1.0f, 1.0f, 1.0f);

        idle = new ObImage(L"EnterTheGungeon/Boss_1/Idle.png");
        idle->isVisible = true;
        idle->maxFrame = Int2(2, 8);
        idle->scale = Vector2(80.0f / 2.0f, 352.0f / 8.0f) * scaleFactor;
        idle->ChangeAnim(AnimState::loop, intervalIdle);
        idle->SetParentRT(*col);

        walk = new ObImage(L"EnterTheGungeon/Boss_1/Walk.png");
        walk->isVisible = false;
        walk->maxFrame = Int2(2, 8);
        walk->scale = Vector2(80.0f / 2.0f, 352.0f / 8.0f) * scaleFactor;
        walk->ChangeAnim(AnimState::loop, intervalWalk);
        walk->SetParentRT(*col);

        attack = new ObImage(L"EnterTheGungeon/Boss_1/Attack_2.png");
        attack->isVisible = false;
        attack->maxFrame.x = 2;
        attack->scale = Vector2(80.0f / 2.0f, 44.0f) * scaleFactor;
        attack->ChangeAnim(AnimState::loop, intervalHit);
        attack->SetParentRT(*col);

        hit = new ObImage(L"EnterTheGungeon/Boss_1/Hit.png");
        hit->isVisible = false;
        hit->maxFrame.x = 2;
        hit->scale = Vector2(72.0 / 2.0f, 38.0f) * scaleFactor;
        hit->ChangeAnim(AnimState::loop, intervalHit);
        hit->SetParentRT(*col);

        die = new ObImage(L"EnterTheGungeon/Boss_1/Die.png");
        die->isVisible = false;
        die->maxFrame.x = 2;
        die->scale = Vector2(72.0f / 2.0f, 40.0f) * scaleFactor;
        die->ChangeAnim(AnimState::loop, intervalDie);
        die->SetParentRT(*col);

        chairIdle = new ObImage(L"EnterTheGungeon/Boss_1/Chair_Idle.png");
        chairIdle->isVisible = true;
        chairIdle->maxFrame = Int2(2, 8);
        chairIdle->scale = Vector2(168.0f / 2.0f, 616.0f / 8.0f) * scaleFactor;
        chairIdle->ChangeAnim(AnimState::loop, 0.5f);
        chairIdle->SetParentRT(*col);

        chairWalk = new ObImage(L"EnterTheGungeon/Boss_1/Chair_Walk.png");
        chairWalk->isVisible = false;
        chairWalk->maxFrame = Int2(2, 8);
        chairWalk->scale = Vector2(168.0f / 2.0f, 616.0f / 8.0f) * scaleFactor;
        chairWalk->ChangeAnim(AnimState::loop, 0.5f);
        chairWalk->SetParentRT(*col);

        chairAttack1Start = new ObImage(L"EnterTheGungeon/Boss_1/Chair_Attack_1_Start.png");
        chairAttack1Start->isVisible = false;
        chairAttack1Start->maxFrame.x = 1;
        chairAttack1Start->scale = Vector2(64.0f, 78.0f) * scaleFactor;
        chairAttack1Start->ChangeAnim(AnimState::once, 0.2f);
        chairAttack1Start->SetParentRT(*col);

        chairAttack1 = new ObImage(L"EnterTheGungeon/Boss_1/Chair_Attack_1.png");
        chairAttack1->isVisible = false;
        chairAttack1->maxFrame.x = 2;
        chairAttack1->scale = Vector2(120.0f / 2.0f, 74.0f) * scaleFactor;
        chairAttack1->ChangeAnim(AnimState::loop, 0.05f);
        chairAttack1->SetParentRT(*col);

        chairAttack2 = new ObImage(L"EnterTheGungeon/Boss_1/Chair_Attack_2.png");
        chairAttack2->isVisible = false;
        chairAttack2->maxFrame.x = 3;
        chairAttack2->scale = Vector2(204.0f / 3.0f, 79.0f) * scaleFactor;
        chairAttack2->ChangeAnim(AnimState::loop, 0.2f);
        chairAttack2->SetParentRT(*col);

        chairDie = new ObImage(L"EnterTheGungeon/Boss_1/Chair_Die.png");
        chairDie->isVisible = false;
        chairDie->maxFrame.x = 1;
        chairDie->scale = Vector2(73.0f, 75.0f) * scaleFactor;
        chairDie->ChangeAnim(AnimState::once, 0.2f);
        chairDie->SetParentRT(*col);

        firePos = new ObCircle;
        firePos->isVisible = true;
        firePos->scale = Vector2(20.0f, 20.0f);
        firePos->isFilled = false;
        firePos->color = Color(1.0f, 1.0f, 1.0f);
        firePos->SetParentRT(*col);
        firePos->SetLocalPos(Vector2(100.0f, 0.0f));


        float shadowScaleFactor = scaleFactor * 2.0f;
        shadow = new ObImage(L"EnterTheGungeon/boss_1/Shadow_1.png");
        shadow->scale = Vector2(12.0f, 4.0f) * shadowScaleFactor;
        shadow->SetParentRT(*col);
        shadow->SetWorldPosY(-55.0f);
        shadow->zOrder = ZOrder::shadow;

        float hpGuageFactor = 1.5f;

        hpGuageBar = new UI;
        hpGuageBar->img = new ObImage(L"EnterTheGungeon/boss_1/Hp_GuageBar.png");
        hpGuageBar->img->scale = Vector2(400.0f, 30.0f) * hpGuageFactor;
        hpGuageBar->img->SetWorldPosX(-hpGuageBar->img->scale.x / 2.0f);
        hpGuageBar->img->SetWorldPosY(-app.GetHalfHeight() + 40.0f);
        hpGuageBar->img->pivot = OFFSET_L;
        hpGuageBar->img->space = Space::screen;
        hpGuageBar->img->zOrder = ZOrder::UI;

        hpGuage = new UI;
        hpGuage->img = new ObImage(L"EnterTheGungeon/boss_1/Hp_Guage.png");
        hpGuage->imgSize.x = 330.0f * hpGuageFactor;
        hpGuage->imgSize.y = 16.0f * hpGuageFactor;
        hpGuage->img->scale = Vector2(330.0f, 16.0f) * hpGuageFactor;
        hpGuage->img->SetWorldPosX(-hpGuage->img->scale.x / 2.0f);
        hpGuage->img->SetWorldPosY(-app.GetHalfHeight() + 40.0f);
        hpGuage->img->pivot = OFFSET_L;
        hpGuage->img->space = Space::screen;
        hpGuage->img->zOrder = ZOrder::UI;
    }

    void Boss::InitBullet()
    {
        switch (pattern)
        {
        case Gungeon::BossPattern::none:
            break;
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
        case Gungeon::BossPattern::brute:
            InitBrute();
            break;
        case Gungeon::BossPattern::rand:
            InitRand();
            break;
        }//switch
    }

    void Boss::InitItem()
    {
        float scaleFactor = 0.5f;
        dropItem = new Item;
        dropItem->col = new ObCircle;
        dropItem->col->scale = Vector2(40.0f, 40.0f) * scaleFactor;
        dropItem->col->isFilled = false;
        dropItem->SetPos(DEFAULTSPAWN);
        dropItem->idle = new ObImage(L"EnterTheGungeon/player_1/UI_Gold.png");
        dropItem->idle->scale = Vector2(40.0f, 40.0f) * scaleFactor;
        dropItem->idle->SetParentRT(*dropItem->col);
        dropItem->idle->isVisible = false;
    }

    void Boss::Release()
    {
        Unit::Release();
        SafeDelete(chairIdle);
        SafeDelete(chairWalk);
        SafeDelete(chairAttack1Start);
        SafeDelete(chairAttack1);
        SafeDelete(chairAttack2);
        SafeDelete(chairDie);
        SafeDelete(hpGuage);
        SafeDelete(hpGuageBar);
    }

    void Boss::Update()
    {
        Unit::SetTarget(weapon);
        Unit::Update();

        switch (state)
        {
        case Gungeon::State::idle:
            if (false == (moveDir.x == 0.0f && moveDir.y == 0.0f))
            {
                chairIdle->isVisible = false;
                chairWalk->isVisible = true;
            }
            Idle();
            break;
        case Gungeon::State::walk:
            if (moveDir.x == 0.0f && moveDir.y == 0.0f)
            {
                chairWalk->isVisible = false;
                chairIdle->isVisible = true;
            }
            Walk();
            break;
        case Gungeon::State::die:
            Die();
            break;
        case Gungeon::State::cinematic:
            break;
        }

        int curPattern = static_cast<int>(pattern);
        if (ImGui::SliderInt("Boss Pattern", &curPattern, 0, patternMax))
        {
            ChangePattern(curPattern);
            InitBullet();
        }
        
        bulletSpawnPos = firePos->GetWorldPos();
        bulletSpawnDir = targetDir;


        switch (pattern)
        {
        case Gungeon::BossPattern::none:
        case Gungeon::BossPattern::circular:
        case Gungeon::BossPattern::string:
        case Gungeon::BossPattern::shield:
        case Gungeon::BossPattern::spiral:
        case Gungeon::BossPattern::cluster:
        case Gungeon::BossPattern::rand:
            for (auto& elem : bullet)
            {
                elem->Update();
            }
            break;
        case Gungeon::BossPattern::brute:
            for (auto& elem : bullet)
            {
                elem->Update(false);
            }
            break;
        }

        chairIdle->Update();
        chairWalk->Update();
        chairAttack1Start->Update();
        chairAttack1->Update();
        chairAttack2->Update();
        chairDie->Update();

        firePos->Update();
        hpGuageBar->Update();
        hpGuage->Update();
        dropItem->Update();
    }

    void Boss::LateUpdate()
    {
    }

    void Boss::Render()
    {
        chairIdle->Render();
        chairWalk->Render();
        chairAttack1Start->Render();
        chairAttack1->Render();
        chairAttack2->Render();
        chairDie->Render();

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

        firePos->Render();
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
        Unit::Idle();
        
        Hitting();
        UpdateBullet();
    }

    void Boss::Walk()
    {
        moveDir = targetDir;
        Unit::Walk();

        Hitting();
        UpdateBullet();
    }

    void Boss::Die()
    {
        Unit::Die();

        for (auto& elem : bullet)
        {
            elem->idle->isVisible = false;
        }
    }

    void Boss::Hit(const int damage, const Vector2& dir)
    {
        pushedDir = dir;

        Unit::Hit(damage);

        hit->ChangeAnim(AnimState::once, 0.1f);

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
            idle->color = c;
            walk->color = c;
            hit->color = c;

            SetPosX(Pos().x + RANDOM->Float(-1.0f, 1.0f));
            SetPosY(Pos().y + RANDOM->Float(-1.0f, 1.0f));

            idle->isVisible = false;
            walk->isVisible = false;
            hit->isVisible = true;

            if (TIMER->GetTick(timeHitAnim, 0.4f))
            {
                Color c = Color(0.5f, 0.5f, 0.5f, 1.0f);
                idle->color = c;
                walk->color = c;
                hit->color = c;
                die->color = c;

                walk->isVisible = true;
                hit->isVisible = false;

                isHitAnim = false;

                pushedDir = Vector2(0.0f, 0.0f);
            }
        }
        else
        {
            idle->color.w = 1.0f;
            walk->color.w = 1.0f;
            hit->isVisible = false;
        }
    }

    void Boss::StartDie()
    {
        Unit::StartDie();

        chairIdle->isVisible = false;
        chairWalk->isVisible = false;
        chairDie->isVisible = true;

        hpGuageBar->img->isVisible = false;
        hpGuage->img->isVisible = false;

        // drop
        dropItem->Spawn(Vector2(Pos().x - 10.0f, Pos().y - 10.0f));
        dropItem->idle->isVisible = true;
        dropItem->state = State::idle;
    }

    void Boss::Spawn(const Vector2 wpos)
    {
        Unit::Spawn(wpos);

        InitVar();

        if (pushedDir.x < 0.0f)
        {
            die->reverseLR = true;
        }
        else
        {
            die->reverseLR = false;
        }

        dropItem->idle->isVisible = false;
        dropItem->state = State::die;
    }

    void Boss::ColToggle()
    {
        Character::ColToggle();
        firePos->isVisible ^= 1;
        for (auto& bulletElem : bullet)
        {
            bulletElem->col->isVisible ^= 1;
        }
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
            elem->SetPos(DEFAULTSPAWN);
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
        stringBullet.midForTargetFactor = 0.0f;
        stringBullet.SetStringBullet();
        bullet.resize(stringBullet.inputString.size() * 25);

        int size = stringBullet.inputString.size();

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
            elem->col->SetParentRT(*col);
            elem->col->SetLocalPos(Vector2(80.0f + idx * 2.0f, 80.0f + idx * 2.0f));
            elem->scalar = (idx + 1) * 3.0f;
            elem->idle->isVisible = true;
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

    void Boss::InitBrute()
    {
        bullet.resize(bruteMax);

        int idx = 0;
        for (auto& elem : bullet)
        {
            if (nullptr == elem) elem = new BossBullet;
            elem->scalar = RANDOM->Float(10.0f, 100.0f);
            elem->moveDir = Vector2(cos(idx * 6.0f * ToRadian), sin(idx * 6.0f * ToRadian));
            idx++;
        }
    }

    void Boss::InitRand()
    {
        bullet.resize(bruteMax);

        int idx = 0;
        for (auto& elem : bullet)
        {
            if (nullptr == elem) elem = new BossBullet;
            elem->scalar = RANDOM->Float(400.0f, 800.0f);
            elem->moveDir = Vector2(RANDOM->Float(-DIV2PI, DIV2PI), RANDOM->Float(-DIV2PI, DIV2PI));
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
        case Gungeon::BossPattern::brute:
            UpdateBrute();
            break;
        case Gungeon::BossPattern::rand:
            UpdateRand();
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

        if (ImGui::InputText("String Danmaku", s, 27) || 
            bullet.size() != size * 25)
        {
            stringBullet.inputString = s;
            size = stringBullet.inputString.size();
            bullet = vector<Bullet*>(size * 25);
            InitBullet();
            stringBullet.SetStringBullet();
        }

        if (TIMER->GetTick(timeFire, 2.0f))
        {
            angleFactor = firePos->rotation2 - stringBullet.midForTargetFactor;

            for (int r = 0; r < 5; r++)
            {
                for (int c = 0; c < 5; c++)
                {
                    for (int i = 0; i < size; i++)
                    {
                        if (stringBullet.outputAlphbets[i][r][c])
                        {
                            int idx = i * 25 + r * 5 + c;
                            bullet[idx]->atkAngle = (bullet[idx]->angle / 60.0f) + (0.2f * i) + angleFactor;
                            bullet[idx]->moveDir = Vector2(cos(bullet[idx]->atkAngle), sin(bullet[idx]->atkAngle));
                        }
                    }
                }
            }

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
            elem->isFired = true;
            elem->idle->isVisible = true;

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

    void Boss::UpdateBrute()
    {
        int t = 50;
        while (t--)
        {
            bullet[curBruteIdx++]->Spawn(bulletSpawnPos);
        }
        if (curBruteIdx >= bruteMax) curBruteIdx = 0;
    }

    void Boss::UpdateRand()
    {
        if (TIMER->GetTick(timeRand, 2.0f))
        {
            int t = 5;
            while (t--)
            {
                bullet[curRandIdx++]->Spawn(bulletSpawnPos);
                if (curRandIdx >= randMax) curRandIdx = 0;
            }
        }
    }
}