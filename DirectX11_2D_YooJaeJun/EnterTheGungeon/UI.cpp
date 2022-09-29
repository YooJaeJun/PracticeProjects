#include "stdafx.h"

namespace Gungeon
{
    UI::UI()
    {
        anchor = Anchor::NONE;
    }

    void UI::Release()
    {
        if (img) SafeDelete(img);
    }

    void UI::Update()
    {
        img->Update();
    }

    void UI::LateUpdate()
    {
    }

    void UI::Render()
    {
        img->Render(); // RENDER->push(img);
    }

    void UI::Spawn(const float coefX, const float coefY)
    {
        switch (anchor)
        {
        case Anchor::LEFTTOP:
            img->SetWorldPos(Vector2(-app.GetHalfWidth() + coefX, app.GetHalfHeight() + coefY));
            break;
        case Anchor::LEFTBOTTOM:
            img->SetWorldPos(Vector2(-app.GetHalfWidth() + coefX, -app.GetHalfHeight() + coefY));
            break;
        case Anchor::RIGHTBOTTOM:
            img->SetWorldPos(Vector2(app.GetHalfWidth() + coefX, -app.GetHalfHeight() + coefY));
            break;
        }
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