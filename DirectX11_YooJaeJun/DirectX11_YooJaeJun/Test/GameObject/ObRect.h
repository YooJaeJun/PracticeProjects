#pragma once
#include "GameObject.h"

class ObRect : public GameObject
{
public:
	Vector2 position;

	ObRect();

	void Render(HDC hdc) override;

};