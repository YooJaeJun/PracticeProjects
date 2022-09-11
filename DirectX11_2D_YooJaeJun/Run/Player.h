#pragma once
enum class State
{
	RUN,
	SLIDE,
	JUMP,
	BOOST
};

class Player : public Character
{
public:
	ObImage*	run;
	ObImage*	slide;
	ObImage*	jump;
	ObImage*	doubleJump;
	ObImage*	land;
	ObImage*	hit;
	ObImage*	boost;
	State		state;
	float		gravity;
	bool		isDoubleJump;
	bool		isHit;
	float		timerHit;
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
};

