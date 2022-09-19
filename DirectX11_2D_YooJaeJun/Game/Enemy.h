#pragma once
const int enemyBulletMax = 20;

class Enemy : public Character
{
public:
	Enemy();

	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	void Move(const Vector2& dir);

public:
	ObImage*		idle;
	ObImage*		hit;
	ObImage*		walk;
	ObImage*		die;
	UI*				hpGuage;
	EnemyBullet*	bullet[enemyBulletMax];
	State			state;
	float			timeFire;
	float			timeReload;
	float			timeHit;
	bool			isHit;
	bool			isHitAnim;
	float			timeHitAnim;

};

