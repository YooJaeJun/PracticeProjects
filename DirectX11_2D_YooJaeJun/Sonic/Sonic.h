#pragma once
enum class State
{
	RUN,
	JUMP,
	SPIN
};

class Sonic : public Character
{
public:
	ObImage*	run;
	ObImage*	spin;
	State		state;
	float		gravity;
	bool		doubleJump;
	bool		hit;
	float		timerHit;

public:
	Sonic();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

	void LandOn();
	void Hit();
};

