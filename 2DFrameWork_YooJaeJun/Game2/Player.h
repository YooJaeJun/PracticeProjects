#pragma once
class Player : public Unit
{
public:
	GameObject	firePos;
	ObRect		muzzle;
	ObRect		shootGauge;
	ObRect		shootGaugeFrame;
	ObRect		hpGauge;
	ObRect		hpGaugeFrame;

public:
	Player();
	void Init() override;
	void Update() override;
	bool LateUpdate() override;
	void Render() override;
	void Move();
	void GaugeUp();
	void Down();
	bool HitFrom(const float damage) override;
};

