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

public:
	EnemyBullet*	bullet[enemyBulletMax];
};

