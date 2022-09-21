#pragma once
enum class State
{
	idle,
	walk,
	roll,
	die
};

// 8πÊ«‚
enum dir
{
	front,
	leftSide,
	rightSide,
	leftDiag,
	rightDiag,
	back,
	backLeftDiag,
	backRightDiag
};

class Unit : public Character
{
public:
	Unit();

	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	void Spawn();
	void Hit(const int damage);
	void Die();

public:
	ObImage*	idle[8];
	ObImage*	walk[8];
	ObImage*	roll[8];
	ObImage*	kick[8];
	ObImage*	hit;
	ObImage*	fall;
	ObImage*	die;
	Weapon*		weapon;
	State		state;
	dir			curDir;
	dir			beforeDir;
	Vector2		dest;
	float		timeFire;
	float		timeReload;
	float		timeHit;
	bool		isHit;
	bool		isHitAnim;
	float		timeHitAnim;
	bool		godMode;
	Vector2		rotationForMouse;
	Vector2		rotationForMouseBefore;
	GameObject*	firePos;
};

