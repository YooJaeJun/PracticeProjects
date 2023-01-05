#pragma once

class Character
{
public:
	GameObject*			obj;
	int					score;
	Vector2				moveDir;
	float				scalar;
	Vector2				lastPos;
	enum class Type		{ none, p1, p2, ball, post };
	Type				type;
	enum class State	{ idle, hit };
	State				state;
	float				hitTime;
	Color				originColor;

public:
	virtual void Init(Vector2 pos = Vector2(0.0f, 0.0f));
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void Release();

	virtual void Move();
	void Bounce(ColPos interPos, Character* other, Type type = Type::none);
	void SetDir(const Vector2 otherDir);
	void SetDirX(const float otherDirX);
	void SetDirY(const float otherDirY);
};

