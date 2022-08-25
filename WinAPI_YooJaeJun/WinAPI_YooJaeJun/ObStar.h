#pragma once

class ObStar : public GameObject
{
public:
	Vector2 vertex[5];

public:
	ObStar();

	void Render() override;
};

