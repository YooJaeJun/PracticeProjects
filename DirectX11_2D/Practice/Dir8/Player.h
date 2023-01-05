#pragma once

namespace Dir8
{
	enum class PlayerState
	{
		IDLE,
		WALK,
		ROLL,
	};

	class Player : public Character
	{
	public:
		PlayerState		state;
		ObImage*		walk;
		ObImage*		roll;
		float			timeRoll;
		ObRect*			colTile;
		Vector2			lastPos;

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

		bool IntersectTile(ObTileMap* tilemap);
		void StepBack();
	};
}