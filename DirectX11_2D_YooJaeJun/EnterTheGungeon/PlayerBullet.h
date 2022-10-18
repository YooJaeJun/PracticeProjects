#pragma once

namespace Gungeon
{
	class PlayerBullet : public Bullet
	{
	public:
		PlayerBullet();
		virtual void Init() override;
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}