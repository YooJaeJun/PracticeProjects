#pragma once

namespace Gungeon
{
	const int doorOpenMax = 10;
	const int doorClosedMax = 5;

	class MapObject : public Character
	{
	public:
		MapObject();
		void Release();
		void Update();
		void LateUpdate();
		void Render();

	public:
		Obstacle* doorOpenUp[doorOpenMax];
		Obstacle* doorOpenDown[doorOpenMax];
		Obstacle* doorClosed[doorClosedMax];
	};
}

