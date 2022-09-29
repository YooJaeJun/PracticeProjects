#include "stdafx.h"

namespace Gungeon
{
    Boss::Boss()
    {
        Init();
    }

    void Boss::Init()
    {
        pattern = BossPattern::string;

        if (pattern == BossPattern::string)
        {
            stringBullet.inputString = "abcdefghijklmnopqrstuvwxyz";
        }

        SetPattern();

        curHp = maxHp = 1;
        scalar = 30.0f;
        timeFire = 0.0f;
        timeHit = 0.0f;
        isHit = false;
        isHitAnim = false;
        timeHitAnim = 0.0f;
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

        switch (state)
        {
        case State::idle:
            Idle();
            break;
        case State::die:
            Die();
            break;
        default:
            break;
        }

        if (isHit)
        {
            if (curHp <= 0.0f)
            {
                curHp = 0.0f;
                Killed();
            }

            if (TIMER->GetTick(timeHit, 0.01f))
            {
                isHit = false;
            }
        }

        if (curHp <= 0)
        {
            hpGuageBar->img->isVisible = false;
            hpGuage->img->isVisible = false;
        }
        else
        {
            hpGuage->img->scale.x = (float)curHp / maxHp * hpGuage->imgSize.x;
            hpGuage->img->uv.z = hpGuage->img->scale.x / hpGuage->imgSize.x;
        }
        hpGuageBar->Update();
        hpGuage->Update();
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
    }

    void Boss::ResizeScreen()
    {
        hpGuageBar->img->SetWorldPosX(-hpGuageBar->img->scale.x / 2.0f);
        hpGuageBar->img->SetWorldPosY(-app.GetHalfHeight() + 40.0f);
        hpGuage->img->SetWorldPosX(-hpGuage->img->scale.x / 2.0f);
        hpGuage->img->SetWorldPosY(-app.GetHalfHeight() + 40.0f);
    }

    void Boss::SetPattern()
    {
        if (pattern == BossPattern::circular)
        {
            bullet.resize(circularBulletMax);

            float bulletCoef = 4.0f;

            int idx = 0;
            for (auto& elem : bullet)
            {
                elem = new BossBullet;
                elem->col->scale.x = 8.0f * bulletCoef;
                elem->col->scale.y = 8.0f * bulletCoef;
                elem->idle = new ObImage(L"EnterTheGungeon/Boss_0/Bullet_0.png");
                elem->idle->scale.x = 8.0f * bulletCoef;
                elem->idle->scale.y = 8.0f * bulletCoef;
                elem->idle->SetParentRT(*elem->col);
                elem->moveDir.x = cos(idx * 360.0f / circularBulletMax * ToRadian);
                elem->moveDir.y = sin(idx * 360.0f / circularBulletMax * ToRadian);
                idx++;
            }
        }
        else if (pattern == BossPattern::string)
        {
            stringBullet.coefMidForTarget = 0.0f;
            stringBullet.SetStringBullet();
            bullet.resize(stringBullet.inputString.size() * 25);

            int idx = 0;
            float bulletCoef = 4.0f;
            for (auto& elem : bullet)
            {
                elem = new BossBullet;
                elem->col->scale.x = 8.0f * bulletCoef;
                elem->col->scale.y = 8.0f * bulletCoef;
                elem->idle = new ObImage(L"EnterTheGungeon/Boss_0/Bullet_1.png");
                elem->idle->scale.x = 8.0f * bulletCoef;
                elem->idle->scale.y = 8.0f * bulletCoef;
                elem->idle->SetParentRT(*elem->col);
                idx++;
            }
        }
    }

    void Boss::Idle()
    {
        Unit::Idle();

        if (isHitAnim)
        {
            Color c = Color(RANDOM->Float(0.6f, 1.0f), 0.5f, 0.5f, RANDOM->Float(0.2f, 1.0f));
            for (auto& elem : idle) elem->color = c;
            for (auto& elem : walk) elem->color = c;
            hit->color = c;

            SetPosX(Pos().x + RANDOM->Float(-1.0f, 1.0f));
            SetPosY(Pos().y + RANDOM->Float(-1.0f, 1.0f));

            for (auto& elem : idle) elem->isVisible = false;
            hit->isVisible = true;

            if (TIMER->GetTick(timeHitAnim, 0.4f))
            {
                Color c = Color(0.5f, 0.5f, 0.5f, 1.0f);
                for (auto& elem : idle) elem->color = c;
                for (auto& elem : walk) elem->color = c;
                hit->color = c;
                die->color = c;

                hit->isVisible = false;
                idle[curTargetDirState]->isVisible = true;

                isHitAnim = false;
            }
        }
        else
        {
            idle[curTargetDirState]->color.w = 1.0f;
            walk[curTargetDirState]->color.w = 1.0f;
            idle[curTargetDirState]->isVisible = true;
            hit->isVisible = false;
        }


        if (pattern == BossPattern::circular)
        {
            if (TIMER->GetTick(timeFire, 3.0f))
            {
                for (auto& elem : bullet)
                {
                    elem->Spawn(Vector2(
                        weapon->idle->GetWorldPivot().x + weapon->idle->scale.x / 2.0f,
                        weapon->idle->GetWorldPivot().y));
                }
            }
        }
        else if (pattern == BossPattern::string)
        {
            int size = stringBullet.inputString.size();
            char* s = const_cast<char*>(stringBullet.inputString.c_str());

            if (ImGui::InputText("String Danmaku", s, 26))
            {
                stringBullet.inputString = s;
                size = stringBullet.inputString.size();
                bullet = vector<BossBullet*>(size * 25);
                SetPattern();
                stringBullet.SetStringBullet();
            }

            if (TIMER->GetTick(timeFire, 3.0f))
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
                                    weapon->col->rotation - stringBullet.coefMidForTarget;
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

                    elem->Spawn(Vector2(
                        weapon->idle->GetWorldPivot().x + weapon->idle->scale.x / 2.0f,
                        weapon->idle->GetWorldPivot().y));
                }
            }
        }

        for (auto& elem : bullet)
        {
            elem->Update();
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

    void Boss::Killed()
    {
        Unit::Killed();

        for (auto& elem : bullet)
        {
            elem->col->colOnOff = false;
            elem->col->isVisible = false;
            elem->idle->colOnOff = false;
            elem->idle->isVisible = false;
        }
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
}