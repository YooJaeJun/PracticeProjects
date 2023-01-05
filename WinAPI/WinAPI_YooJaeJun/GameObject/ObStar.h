#pragma once
#include "GameObject.h"

class ObStar : public GameObject
{
public:
	Vector2 position;

	ObStar();

	void Render(HDC hdc) override;

};
