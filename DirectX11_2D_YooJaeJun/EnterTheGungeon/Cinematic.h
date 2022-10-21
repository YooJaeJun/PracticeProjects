#pragma once

namespace Gungeon
{
	enum class CinematicState
	{
		none,
		// ���� ����
		cinematicBox1,
		cameraTargeting1,
		bossSpawnAnim,
		cutScene,
		cameraTargeting2,
		cinematicBox2,
		finish,
		// ���� ���
		cinematicBox3,
		cameraTargeting3,
		bossDieAnim,
		cameraTargeting4,
		cinematicBox4,
		finish2,
		clear,
		max
	};

	class Cinematic
	{
	public:
		Cinematic();
		void Init();
		void Release();
		void Update();
		void Render();

	public:
		CinematicState cinematicState = CinematicState::none;
		UI* cinematicBox[2];
		float timeCinematic[(int)CinematicState::max];
		float intervalCinematic[(int)CinematicState::max];
	};
}
