#pragma once
const int bombMax = 5;

enum class PlaneState
{
	RUN,
	BOOST,
	DIE
};

enum class PlaneType
{
	PLAYER,
	ENEMY,
	BOSS
};

class Airplane : public Character
{
public:
	PlaneType	type;
	float		key;
	Vector2		moveDir;
	float		speed;
	ObImage*	hit;
	ObImage*	die;
	ObImage*	bomb[bombMax];
	PlaneState	state;
	float		timeShoot;
	bool		isHit;
	float		timeHit;
	bool		isHitAnim;
	float		timeHitAnim;
	float		speedOrigin;

public:
	Airplane();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	virtual void Spawn();
	virtual void Hit(const float damage);
	virtual void Die();
};

