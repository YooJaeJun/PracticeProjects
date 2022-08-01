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
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
