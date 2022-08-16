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
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
