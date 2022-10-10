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
		enteringFirstRoom,
		// ���� �ݺ��Ǵ� ����
		waitingSpawn,
		fight,
		cleared
	};

	class Scene02 : public Scene
	{
	private:
		GameState		gameState;
		MapObject*		mapObj;
		Player*			player;
		Enemy*			enemy[enemyMax];
		Boss*			boss;

	public:
		ProcedureMapGeneration* mapGen;
		Room*					curRoom;
		int						curRoomIdx;
		Effect*					spawnEffect[4];
		bool					fadeOut;
		float					timeFade;

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
		void EnteringFirstRoom();
		void WaitingSpawn();
		void Fight();
		void Cleared();

		void SpawnPlayer();
		void SpawnEffect();
		void SpawnEnemy();
		void ColOnOff();

		void IntersectPlayer();
		void IntersectEnemy();
		void IntersectBoss();
		void IntersectMapObj();

		void ChangeUpdateScene();
	};
}