#pragma once

namespace Gungeon
{
	class Enemy : public Unit
	{
	public:
		Enemy();
		virtual void Init() override;
		void InitVar();
		void InitSelf();
		void InitWeapon();
		void InitBullet();
		void InitItem();
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void Idle();
		void Walk();
		virtual void Die() override;
		void StartWalk();
		void StartIdle();
		void Fire();
		void Hit(const int damage, const Vector2& dir);
		void Hitting();
		virtual void StartDie() override;

	private:
		float					timeSetMoveDir;
		float					timeSetTargetDir;
		Vector2					pushedDir;
		float					pushedScalar;
		float					pushedScalarCoef;
		float					timeAiming;

	public:
		vector<EnemyBullet*>	bullet;
		float					timeSetDir;
	};
}