#pragma once
#define MAX 20

class Main : public Scene
{
private:
	ObRect		player;
	ObCircle	pet;
	Bullet		bullet[MAX];
	ObRect		shootVelocityGauge;
	ObRect		shootVelocityGaugeFrame;

public:
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
