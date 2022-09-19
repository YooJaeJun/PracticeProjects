#pragma once
const int bossBulletMax = 60;

class Boss : public Unit
{
public:
	Boss();

	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

public:
	UI*				hpGuage;
	EnemyBullet*	bullet[bossBulletMax];
};

