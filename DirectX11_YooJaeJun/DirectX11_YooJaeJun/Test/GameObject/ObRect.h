#pragma once

class ObRect : public GameObject
{
public:
	Vector2 position;

	ObRect();

	void Render(HDC hdc) override;

};