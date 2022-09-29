#include "stdafx.h"

namespace Gungeon
{
    MapObject::MapObject()
    {
    }

    void MapObject::Release()
    {
        for (auto& elem : doorOpenUp) elem->Release();
        for (auto& elem : doorOpenDown) elem->Release();
        for (auto& elem : doorClosed) elem->Release();
    }

    void MapObject::Update()
    {
        for (auto& elem : doorOpenUp) elem->Update();
        for (auto& elem : doorOpenDown) elem->Update();
        for (auto& elem : doorClosed) elem->Update();
    }

    void MapObject::LateUpdate()
    {
    }

    void MapObject::Render()
    {
        for (auto& elem : doorOpenUp)  elem->Render();
        for (auto& elem : doorOpenDown) elem->Render();
        for (auto& elem : doorClosed) elem->Render();
    }
}