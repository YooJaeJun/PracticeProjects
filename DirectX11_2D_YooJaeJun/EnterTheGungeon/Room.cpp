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
        roomType = RoomType::enemy;
        
        col = new ObRect();
    }

    void Room::Release()
    {
        Character::Release();
    }

    void Room::Update()
    {
        Character::Update();
    }

    void Room::LateUpdate()
    {
    }

    void Room::Render()
    {
        Character::Render();
    }
}