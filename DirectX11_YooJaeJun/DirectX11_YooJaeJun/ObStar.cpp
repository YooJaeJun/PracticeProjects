#include "framework.h"

ObStar::ObStar()
{

}

void ObStar::Render()
{
    MoveToEx(g_MemDC, position.x + 100 * cosf(0 * ToRadian + rotation) * scale.x,
        position.y + 100 * sinf(0 * ToRadian + rotation) * scale.y, NULL);

    LineTo(g_MemDC, position.x + 100 * cosf(216 * ToRadian + rotation) * scale.x,
        position.y + 100 * sinf(216 * ToRadian + rotation) * scale.y);

    LineTo(g_MemDC, position.x + 100 * cosf(72 * ToRadian + rotation) * scale.x,
        position.y + 100 * sinf(72 * ToRadian + rotation) * scale.y);

    LineTo(g_MemDC, position.x + 100 * cosf(288 * ToRadian + rotation) * scale.x,
        position.y + 100 * sinf(288 * ToRadian + rotation) * scale.y);

    LineTo(g_MemDC, position.x + 100 * cosf(144 * ToRadian + rotation) * scale.x,
        position.y + 100 * sinf(144 * ToRadian + rotation) * scale.y);

    LineTo(g_MemDC, position.x + 100 * cosf(0 * ToRadian + rotation) * scale.x,
        position.y + 100 * sinf(0 * ToRadian + rotation) * scale.y);
}
