#pragma once
enum class State
{
	RUN,
	SLIDE,
	JUMP,
	BOOST,
	DIE
};

class Player : public Character
{
public:
	ObImage*	slide;
	ObImage*	jump;
	ObImage*	doubleJump;
	ObImage*	land;
	ObImage*	hit;
	ObImage*	boost;
	ObImage*	die;
	State		state;
	float		gravity;
	bool		isDoubleJump;
	bool		isHit;
	float		timerHit;
	bool		isHitAnim;
	float		timerHitAnim;
	float		speed;
	float		speedOrigin;
	bool		isBoost;
	float		timerBoost;
	bool		isLand;
	float		timerLand;

public:
	Player();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	void Spawn();
	void LandOn();
	void Hit(const float damage);
	void Boost();
	void Die();
};

