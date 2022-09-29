#pragma once

namespace Dir8
{
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

	enum class CharacterState
	{
		IDLE,
		WALK,
		ROLL
	};

	class Character
	{
	public:
		ObRect*			col;
		Vector2			moveDir;
		Vector2			targetDir;
		float			scalar;
		DirState		targetDirstate;
		int				frameY[8];
		CharacterState	state;

	public:
		Character();

		virtual void LookTarget();
	};
}