#include "stdafx.h"

namespace Gungeon
{
    Room::Room()
    {
        Init();
    }

    void Room::Init()
    {
        col = new ObRect();
        selected = false;
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