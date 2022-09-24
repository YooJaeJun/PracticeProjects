#pragma once
const int circularBulletMax = 200;

enum class BossPattern
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
	virtual void Idle() override;
	virtual void Die() override;
	virtual void Hit(const int damage) override;

public:
	UI*							hpGuageBar;
	UI*							hpGuage;
	std::vector<BossBullet*>	bullet;
    BossPattern                 pattern;
	StringBulletData            stringBullet;
	float						timeSetDir;
};

