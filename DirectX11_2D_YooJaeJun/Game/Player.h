#pragma once
const int playerBulletMax = 20;

class Player : public Unit
{
public:
	Player();

	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

public:
	ObImage*		respawn;
	PlayerBullet*	bullet[playerBulletMax];
	bool			canFire;
	float			timeRoll;
};

