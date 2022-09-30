#pragma once

namespace Gungeon
{
	const int enemyBulletMax = 20;

	class Enemy : public Unit
	{
	public:
		Enemy();

		virtual void Init() override;
		void InitVar();
		void InitBullet();
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void Idle() override;
		virtual void Die() override;
		void IdleOrWalkVisible();
		void Fire();
		void Hit(const int damage, const Vector2& dir);
		void Hitting();
		virtual void StartDie() override;
		//void FindPath(ObTileMap* map);

	private:
		vector<Tile*>	way;
		Vector2			start;
		Vector2			end;
		float			g;	// ∫Ò¿≤
		float			timeFindPath;
		float			timeSetMoveDir;
		float			timeSetTargetDir;
		Vector2			pushedDir;
		float			pushedScalar;
		float			pushedScalarCoef;

	public:
		EnemyBullet* bullet[enemyBulletMax];
		float			timeSetDir;
	};
}