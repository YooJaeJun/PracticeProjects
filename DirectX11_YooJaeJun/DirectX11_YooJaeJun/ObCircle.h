#pragma once

class ObCircle : public GameObject
{
public:
	Vector2 position;

	ObCircle();

	void Render() override;
};

