#include "ObStar.h"

ObStar::ObStar()
{
}

void ObStar::Render(HDC hdc)
{
	MoveToEx(hdc, position.x - 100 * cosf(45 * ToRadian + rotation) * scale.x, position.y * scale.y, NULL);
	LineTo(hdc, position.x + 100 * cosf(135 * ToRadian + rotation) * scale.x, position.y * scale.y);
	LineTo(hdc, position.x + 100 * cosf(225 * ToRadian + rotation) * scale.x, position.y * scale.y);
	LineTo(hdc, position.x + 100 * cosf(315 * ToRadian + rotation) * scale.x, position.y * scale.y);
	LineTo(hdc, position.x + 100 * cosf(0 * ToRadian + rotation) * scale.x, position.y * scale.y);
}
