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
    }

    void Gate::LateUpdate()
    {
    }

    void Gate::Render()
    {
        Obstacle::Render();
        col->Render();
        colTile->Render();
    }

    void Gate::Spawn(const Vector2 wpos)
    {
        SetPos(wpos);
        idle->ChangeAnim(AnimState::once, 0.1f);
        idle->isVisible = true;
        gateState = GateState::opening;
    }
}