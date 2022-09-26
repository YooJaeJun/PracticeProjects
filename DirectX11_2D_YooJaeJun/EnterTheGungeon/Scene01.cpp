#include "stdafx.h"

Scene01::Scene01()
{
    Init();
}

Scene01::~Scene01()
{
    SafeDelete(tilemap);
    mapObj->Release();
    player->Release();
    for (auto& elem : enemy) elem->Release();
    boss->Release();
}

void Scene01::Init()
{
    int idx = 0;

    // 맵
    LIGHT->light.radius = 2000.0f;
    tilemap = new ObTileMap;
    tilemap->file = "EnterTheGungeon.txt";
    tilemap->Load();
    tilemap->CreateTileCost();

    // 맵 오브젝트
    mapObj = new MapObject;

    // 플레이어
    player = new Player;

    Int2 on;
    if (tilemap->WorldPosToTileIdx(Vector2(-5.0f, 0.0f), on))
    {
        player->Spawn(tilemap->TileIdxToWorldPos(on));
    }

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
        elem->die->maxFrame.x = 4;
        elem->die->scale.x = 96.0f / 4.0f * enemyScaleCoef;
        elem->die->scale.y = 24.0f * enemyScaleCoef;
        elem->die->SetParentRT(*elem->col);
        elem->die->zOrder = ZOrder::object;

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
        elem->weapon->idle->zOrder = ZOrder::weapon;

        elem->weapon->firePos = new GameObject;
        elem->weapon->firePos->SetParentRT(*elem->weapon->col);
        elem->weapon->firePos->SetLocalPos(Vector2(elem->weapon->col->scale.x / 2.0f, 0.0f));
        elem->weapon->firePos->zOrder = ZOrder::none;

        elem->shadow = new ObImage(L"EnterTheGungeon/Enemy_0/Shadow_1.png");
        elem->shadow->scale.x = 12.0f * enemyScaleCoef;
        elem->shadow->scale.y = 4.0f * enemyScaleCoef;
        elem->shadow->SetParentRT(*elem->col);
        elem->shadow->SetWorldPosY(-35.0f);
        elem->shadow->zOrder = ZOrder::shadow;
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
    boss->col->zOrder = ZOrder::object;

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
        elem->maxFrame.x = 2;
        elem->scale.x = 40.0f / 2.0f * bossScaleCoef;
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
    boss->die->scale.x = 320.0f / 8.0f * enemyScaleCoef;
    boss->die->scale.y = 40.0f * enemyScaleCoef;
    boss->die->SetParentRT(*boss->col);
    boss->die->zOrder = ZOrder::object;

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
    boss->weapon->idle->zOrder = ZOrder::weapon;

    boss->weapon->firePos = new GameObject;
    boss->weapon->firePos->SetParentRT(*boss->weapon->col);
    boss->weapon->firePos->SetLocalPos(Vector2(boss->weapon->col->scale.x / 2.0f, 0.0f));
    boss->weapon->firePos->zOrder = ZOrder::none;


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


    // 맵 오브젝트
    float doorOpenScaleCoef = 2.5f;

    idx = 0;
    for (auto& elem : mapObj->doorOpenUp)
    {
        elem = new Obstacle;
        elem->col = new ObRect;
        elem->col->isFilled = false;
        elem->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
        elem->col->scale.x = 66.0f / 3.0f * doorOpenScaleCoef;
        elem->col->scale.y = 48.0f * doorOpenScaleCoef;
        elem->SetPosX(200.0f + idx * elem->col->scale.x);
        elem->col->collider = Collider::rect;
        elem->col->zOrder = ZOrder::object;

        elem->idle = new ObImage(L"EnterTheGungeon/Level/Door_Open_Up.png");
        elem->idle->maxFrame.x = 3;
        elem->idle->scale.x = 66.0f / 3.0f * doorOpenScaleCoef;
        elem->idle->scale.y = 48.0f * doorOpenScaleCoef;
        elem->idle->SetParentRT(*elem->col);
        elem->idle->ChangeAnim(ANIMSTATE::STOP, 0.1f);
        elem->idle->zOrder = ZOrder::object;

        if (idx & 1)
        {
            elem->idle->reverseLR = true;
        }

        elem->col->Update();
        Int2 on;
        if (tilemap->WorldPosToTileIdx(elem->Pos(), on))
        {
            tilemap->SetTileState(on, TileState::door);
        }

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
        elem->col->scale.x = 66.0f / 3.0f * doorOpenScaleCoef;
        elem->col->scale.y = 48.0f * doorOpenScaleCoef;
        elem->SetPosX(200.0f + idx * elem->col->scale.x);
        elem->col->collider = Collider::rect;
        elem->col->zOrder = ZOrder::object;

        elem->idle = new ObImage(L"EnterTheGungeon/Level/Door_Open_Down.png");
        elem->idle->isVisible = false;  //
        elem->idle->maxFrame.x = 3;
        elem->idle->scale.x = 66.0f / 3.0f * doorOpenScaleCoef;
        elem->idle->scale.y = 48.0f * doorOpenScaleCoef;
        elem->idle->SetParentRT(*elem->col);
        elem->idle->ChangeAnim(ANIMSTATE::STOP, 0.1f);
        elem->idle->zOrder = ZOrder::object;

        if (idx & 1)
        {
            elem->idle->reverseLR = true;
        }

        elem->col->Update();
        Int2 on;
        if (tilemap->WorldPosToTileIdx(elem->Pos(), on))
        {
            tilemap->SetTileState(on, TileState::door);
        }

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
        Int2 on;
        if (tilemap->WorldPosToTileIdx(elem->Pos(), on))
        {
            tilemap->SetTileState(on, TileState::door);
        }

        idx++;
    }
}

