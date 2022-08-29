#pragma once
class Ball : public Mover
{
public:
	

public:
	Ball() = default;

	void LastPosUpdate();
	void Bounce(IntersectPos interPos, bool withBar = false, Vector2 barDir = Vector2(0.0f, 0.0f));
	void SpawnStorm(Vector2 pos = Vector2(0.0f, 0.0f));
};

