#pragma once

namespace Gungeon
{
	const int enemyMax = 3;
	const int bossMax = 1;
	const int doorMax = 4;

	enum class GameState
	{
		// �� ���� ��ٸ��� ����
		start,
		waitingRoom,
		// ���� �ݺ��Ǵ� ����
		enteringRoom,
		waitingSpawn,
		fight
	};

	class Scene02 : public Scene
	{
	public:
		Scene02();
		~Scene02();

	protected:
		virtual void Init() override;
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void ResizeScreen() override;

	private:
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
		void GateProcess();
		void ChangeUpdateScene();
		void ColOnOff();

	public:
		ProcedureMapGeneration* mapGen;
		Player*					player;

	private:
		Room*					curRoom;
		GameState				gameState;
		Enemy*					enemy[enemyMax];
		bool					fadeOut;
		float					timeFade;
		vector<Effect*>			spawnEffect;
		int						afterRoomIdx;
		int						curRoomIdx;
		int						roomClearCount;
		int						roomClearCountForBossBattle;
		Gate*					gate;
		ObRect*					cinematicBox[2];
		vector<Door*>			door;
	};
}