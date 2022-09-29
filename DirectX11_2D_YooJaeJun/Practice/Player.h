#pragma once

namespace Dir8
{
	class Player : public Character
	{
	public:
		ObImage*		walk;
		ObImage*		roll;
		float			timeRoll;
		DirState		moveDirState;
		float			scalarCoef;

	public:
		Player();
		~Player();

		void Release();
		void Update();
		void Render();

		void Input();

		void Idle();
		void Walk();
		void Roll();

		void SetMoveDir();
	};
}