#include "framework.h"

ObRect::ObRect()
{
    vertex[0] = Vector2(-0.5f, -0.5f);
    vertex[1] = Vector2(-0.5f, 0.5f);
    vertex[2] = Vector2(0.5f, 0.5f);
    vertex[3] = Vector2(0.5f, -0.5f);
}

void ObRect::Render()
{
    GameObject::Render();

    Vector2 TransfVtx[4];
    for (int i = 0; i < 4; i++)
    {
        TransfVtx[i] = Vector2::Transform(vertex[i], W);
    }

    MoveToEx(g_MemDC, (int)TransfVtx[0].x, (int)TransfVtx[0].y, NULL);
    LineTo(g_MemDC, (int)TransfVtx[1].x, (int)TransfVtx[1].y);
    LineTo(g_MemDC, (int)TransfVtx[2].x, (int)TransfVtx[2].y);
    LineTo(g_MemDC, (int)TransfVtx[3].x, (int)TransfVtx[3].y);
    LineTo(g_MemDC, (int)TransfVtx[0].x, (int)TransfVtx[0].y);
}
