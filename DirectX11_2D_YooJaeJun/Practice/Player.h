#pragma once
enum class PlState
{
	IDLE,
	WALK
};

class Player : public Character
{
public:
	ObImage* walk;
	PlState plState;

public:
	Player();
	~Player();

	void Update();
	void Render();

	void Input();
	void LookTarget();

	void Idle();
	void Walk();
};

