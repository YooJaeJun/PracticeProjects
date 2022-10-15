#pragma once

namespace Gungeon
{
	enum class FireState
	{
		none,
		z,
		circle,
		target,
		toWalk
	};

	class Enemy3 : public Enemy
	{
	public:
		Enemy3();
		virtual void Init() override;
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		void InitVar();
		void InitSelf();
		void InitWeapon();
		void InitBullet();
		virtual void Fire() override;
		virtual void Attack() override;

	public:
		const int			bulletMax = 43;
		FireState			fireState;
		float				timeBulletTarget;
		Vector2				spawnPos;
		float				timeBulletZ;
		float				timeBulletCircle;
		float				timeAttackToWalk;
		int					curBulletIdx;
		int					curBulletX;
		int					curBulletY;
	};
}