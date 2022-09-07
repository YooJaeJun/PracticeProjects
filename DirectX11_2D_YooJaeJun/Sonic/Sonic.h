#pragma once
enum class State { run, spin, jump, doubleJump };

class Sonic : public Character
{
public:
	ObImage*	run;
	ObImage*	spin;

	State		state;

	float		timerRun;
	float		intervalRun;
	float		timerSpin;
	float		intervalSpin;
	float		timerSpin2;
	float		intervalSpin2;

	float		gravity;
	bool		onGround;
	Vector2		lastPos;
	State		lastState;

	bool		hit;
	float		timerHit;
	float		intervalHit;

	Vector2		camOriginPos;
	
public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	void SpinAnim();
	void Fall();
	void Hit();
};

