#pragma once

namespace Gungeon
{
	class BossBullet : public Bullet
	{
	public:
		BossBullet();
		virtual void Init() override;
		virtual void Release() override;
		virtual void Update() override;
		virtual void Update(const bool notRotation) override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void Reload() override;
	};
}