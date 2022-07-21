#pragma once

class ObCircle : public GameObject
{
public:
	Vector2 vertex[60];

public:
	ObCircle();

	void Render() override;
};

