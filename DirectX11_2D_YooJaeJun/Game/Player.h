#pragma once
const int playerBulletMax = 5;

class Player : public Character
{
public:
	Player();

	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	void Spawn();
	void Hit(const float damage);
	void Die();

public:
	ObImage*		idle;
	ObImage*		walk;
	ObImage*		roll;
	ObImage*		hit;
	ObImage*		die;
	ObImage*		respawn;
	Weapon*			weapon;
	PlayerBullet*	bullet[playerBulletMax];
	State			state;
	bool			canFire;
	float			timeFire;
	float			timeReload;
	float			timeHit;
	bool			isHit;
	bool			isHitAnim;
	float			timeHitAnim;

};

