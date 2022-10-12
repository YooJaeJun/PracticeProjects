#pragma once

namespace Gungeon
{
	class Enemy1 : public Enemy
	{
	public:
		Enemy1();
		virtual void Init() override;
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void InitVar();
		void InitSelf();
		void InitWeapon();
		void InitBullet();

	public:
		Enemy* kin;
	};
}