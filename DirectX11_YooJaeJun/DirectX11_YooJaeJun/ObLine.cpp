#include "framework.h"

ObLine::ObLine()
{
    vertex[0] = Vector2(0.0f, 0.0f);
    vertex[1] = Vector2(1.0f, 0.0f);
}

void ObLine::Render()
{
    Vector2 TransfVtx[2];

    for (int i = 0; i < 2; i++)
    {
        TransfVtx[i] = Vector2::Transform(vertex[i], W);
    }

    MoveToEx(g_MemDC, TransfVtx[0].x, TransfVtx[0].y, NULL);
    LineTo(g_MemDC, TransfVtx[1].x, TransfVtx[1].y);
}
