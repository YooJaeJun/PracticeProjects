#pragma once
class Boss : public Character
{
public:
	ObImage* walk;

public:
	Boss();
	~Boss();

	void Update();
	void Render();

	void LookTarget();

	void Idle();
	void Walk();
};

