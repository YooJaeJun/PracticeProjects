#pragma once

namespace Gungeon
{
	enum class EnemyFireState
	{
		none,
		z,
		circle,
		target,
		toWalk
	};

	class Enemy : public Unit
	{
	public:
		Enemy();
		virtual void Init() override;
		void InitVar();
		void InitSelf();
		void InitItem();
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void Idle();
		void Walk();
		virtual void Die() override;
		virtual void Fire();
		void Hit(const int damage, const Vector2& dir);
		void Hitting();
		virtual void StartDie() override;
		virtual void Spawn(const Vector2 wpos) override;
		virtual void Attack();
		void AttackStart();
		void AttackEnd();
		void AttackToWalk();
		virtual void InitFireCycle();
		virtual void ColToggle() override;

	private:
		float			timeSetMoveDir = 0.0f;
		float			timeSetTargetDir = 0.0f;
		float			pushedScalar = 400.0f;
		float			timeAiming = 0.0f;

	protected:
		float			intervalFire = 0.0f;

	public:
		float			timeSetDir = 0.0f;
		Weapon*			weapon = nullptr;
		EnemyFireState	fireState = EnemyFireState::none;
	};
}