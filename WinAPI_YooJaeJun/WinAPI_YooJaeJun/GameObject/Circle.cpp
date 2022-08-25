#include "Circle.h"

Circle::Circle()
{
}

void Circle::Render(HDC hdc)
{
	MoveToEx(hdc, position.x + 100 * cosf(0 * ToRadian + rotation) * scale.x,
		position.y + 100 * sinf(0 * ToRadian + rotation) * scale.y, NULL);

	for (int i = 0; i <= 360; i += 1)
	{
		LineTo(hdc, position.x + 100 * cosf(i * ToRadian + rotation) * scale.x,
			position.y + 100 * sinf(i * ToRadian + rotation) * scale.y);
	}
}
