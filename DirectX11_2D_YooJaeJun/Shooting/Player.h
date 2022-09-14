#pragma once
enum class PlState
{
	RUN,
	BOOST,
	DIE
};

class Player : public Character
{
public:
	ObImage*	boost;
	ObImage*	hit;
	ObImage*	die;
	PlState		state;
	float		timeLeft;
	float		timeRight;
	bool		isHit;
	float		timeHit;
	bool		isHitAnim;
	float		timeHitAnim;
	float		speed;
	float		speedOrigin;
	bool		isBoost;

public:
	Player();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	void Spawn();
	void Hit(const float damage);
	void Boost();
	void CancelBoost();
	void Die();
};

