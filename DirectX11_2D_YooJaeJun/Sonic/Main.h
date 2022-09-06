#pragma once

class Main : public Scene
{
private:
	ObRect*		sonic;
	ObImage*	run;
	ObImage*	spin;
	ObRect*		rock[3];
	ObImage*	rockImg[3];
	ObRect*		floor[10];
	ObImage*	floorImg[10];

	float		timerRun;
	float		intervalRun;
	float		frameRun;
	float		timerSpin;
	float		intervalSpin;
	float		frameSpin;
	float		timerSpin2;
	float		intervalSpin2;
	bool		flagSpin2;

	float		gravity;
	bool		onGround;
	bool		isJumping;
	bool		isDoubleJumping;

	float		speed;

	bool		hit;
	float		timerHit;
	float		intervalHit;

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
