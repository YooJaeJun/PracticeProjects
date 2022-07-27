#include "framework.h"

ObStar::ObStar()
{
    vertex[0] = Vector2(0.5f * cosf(0), 0.5f * sinf(0));
    vertex[1] = Vector2(0.5f * cosf(72  * ToRadian), 0.5f * sinf(72  * ToRadian));
    vertex[2] = Vector2(0.5f * cosf(144 * ToRadian), 0.5f * sinf(144 * ToRadian));
    vertex[3] = Vector2(0.5f * cosf(216 * ToRadian), 0.5f * sinf(216 * ToRadian));
    vertex[4] = Vector2(0.5f * cosf(288 * ToRadian), 0.5f * sinf(288 * ToRadian));
}

void ObStar::Render()
{
    GameObject::Render();

    Vector2 TransfVtx[5];
    for (int i = 0; i < 5; i++)
    {
        TransfVtx[i] = Vector2::Transform(vertex[i], W);
    }

    MoveToEx(g_MemDC, (int)TransfVtx[0].x, (int)TransfVtx[0].y, NULL);
    LineTo(g_MemDC, (int)TransfVtx[3].x, (int)TransfVtx[3].y);
    LineTo(g_MemDC, (int)TransfVtx[1].x, (int)TransfVtx[1].y);
    LineTo(g_MemDC, (int)TransfVtx[4].x, (int)TransfVtx[4].y);
    LineTo(g_MemDC, (int)TransfVtx[2].x, (int)TransfVtx[2].y);
    LineTo(g_MemDC, (int)TransfVtx[0].x, (int)TransfVtx[0].y);
}
