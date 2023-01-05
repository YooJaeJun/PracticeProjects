#pragma once
class Player : public Unit
{
public:
	ObRect		firePos;
	ObRect		muzzle;
	ObRect		shootGauge;
	ObRect		shootGaugeFrame;
	ObRect		hpGauge;
	ObRect		hpGaugeFrame;
	ObCircle	wheels[2];
	ObRect		wheelProps[2];
	Color		hitboxColor;
	Color		muzzleColor;
	Color		wheelColor;
	Color		wheelPropColor;

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

