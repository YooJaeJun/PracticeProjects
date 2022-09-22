#pragma once
const int circularBulletMax = 200;

enum class bossPattern
{
	none, circular, string
};

class Boss : public Unit
{
public:
	Boss();

	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	void SetPattern();
	virtual void Hit(const int damage) override;

public:
	UI*				            hpGuage;
	std::vector<BossBullet*>	bullet;
    bossPattern                 pattern;
	StringBulletData            stringBullet;
	float						timeSetDir;
};

