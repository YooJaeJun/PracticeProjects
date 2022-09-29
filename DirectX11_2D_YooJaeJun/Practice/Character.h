#pragma once
enum DirState
{
	DIR_L,
	DIR_R,
	DIR_T,
	DIR_B,
	DIR_LT,
	DIR_LB,
	DIR_RT,
	DIR_RB
};

class Character
{
public:
	ObRect* col;

	Vector2 moveDir;
	float scalar;

	DirState dirstate;
	int frameY[8];
};

