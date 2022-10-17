#pragma once

namespace Gungeon
{
	const int enemyMax = 1;
	const int doorMax = 5;

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
		void SetCamera();
		void SpawnPlayer();
		void SpawnEffect();
		void SpawnEnemy();
		void IntersectPlayer();
		void IntersectEnemy();
		void GateProcess();
		void ChangeUpdateScene();
		void ColToggle();

	public:
		ProcedureMapGeneration* mapGen = nullptr;
		Player*					player = nullptr;

	private:
		Room*					curRoom = nullptr;
		GameState				gameState = GameState::start;
		Enemy*					enemy[enemyMax];
		bool					isChangingScene = false;
		float					timeFade = 0.0f;
		vector<Effect*>			spawnEffect;
		int						afterRoomIdx = -2;
		int						curRoomIdx = 0;
		int						roomClearCount = 0;
		int						roomClearCountForBossBattle = 1;
		Gate*					gate = nullptr;
		vector<Door*>			door;
	};
}