#include "stdafx.h"

namespace Gungeon
{
    Gate::Gate()
    {
        Init();
    }

    void Gate::Init()
    {
        timeGateOpen = 0.0f;
        timeGateClosed = 0.0f;
        flagGateOpen = false;
        flagGateClosed = false;

        float scaleFactor = 2.0f;

        col = new ObRect;
        col->isVisible = false;
        col->scale = Vector2(70.0f, 70.0f) * scaleFactor;
        col->color = Color(1.0f, 1.0f, 1.0f);
        col->isFilled = false;
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
    }

    void Gate::Release()
    {
        Obstacle::Release();
        SafeDelete(col);
        SafeDelete(colTile);
    }

    void Gate::Update()
    {
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
}