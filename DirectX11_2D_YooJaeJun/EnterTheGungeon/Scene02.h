#pragma once

namespace Gungeon
{
	const int enemyMax = 3;
	const int bossMax = 1;

	class Scene02 : public Scene
	{
	private:
		Vector2				room0Pos;
		MapObject*			mapObj;
		Player*				player;
		Enemy*				enemy[enemyMax];
		Boss*				boss;

	public:
		ProcedureMapGeneration* mapGen;

	public:
		Scene02();
		~Scene02();

		virtual void Init() override;
		void InitEnemy();
		void InitBoss();
		void InitMapObject();
		void Spawn();
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void ResizeScreen() override;
	};
}