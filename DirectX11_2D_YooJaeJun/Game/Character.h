#pragma once

enum class State
{
	idle,
	roll,
	die
};

class Character
{
public:
	Character();

	virtual void Release();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

public:
	GameObject*		col;
	State			state;
	Vector2			moveDir;
	float			scalar;
	int				curHp;
	int				maxHp;
	bool			isHit;
};

