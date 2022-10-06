#include "stdafx.h"

namespace Gungeon
{
    MapObject::MapObject()
    {
    }

    void MapObject::Init()
    {
        float doorOpenScaleCoef = 2.5f;

        int idx = 0;
        for (auto& elem : doorOpenUp)
        {
            elem = new Obstacle;
            elem->col->scale.x = 88.0f / 4.0f * doorOpenScaleCoef;
            elem->col->scale.y = 50.0f * doorOpenScaleCoef;
            elem->SetPosX(200.0f + idx * elem->col->scale.x);
            elem->SetPosY(0.0f);
            elem->col->collider = Collider::rect;
            elem->col->zOrder = ZOrder::object;

            elem->idle = new ObImage(L"EnterTheGungeon/Level/Door_Open_Up.png");
            elem->idle->maxFrame.x = 4;
            elem->idle->scale.x = 88.0f / 4.0f * doorOpenScaleCoef;
            elem->idle->scale.y = 50.0f * doorOpenScaleCoef;
            elem->idle->SetParentRT(*elem->col);
            elem->idle->ChangeAnim(ANIMSTATE::STOP, 0.1f);
            elem->idle->zOrder = ZOrder::object;

            if (idx & 1)
            {
                elem->idle->reverseLR = true;
            }

            elem->col->Update();

            idx++;
        }

        idx = 0;
        for (auto& elem : doorOpenDown)
        {
            elem = new Obstacle;
            elem->col->isVisible = false;   //
            elem->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
            elem->col->scale.x = 88.0f / 4.0f * doorOpenScaleCoef;
            elem->col->scale.y = 50.0f * doorOpenScaleCoef;
            elem->SetPosX(200.0f + idx * elem->col->scale.x);
            elem->SetPosY(0.0f);
            elem->col->collider = Collider::rect;
            elem->col->zOrder = ZOrder::object;

            elem->idle = new ObImage(L"EnterTheGungeon/Level/Door_Open_Down.png");
            elem->idle->maxFrame.x = 4;
            elem->idle->scale.x = 88.0f / 4.0f * doorOpenScaleCoef;
            elem->idle->scale.y = 50.0f * doorOpenScaleCoef;
            elem->idle->SetParentRT(*elem->col);
            elem->idle->ChangeAnim(ANIMSTATE::STOP, 0.1f);
            elem->idle->zOrder = ZOrder::object;

            if (idx & 1)
            {
                elem->idle->reverseLR = true;
            }

            elem->col->Update();

            idx++;
        }

        float doorClosedScaleCoef = 2.5f;

        idx = 0;
        for (auto& elem : doorClosed)
        {
            elem = new Obstacle;
            elem->col->isVisible = true;
            elem->col->isFilled = false;
            elem->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
            elem->col->scale.x = 68.0f / 2.0f * doorClosedScaleCoef;
            elem->col->scale.y = 41.0f * doorClosedScaleCoef;
            elem->SetPosX(200.0f + idx * elem->col->scale.x);
            elem->SetPosY(200.0f);
            elem->col->collider = Collider::rect;
            elem->col->zOrder = ZOrder::object;

            elem->idle = new ObImage(L"EnterTheGungeon/Level/Door_Closed.png");
            elem->idle->maxFrame.x = 2;
            elem->idle->scale.x = 68.0f / 2.0f * doorClosedScaleCoef;
            elem->idle->scale.y = 41.0f * doorClosedScaleCoef;
            elem->idle->SetParentRT(*elem->col);
            elem->idle->ChangeAnim(ANIMSTATE::LOOP, 2.0f);
            elem->idle->zOrder = ZOrder::object;

            if (idx & 1)
            {
                elem->idle->reverseLR = true;
            }

            elem->col->Update();

            idx++;
        }
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