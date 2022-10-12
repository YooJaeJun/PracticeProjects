#pragma once

namespace Gungeon
{
	const int enemyMax = 3;
	const int bossMax = 1;

	enum class GameState
	{
		// 맵 생성 기다리는 상태
		start,
		waitingRoom,
		enteringRoom,
		// 이하 반복되는 상태
		waitingSpawn,
		fight
	};

	class Scene02 : public Scene
	{
	private:
		GameState				gameState;
		MapObject*				mapObj;
		Player*					player;
		Enemy*					enemy[enemyMax];
		Boss*					boss;

	public:
		ProcedureMapGeneration* mapGen;
		Room*					curRoom;
		int						curRoomIdx;
		vector<Effect*>			spawnEffect;
		bool					fadeOut;
		float					timeFade;
		int						afterRoomIdx;

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
		void IntersectBoss();
		void IntersectMapObj();

		void ChangeUpdateScene();

		void ColOnOff();
	};
}