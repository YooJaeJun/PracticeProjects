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
    Vector2 TransfVtx[4];
    for (int i = 0; i < 4; i++)
    {
        TransfVtx[i] = Vector2::Transform(vertex[i], W);
    }

    MoveToEx(g_MemDC, TransfVtx[0].x, TransfVtx[0].y, NULL);
    LineTo(g_MemDC, TransfVtx[1].x, TransfVtx[1].y);
    LineTo(g_MemDC, TransfVtx[2].x, TransfVtx[2].y);
    LineTo(g_MemDC, TransfVtx[3].x, TransfVtx[3].y);
    LineTo(g_MemDC, TransfVtx[0].x, TransfVtx[0].y);
}
