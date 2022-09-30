#pragma once

namespace Dir8
{
	enum class BossState
	{
		IDLE = 400,
		LOOK = 300,
		MOVE = 200,
		ATTACK = 100
	};

	class Boss : public Character
	{
	public:
		BossState	state;
		ObImage*	img;
		ObCircle*	range[3];
		Vector2		targetPos;
		float		distance;
		bool		switching;

	public:
		Boss();
		~Boss();

		void Release();
		void Update();
		void Render();

		void Idle();
		void Look();
		void Move();
		void Attack();
	};
}

