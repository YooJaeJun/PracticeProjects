#include "stdafx.h"

Boss::Boss()
{
	curHp = maxHp = 1;
	scalar = 30.0f;
	timeFire = 0.0f;
	timeHit = 0.0f;
	isHit = false;
	isHitAnim = false;
	timeHitAnim = 0.0f;

    pattern = bossPattern::string;
    stringBullet.inputString = "abcdefghijklmnopqrstuvwxyz";
    bullet.resize(stringBullet.inputString.size() * 25);

    SetPattern();

    stringBullet.SetStringBullet();
}

void Boss::Release()
{
	Unit::Release();
	SafeDelete(hpGuage);
}

void Boss::Update()
{
	Unit::Update();

	if (isHit)
	{
		if (TIMER->GetTick(timeHit, 0.01f))
		{
			isHit = false;
		}
	}

	for (auto& elem : bullet)
	{
		elem->Update();
	}

    if (state != State::die)
    {
        if (pattern == bossPattern::circular)
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
        else if (pattern == bossPattern::string)
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
                    elem->Spawn(Vector2(
                        weapon->idle->GetWorldPivot().x + weapon->idle->scale.x / 2.0f,
                        weapon->idle->GetWorldPivot().y));
                }
            }
        }

        hpGuage->img->scale.x = (float)curHp / maxHp * hpGuage->imgSize.x;
        hpGuage->img->uv.z = hpGuage->img->scale.x / hpGuage->imgSize.x;
        hpGuage->Update();
    }
}

void Boss::LateUpdate()
{
	Unit::LateUpdate();
	for (auto& elem : bullet) if (elem) elem->LateUpdate();
	hpGuage->LateUpdate();
}

void Boss::Render()
{
	for (auto& elem : bullet) if (elem) elem->Render();
	Unit::Render();
    hpGuage->Render();
}

void Boss::SetPattern()
{
    pattern = bossPattern::string;

    if (pattern == bossPattern::circular)
    {
        bullet.resize(circularBulletMax);

        int idx = 0;
        float bulletCoef = 4.0f;
        for (auto& elem : bullet)
        {
            elem = new BossBullet;
            elem->col->scale.x = 8.0f * bulletCoef;
            elem->col->scale.y = 8.0f * bulletCoef;
            elem->idle = new ObImage(L"EnterTheGungeon/Boss_0/Bullet_0.png");
            elem->idle->scale.x = 8.0f * bulletCoef;
            elem->idle->scale.y = 8.0f * bulletCoef;
            elem->idle->SetParentRT(*elem->col);
            elem->moveDir = Vector2(cos(idx * 4.0f * ToRadian), sin(idx * 4.0f * ToRadian));
            idx++;
        }
    }
    else if (pattern == bossPattern::string)
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