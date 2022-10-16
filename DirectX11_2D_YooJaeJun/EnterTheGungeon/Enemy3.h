#pragma once

namespace Gungeon
{
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
		float				timeBulletTarget = 0.0f;
		Vector2				spawnPos;
		float				timeBulletZ = 0.0f;
		float				timeBulletCircle = 0.0f;
		float				timeAttackToWalk = 0.0f;
		int					curBulletIdx = 0;
		int					curBulletX = 0;
		int					curBulletY = 0;
	};
}