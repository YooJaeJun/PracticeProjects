#pragma once
#include "GameObject.h"

class Circle : public GameObject
{
public:
	Vector2 position;

	Circle();

	void Render(HDC hdc) override;
};

