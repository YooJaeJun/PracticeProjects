#pragma once
enum class State
{
	idle,
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
	virtual void Idle();
	virtual void Die();
	virtual void Hit(const int damage);
	void ToDie();
	void SetMoveDir();
	void SetTargetDir();

public:
	ObImage*	idle[8];
	ObImage*	walk[8];
	ObImage*	kick[8];
	ObImage*	hit;
	ObImage*	fall;
	ObImage*	die;
	Weapon*		weapon;
	ObImage*	shadow;
	State		state;
	dirState	curMoveDirState;
	dirState	curMoveDirStateBefore;
	dirState	curTargetDirState;
	dirState	curTargetDirStateBefore;
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

