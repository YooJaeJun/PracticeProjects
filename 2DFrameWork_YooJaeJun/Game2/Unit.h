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
	Vector2		lastPos;

public:
	Unit();
	void Init(const Vector2& pos);
	void Move();
	bool HitFrom(float damage);
	void Update();
	void LateUpdate();
	void Render();
};

