#pragma once
enum class State
{
	idle,
	walk,
	roll,
	die
};

// 8πÊ«‚
enum dirState
{
	dirB,
	dirL,
	dirR,
	dirLB,
	dirRB,
	dirT,
	dirLT,
	dirRT
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
	virtual void Hit(const int damage);
	void Die();
	void SetMoveDir();
	void SetTargetDir();

public:
	ObImage*	idle[8];
	ObImage*	walk[8];
	ObImage*	roll[8];
	ObImage*	kick[8];
	ObImage*	hit;
	ObImage*	fall;
	ObImage*	die;
	Weapon*		weapon;
	ObImage*	shadow;
	State		state;
	dirState		curMove8Dir;
	dirState		curMove8DirBefore;
	dirState		curTarget8Dir;
	dirState		curTarget8DirBefore;
	Vector2		target;
	Vector2		targetDir;
	Vector2		targetDirBefore;
	float		targetRotation;
	GameObject* firePos;
	float		timeFire;
	float		timeReload;
	float		timeHit;
	bool		isHit;
	bool		isHitAnim;
	float		timeHitAnim;
};

