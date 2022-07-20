#include "framework.h"

ObCircle::ObCircle()
{
}

void ObCircle::Render()
{
	MoveToEx(g_MemDC, position.x + 100 * cosf(0 * ToRadian + rotation) * scale.x,
		position.y + 100 * sinf(0 * ToRadian + rotation) * scale.y, NULL);

	for (int i = 0; i <= 60; i++)
	{
		LineTo(g_MemDC, position.x + 100 * cosf(i * 6 * ToRadian + rotation) * scale.x,
			position.y + 100 * sinf(i * 6 * ToRadian + rotation) * scale.y);
	}
}
