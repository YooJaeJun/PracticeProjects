#pragma once

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
	Vector2			moveDir;
	float			scalar;
	int				curHp;
	int				maxHp;
	bool			isHit;
};

