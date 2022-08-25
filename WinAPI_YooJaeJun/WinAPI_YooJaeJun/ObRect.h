#pragma once

class ObRect : public GameObject
{
public:
	Vector2 vertex[4];

public:
	ObRect();

	void Render() override;
};


