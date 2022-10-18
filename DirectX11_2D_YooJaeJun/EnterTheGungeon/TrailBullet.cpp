#include "stdafx.h"

namespace Gungeon
{
    TrailBullet::TrailBullet()
    {
        Init();

        float scaleFactor = 5.0f;
        col->scale = Vector2(8.0f, 8.0f) * scaleFactor;
        col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        SetPos(DEFAULTSPAWN);

        idle = new ObImage(L"EnterTheGungeon/boss_1/Bullet_0.png");
        idle->isVisible = false;
        idle->scale = col->scale;
        idle->color = Color(0.5f, 0.7f, 1.0f);
        idle->SetParentRT(*col);

        float bombScaleFactor = 2.5f;
        hitBomb = new Effect;
        hitBomb->idle = new ObImage(L"EnterTheGungeon/boss_1/HitBomb.png");
        hitBomb->idle->maxFrame.x = 4;
        hitBomb->idle->scale = Vector2(88.0f / 4.0f, 22.0f) * bombScaleFactor;
        hitBomb->idle->isVisible = false;


        trails.resize(trailNum);

        for (auto& trail : trails)
        {
            trail = new ObImage(L"EnterTheGungeon/boss_1/Bullet_0.png");
            trail->isVisible = false;
            trail->scale = col->scale;
        }
    }

    void TrailBullet::Init()
    {
        Bullet::Init();
        scalar = 400.0f;
        damage = 1;
        angle = 0.0f;
        atkAngle = 0.0f;

        timeTrail = 0.01f;
        trailNum = 15;
        timeSpawnTrail = 0.0f;
    }

    void TrailBullet::Release()
    {
        Bullet::Release();
        for (auto& trail : trails) SafeDelete(trail);
    }

    void TrailBullet::Update()
    {
        Bullet::Update();

        if (TIMER->GetTick(timeSpawnTrail, timeTrail))
        {
            trails[0]->isVisible = true;
            trails[0]->SetWorldPos(Pos());
            trails[0]->rotation = col->rotation;
            trails[0]->scale = Vector2(30.0f, 30.0f);
            trails.push_back(trails[0]);
            trails.pop_front();
        }

        int idx = 0;
        for (auto& elem : trails)
        {
            if (idx == trails.size() - 1) elem->color = Color(1.0f, 0.6f, 0.5f);
            else elem->color = Color(0.5f, 0.5f, 0.8f); 
            elem->Update();
            idx++;
        }
    }

    void TrailBullet::Update(const bool notRotation)
    {
        Bullet::Update(notRotation);
    }

    void TrailBullet::LateUpdate()
    {
    }

    void TrailBullet::Render()
    {
        if (isFired)
        {
            Bullet::Render();

            for (auto& elem : trails)
            {
                elem->Render();
            }
        }
    }

    void TrailBullet::Reload()
    {
        Bullet::Reload();
    }
}