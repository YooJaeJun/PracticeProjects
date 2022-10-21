#include "stdafx.h"

namespace Gungeon
{
    Gate::Gate()
    {
        Init();
    }

    void Gate::Init()
    {
        float scaleFactor = 2.0f;

        col->scale = Vector2(70.0f, 70.0f) * scaleFactor;
        col->pivot = OFFSET_B;
        SetPos(DEFAULTSPAWN);

        colTile = new ObRect;
        colTile->isVisible = false;
        colTile->scale = Vector2(40.0f, 20.0f) * scaleFactor;
        colTile->color = Color(1.0f, 1.0f, 1.0f);
        colTile->isFilled = false;
        colTile->SetParentRT(*col);
        colTile->SetLocalPosY(-20.0f);
        colTile->pivot = OFFSET_B;

        idle = new ObImage(L"EnterTheGungeon/Level/Gate.png");
        idle->isVisible = false;
        idle->maxFrame.x = 9;
        idle->scale = Vector2(604.0f / 9.0f, 165.0f) * scaleFactor;
        idle->SetParentRT(*col);
        idle->SetLocalPosY(-20.0f);
        idle->pivot = OFFSET_B;

        for (auto& elem : cinematicBox)
        {
            elem = new UI;
            elem->img = new ObImage(L"EnterTheGungeon/Level/Cinematic_Box.png");
            elem->img->scale = Vector2(app.GetWidth(), 150.0f);
            elem->img->isFilled = true;
            elem->img->color = Color(0.0f, 0.0f, 0.0f);
            elem->img->space = Space::screen;
            elem->img->pivot = OFFSET_LT;
        }
        cinematicBox[0]->anchor = DirState::dirLT;
        cinematicBox[0]->Spawn(0.0f, 150.0f);
        cinematicBox[1]->anchor = DirState::dirLB;
        cinematicBox[1]->Spawn(0.0f, 0.0f);

        gateState = GateState::none;
    }

    void Gate::Release()
    {
        Obstacle::Release();
        SafeDelete(col);
        SafeDelete(colTile);
    }

    void Gate::Update()
    {
        switch (gateState)
        {
        case Gungeon::GateState::none:
            break;

        case Gungeon::GateState::opening:
            if (TIMER->GetTick(timeOpen, 1.5f))
            {
                gateState = GateState::open;
            }
            break;

        case Gungeon::GateState::open:
            if (flagIntersectPlayer)
            {
                gateState = GateState::cinematic;
            }
            break;

        case Gungeon::GateState::cinematic:
            cinematicBox[0]->img->MoveWorldPos(Vector2(0.0f, -75.0f * DELTA));
            cinematicBox[1]->img->MoveWorldPos(Vector2(0.0f, 75.0f * DELTA));

            if (TIMER->GetTick(timeCinematicBox, 1.0f))
            {
                gateState = GateState::process;
            }
            break;

        case Gungeon::GateState::process:
            break;

        case Gungeon::GateState::setting:
            if (TIMER->GetTick(timeSet, 0.5f))
            {
                gateState = GateState::set;
            }
            break;

        case Gungeon::GateState::set:
            idle->ChangeAnim(AnimState::reverseOnce, 0.1f);
            gateState = GateState::closing;
            break;

        case Gungeon::GateState::closing:

            if (TIMER->GetTick(timePlayerDisappear, 0.2f))
            {
                flagPlayerDisappear = true;
            }

            if (TIMER->GetTick(timeClosed, 0.3f))
            {
                gateState = GateState::closed;
            }
            break;

        case Gungeon::GateState::closed:
            break;
        }


        Obstacle::Update();
        col->Update();
        colTile->Update();
        for (auto& elem : cinematicBox) elem->Update();
    }

    void Gate::LateUpdate()
    {
    }

    void Gate::Render()
    {
        Obstacle::Render();
        col->Render();
        colTile->Render();
        for (auto& elem : cinematicBox) elem->Render();
    }

    void Gate::Spawn(const Vector2 wpos)
    {
        SetPos(wpos);
        idle->ChangeAnim(AnimState::once, 0.1f);
        idle->isVisible = true;
        gateState = GateState::opening;
    }
}