#pragma once
class Mover : public Unit
{
public:
	Vector2		lastPos;
	Vector2		dir;
	float		scalar;
	bool		fired;

public:
	Mover() = default;

	virtual void Move();
	void SetDir(const Vector2 otherDir);
	void SetDirX(const float otherDirX);
	void SetDirY(const float otherDirY);
	void Ready(const Vector2 pos = Vector2(0.0f, 0.0f));
};

