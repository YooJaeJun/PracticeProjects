#pragma once

class ObLine : public GameObject
{
public:
	Vector2 vertex[4];

public:
	ObLine();
	void Render() override;
	void RenderClock(WORD degree);
};


