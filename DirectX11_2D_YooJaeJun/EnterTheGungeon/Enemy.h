#pragma once
const int enemyBulletMax = 20;

class Enemy : public Unit
{
public:
	Enemy();

	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	virtual void Idle() override;
	virtual void Die() override;
	virtual void Hit(const int damage) override;

public:
	EnemyBullet*	bullet[enemyBulletMax];
	float			timeSetDir;
};

