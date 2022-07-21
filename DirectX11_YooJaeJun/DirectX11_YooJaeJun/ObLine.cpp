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

void ObLine::RenderClock(WORD degree)
{
    Vector2 TransfVtx[2];

    vertex[1] = Vector2(0.5f * cosf(6 * (degree - 15) * ToRadian),
        0.5f * sinf(6 * (degree - 15) * ToRadian));

    for (int i = 0; i < 2; i++)
    {
        TransfVtx[i] = Vector2::Transform(vertex[i], W);
    }

    MoveToEx(g_MemDC, TransfVtx[0].x, TransfVtx[0].y, NULL);
    LineTo(g_MemDC, 
        TransfVtx[1].x, 
        TransfVtx[1].y);
}
