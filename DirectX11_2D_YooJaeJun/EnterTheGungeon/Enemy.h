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
		void Fire();
		void Hit(const int damage, const Vector2& dir);
		void Hitting();
		virtual void StartDie() override;
		virtual void Spawn(const Vector2 wpos) override;

	private:
		WeaponData*		weapon;
		float			timeSetMoveDir;
		float			timeSetTargetDir;
		float			pushedScalar;
		float			pushedScalarFactor;
		float			timeAiming;

	public:
		float			timeSetDir;
	};
}