#include "stdafx.h"

namespace Gungeon
{
    TreasureBox::TreasureBox()
    {
        Init();
    }

    void TreasureBox::Init()
    {
        col->scale = Vector2(50.0f, 19.0f) * 2.0f;
        col->SetWorldPos(DEFAULTSPAWN);
        idle = new ObImage(L"EnterTheGungeon/Level/Treasure.png");
        idle->maxFrame.x = 2;
        idle->scale = Vector2(50.0f / 2.0f, 19.0f) * 2.0f;
        idle->SetParentT(*col);
    }

    void TreasureBox::Release()
    {
        Obstacle::Release();
        SafeDelete(col);
    }

    void TreasureBox::Update()
    {
        Obstacle::Update();
        col->Update();
    }

    void TreasureBox::LateUpdate()
    {
    }

    void TreasureBox::Render()
    {
        Obstacle::Render();
        col->Render();
    }
}