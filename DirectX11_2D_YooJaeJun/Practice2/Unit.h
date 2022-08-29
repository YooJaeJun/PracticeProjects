#pragma once

class Unit
{
public:
	GameObject*			obj;
	enum class eState	{ idle, hit };
	int					score;
	Vector2				dir;
	float				scalar;

public:
	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void Release();

	virtual void Move();
	void SetDir(const Vector2 otherDir);
	void SetDirX(const float otherDirX);
	void SetDirY(const float otherDirY);
};

