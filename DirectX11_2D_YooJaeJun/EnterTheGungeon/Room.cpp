#include "stdafx.h"

namespace Gungeon
{
    Room::Room()
    {
        Init();
    }

    void Room::Init()
    {
        selected = false;
        cleared = false;
        
        col = new ObRect();
    }

    void Room::Release()
    {
        SafeDelete(col);
    }

    void Room::Update()
    {
        col->Update();
    }

    void Room::LateUpdate()
    {
    }

    void Room::Render()
    {
        col->Render();
    }
}