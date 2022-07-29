#pragma once
class ObStar : public GameObject
{
public:
	Vector2 vertex[5];

	ObStar();
	void Render() override;
};

