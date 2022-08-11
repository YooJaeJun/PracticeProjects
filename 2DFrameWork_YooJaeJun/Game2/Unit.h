#pragma once
class Unit
{
public:
	ObCircle	hitbox;

	ObRect		shootGauge;
	ObRect		shootGaugeFrame;
	ObRect		hpGauge;
	ObRect		hpGaugeFrame;

	GameObject	firePos;

	float		hitEffectTime;
	bool		hitState;

	string		name;

public:
	Unit();
	void Init();
	void Move();
	void HitFrom(float damage);
	void Update();
	void LateUpdate();
	void Render();
};

