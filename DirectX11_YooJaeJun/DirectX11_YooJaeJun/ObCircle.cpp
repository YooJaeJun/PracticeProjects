#include "framework.h"

ObCircle::ObCircle()
{
	for (int i = 0; i < 60; i++)
	{
		vertex[i] = Vector2(0.5f * cosf(6 * i * ToRadian), 
			0.5f * sinf(6 * i * ToRadian));
	}
}

void ObCircle::Render()
{
	Vector2 TransfVtx[60];

	for (int i = 0; i < 60; i++)
	{
		TransfVtx[i] = Vector2::Transform(vertex[i], W);
	}

	MoveToEx(g_MemDC, TransfVtx[0].x, TransfVtx[0].y, NULL);
	for (int i = 0; i < 60; i++)
	{
		LineTo(g_MemDC, TransfVtx[i].x, TransfVtx[i].y);
	}
	LineTo(g_MemDC, TransfVtx[0].x, TransfVtx[0].y);
}
