#pragma once
class Unit
{
public:
	ObCircle	hitbox;
	float		hitEffectTime;
	int			state;
	enum class estate { die, hit, alive };
	string		name;
	Vector2		lastPos;
	bool		onGround;
	float       gravity;
	Vector2		velocity;

public:
	Unit();
	virtual void Init();
	virtual void Update();
	virtual bool LateUpdate();
	virtual void Render();
	virtual bool HitFrom(const float damage);
};

