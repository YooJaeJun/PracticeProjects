#include "stdafx.h"

namespace Gungeon
{
    UI::UI()
    {
    }

    void UI::Release()
    {
        SafeDelete(img);
    }

    void UI::Update()
    {
        if (img) img->Update();
    }

    void UI::LateUpdate()
    {
    }

    void UI::Render()
    {
        if (img) img->Render(); // RENDER->push(img);
    }

    void UI::Spawn(const float xFactor, const float yFactor)
    {
        switch (anchor)
        {
        case DirState::dirLT:
            img->SetWorldPos(Vector2(-app.GetHalfWidth() + xFactor, app.GetHalfHeight() + yFactor));
            break;
        case DirState::dirLB:
            img->SetWorldPos(Vector2(-app.GetHalfWidth() + xFactor, -app.GetHalfHeight() + yFactor));
            break;
        case DirState::dirRT:
            img->SetWorldPos(Vector2(app.GetHalfWidth() + xFactor, app.GetHalfHeight() + yFactor));
            break;
        case DirState::dirRB:
            img->SetWorldPos(Vector2(app.GetHalfWidth() + xFactor, -app.GetHalfHeight() + yFactor));
            break;
        default:
            img->SetWorldPos(Vector2(xFactor, yFactor));
            break;
        }

        img->isVisible = true;
    }

    bool UI::DownGauge()
    {
        if (img->scale.x <= 0.0f)
        {
            img->scale.x = 0.0f;
            img->uv.z = 0.0f;
            return false;
        }
        else
        {
            img->scale.x -= imgSize.x / 50.0f * DELTA;
            img->uv.z = img->scale.x / imgSize.x;
        }
        return true;
    }
}