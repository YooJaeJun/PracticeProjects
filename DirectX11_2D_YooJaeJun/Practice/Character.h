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

	class Character
	{
	public:
		ObRect*			col;
		Vector2			moveDir;
		Vector2			targetDir;
		float			scalar;
		int				frameY[8];
		DirState		dirState;

	public:
		Character() = default;

		void LookTarget(Vector2 target, ObImage* img);
		
		Vector2 GetPos() { return col->GetWorldPos(); }
	};
}