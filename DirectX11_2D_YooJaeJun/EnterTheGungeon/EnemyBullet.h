#pragma once

namespace Gungeon
{
	class EnemyBullet : public Bullet
	{
	public:
		EnemyBullet();
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}