#pragma once
class Brick : public NonMover
{
public:
	int		life;
	float	hitTime;
	eState	state;
	bool	trigger;

public:
	Brick() = default;

	void Hit();
	void HitEffect();
};

