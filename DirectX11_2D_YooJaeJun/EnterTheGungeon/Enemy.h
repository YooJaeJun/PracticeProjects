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
		virtual void ColToggle() override;

	private:
		float		timeSetMoveDir;
		float		timeSetTargetDir;
		float		pushedScalar;
		float		timeAiming;

	protected:

	public:
		float		timeSetDir;
		Weapon*		weapon;
	};
}