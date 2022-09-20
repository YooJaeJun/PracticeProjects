#pragma once
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
	ObImage*	idle;
	ObImage*	walk;
	ObImage*	roll;
	ObImage*	hit;
	ObImage*	die;
	Weapon*		weapon;
	Vector2		dest;
	float		timeFire;
	float		timeReload;
	float		timeHit;
	bool		isHit;
	bool		isHitAnim;
	float		timeHitAnim;
	bool		godMode;
};

