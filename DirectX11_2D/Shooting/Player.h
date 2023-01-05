#pragma once
const int bulletMax = 20;

class Player : public Airplane
{
public:
	ObImage*		boost;
	bool			isBoost;
	PlayerBullet*	bullet[bulletMax];
	int				level;
	float			timeFire;
	float			timeReload;

public:
	Player();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	virtual void Spawn() override;
	virtual void Hit(const float damage) override;
	virtual void Die() override;
	void Boost();
	void CancelBoost();
};

