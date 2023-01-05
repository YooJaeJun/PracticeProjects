#pragma once
enum class PlState
{
	RUN,
	SLIDE,
	JUMP,
	DOUBLEJUMP,
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
	PlState		state;
	float		gravity;
	bool		isHit;
	float		timeHit;
	bool		isHitAnim;
	float		timeHitAnim;
	float		speed;
	float		speedOrigin;
	bool		isBoost;
	float		timeBoost;
	bool		isLand;
	float		timeLand;
	bool		downJump;
	bool		downDoubleJump;
	bool		downSlide;
	bool		upSlide;

public:
	Player();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	void Jump();
	void DoubleJump();
	void Slide();
	void CancelSlide();
	void Spawn();
	void LandOn();
	void Hit(const float damage);
	void Boost();
	void Die();
};

