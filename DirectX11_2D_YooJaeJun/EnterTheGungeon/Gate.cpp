#include "stdafx.h"

namespace Gungeon
{
    Gate::Gate()
    {
        Init();
    }

    void Gate::Init()
    {
    }

    void Gate::Release()
    {
        Obstacle::Release();
        SafeDelete(col);
    }

    void Gate::Update()
    {
        Obstacle::Update();
        col->Update();
    }

    void Gate::LateUpdate()
    {
    }

    void Gate::Render()
    {
        Obstacle::Render();
        col->Render();
    }
}