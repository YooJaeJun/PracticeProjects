#include "stdafx.h"

namespace Gungeon
{
    UI::UI()
    {
        anchor = Anchor::none;
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
        case Anchor::leftTop:
            img->SetWorldPos(Vector2(-app.GetHalfWidth() + xFactor, app.GetHalfHeight() + yFactor));
            break;
        case Anchor::leftBottom:
            img->SetWorldPos(Vector2(-app.GetHalfWidth() + xFactor, -app.GetHalfHeight() + yFactor));
            break;
        case Anchor::rightBottom:
            img->SetWorldPos(Vector2(app.GetHalfWidth() + xFactor, -app.GetHalfHeight() + yFactor));
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