#pragma once

namespace Gungeon
{
	class Enemy2 : public Enemy
	{
	public:
		Enemy2();
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

	public:
		const int	bulletMax = 25;
		int			curBulletIdx;
	};
}