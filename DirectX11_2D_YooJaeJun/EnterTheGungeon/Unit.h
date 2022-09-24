#pragma once
enum class State
{
	idle,
	roll,
	die
};

enum DirState
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

	virtual void Idle();
	virtual void Hit(const int damage);
	virtual void Killed();
	virtual void Die();
	void StepBack();
	void SetMoveDir();
	void SetTargetDir();
	vector<Vector2>& Foot();

public:
	ObImage*		idle[8];
	ObImage*		walk[8];
	ObImage*		kick[8];
	ObImage*		hit;
	ObImage*		fall;
	ObImage*		die;
	Weapon*			weapon;
	ObImage*		shadow;
	State			state;
	Vector2			lastPos;
	DirState		curMoveDirState;
	DirState		curMoveDirStateBefore;
	DirState		curTargetDirState;
	DirState		curTargetDirStateBefore;
	Vector2			targetPos;
	Vector2			targetDir;
	Vector2			targetDirBefore;
	float			targetRotation;
	GameObject*		firePos;
	float			timeFire;
	float			timeReload;
	float			timeHit;
	bool			isHit;
	bool			isHitAnim;
	float			timeHitAnim;
	float			timeDieAnim;
	vector<Vector2>	foot;
};