void Scene01::Release()
{
}

void Scene01::Update()
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
        if (elem->state == State::idle)
        {
            elem->targetPos = player->Pos();
            elem->weapon->col->rotation = Utility::DirToRadian(player->Pos());
        }
        elem->Update();

        if (elem->state == State::idle)
        {
            elem->FindPath(tilemap);
        }
    }

    if (boss->state == State::idle)
    {
        boss->targetPos = player->Pos();
        boss->weapon->col->rotation = Utility::DirToRadian(player->Pos());
    }
    boss->Update();
}

void Scene01::LateUpdate()
{
    // CheckIntersect();

    int idx = 0;

    // 플레이어
    player->CheckFootGrid(tilemap);

    // 플레이어 총알
    for (auto& bulletElem : player->bullet)
    {
        for (auto& enemyElem : enemy)
        {
            if (enemyElem->state != State::die &&
                bulletElem->col->Intersect(enemyElem->col))
            {
                Vector2 dir = enemyElem->col->GetWorldPos() - bulletElem->col->GetWorldPos();
                enemyElem->col->MoveWorldPos(dir * 150.0f * DELTA);
                enemyElem->Hit(bulletElem->damage);
                bulletElem->Hit(1);
            }
        }

        if (boss->state != State::die &&
            bulletElem->col->Intersect(boss->col))
        {
            boss->Hit(bulletElem->damage);
            bulletElem->Hit(1);
        }

        Int2 bulletOn;
        if (tilemap->WorldPosToTileIdx(bulletElem->Pos(), bulletOn))
        {
            if (tilemap->GetTileState(bulletOn) == TileState::wall ||
                tilemap->GetTileState(bulletOn) == TileState::door)
            {
                bulletElem->Reload();
            }
        }
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

            // 적 총알
            for (auto& bulletElem : enemyElem->bullet)
            {
                if (bulletElem->col->Intersect(player->col))
                {
                    player->Hit(bulletElem->damage);
                    bulletElem->Hit(1);
                }

                Int2 bulletOn;
                if (tilemap->WorldPosToTileIdx(bulletElem->Pos(), bulletOn))
                {
                    if (tilemap->GetTileState(bulletOn) == TileState::wall ||
                        tilemap->GetTileState(bulletOn) == TileState::door)
                    {
                        bulletElem->Reload();
                    }
                }
            }
        }
        /*
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
        */
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

        // 보스 총알
        for (auto& bulletElem : boss->bullet)
        {
            if (bulletElem->col->Intersect(player->col))
            {
                player->Hit(bulletElem->damage);
                bulletElem->Hit(1);
            }

            Int2 bulletOn;
            if (tilemap->WorldPosToTileIdx(bulletElem->Pos(), bulletOn))
            {
                if (tilemap->GetTileState(bulletOn) == TileState::wall ||
                    tilemap->GetTileState(bulletOn) == TileState::door)
                {
                    bulletElem->Reload();
                }
            }
        }
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

    /*
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
    */

    player->LateUpdate();
}

void Scene01::Render()
{
    tilemap->Render();
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

void Scene01::ResizeScreen()
{
    player->ResizeScreen();

    boss->ResizeScreen();
}

void Scene01::CheckIntersect()
{
    /*
    grid.clear();

    int idx = 0;

    Int2 on;
    vector<Vector2>& foot = player->Foot();
    for (int i = 0; i < 4; i++)
    {
        if (tilemap->WorldPosToTileIdx(foot[i], on))
        {
            if (tilemap->GetTileState(on) == TileState::wall)
            {
                player->StepBack();
            }
        }
    }

    if (tilemap->WorldPosToTileIdx(player->Pos(), on))
    {
        ImGui::Text("TileState %d", tilemap->GetTileState(on));

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