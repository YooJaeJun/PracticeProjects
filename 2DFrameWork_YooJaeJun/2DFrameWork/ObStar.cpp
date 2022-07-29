#include "framework.h"

ObStar::ObStar()
{
    vertex[0] = Vector2(0.5f * cosf(0), 0.5f * sinf(0));
    vertex[1] = Vector2(0.5f * cosf(72 * ToRadian), 0.5f * sinf(72 * ToRadian));
    vertex[2] = Vector2(0.5f * cosf(144 * ToRadian), 0.5f * sinf(144 * ToRadian));
    vertex[3] = Vector2(0.5f * cosf(216 * ToRadian), 0.5f * sinf(216 * ToRadian));
    vertex[4] = Vector2(0.5f * cosf(288 * ToRadian), 0.5f * sinf(288 * ToRadian));
}

void ObStar::Render()
{
    GameObject::Render();
    //정점이 이동된위치를 받아줄 지역변수
    Vector2 TransfomVertex[5];

    for (int i = 0; i < 5; i++)
    {
        // 이동된좌표  = 버텍스 * W;
        // 이동된좌표  = 버텍스 * S*R*T ;
        TransfomVertex[i] = Vector2::Transform(vertex[i], W);
    }
    //0->2->4->1->3->0

    /*MoveToEx(g_MemDC, TransfomVertex[0].x, TransfomVertex[0].y, NULL);
    LineTo(g_MemDC, TransfomVertex[2].x, TransfomVertex[2].y);
    LineTo(g_MemDC, TransfomVertex[4].x, TransfomVertex[4].y);
    LineTo(g_MemDC, TransfomVertex[1].x, TransfomVertex[1].y);
    LineTo(g_MemDC, TransfomVertex[3].x, TransfomVertex[3].y);
    LineTo(g_MemDC, TransfomVertex[0].x, TransfomVertex[0].y);*/
}
