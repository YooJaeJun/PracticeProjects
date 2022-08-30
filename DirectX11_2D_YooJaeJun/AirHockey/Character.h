#pragma once

class Character
{
public:
	GameObject*			obj;
	int					score;
	Vector2				moveDir;
	float				scalar;
	Vector2				lastPos;
	enum class eType	{ none, p1, p2, ball, post };
	eType				type;
	enum class eState	{ idle, hit };
	eState				state;
	float				hitTime;
	Color				originColor;

public:
	virtual void Init(Vector2 pos = Vector2(0.0f, 0.0f));
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void Release();

	virtual void Move();
	void Bounce(IntersectPos interPos, Character* other, eType type = eType::none);
	void SetDir(const Vector2 otherDir);
	void SetDirX(const float otherDirX);
	void SetDirY(const float otherDirY);
};

