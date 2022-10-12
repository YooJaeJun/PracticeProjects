#pragma once

namespace Gungeon
{
	const int enemyMax = 3;
	const int bossMax = 1;

	enum class GameState
	{
		// �� ���� ��ٸ��� ����
		start,
		waitingRoom,
		enteringRoom,
		// ���� �ݺ��Ǵ� ����
		waitingSpawn,
		fight
	};

	class Scene02 : public Scene
	{
	private:
		GameState				gameState;
		Enemy*					enemy[enemyMax];

	public:
		ProcedureMapGeneration* mapGen;
		Room*					curRoom;
		int						curRoomIdx;
		vector<Effect*>			spawnEffect;
		bool					fadeOut;
		float					timeFade;
		int						afterRoomIdx;
		Player*					player;

	public:
		Scene02();
		~Scene02();

		virtual void Init() override;
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void ResizeScreen() override;

		void Start();
		void WaitingRoom();
		void EnteringRoom();
		void WaitingSpawn();
		void Fight();

		void SpawnPlayer();
		void SpawnEffect();
		void SpawnEnemy();

		void IntersectPlayer();
		void IntersectEnemy();

		void ChangeUpdateScene();

		void ColOnOff();
	};
}