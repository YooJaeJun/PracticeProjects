#pragma once

namespace Gungeon
{
	class BossBullet : public Bullet
	{
	public:
		BossBullet();

		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void Spawn(const Vector2& coord);
		virtual void Reload() override;
	};
}