#pragma once
#define MAX 30

class Main : public Scene
{
private:
	ObRect		player;
	ObCircle	pet;

	ObRect		playerShootGauge;
	ObRect		playerShootGaugeFrame;
	Bullet		bullets[MAX];
	Vector2		lastPos;

	GameObject	firePos;

	ObLine		xAxis;
	ObLine		yAxis;

public:
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
