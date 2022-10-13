#include "stdafx.h"

namespace Gungeon
{
    Door::Door()
    {
        Init();
    }

    void Door::Init()
    {
    }

    void Door::Release()
    {
        Obstacle::Release();
        SafeDelete(col);
    }

    void Door::Update()
    {
        Obstacle::Update();
        col->Update();
    }

    void Door::LateUpdate()
    {
    }

    void Door::Render()
    {
        Obstacle::Render();
        col->Render();
    }
}