#pragma once

namespace Gungeon
{
	class TreasureBox : public Obstacle
	{
	public:
		TreasureBox();
		virtual void Init() override;
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	public:
		Weapon* weaponA = nullptr;
		Weapon* weaponB = nullptr;
	};
}
