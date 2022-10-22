#pragma once

namespace Gungeon
{
	enum class TreasureState
	{
		none,
		spawn,
		opening,
		dropping,
		finish
	};

	const int treasureWeaponNum = 2;

	class TreasureBox : public Obstacle
	{
	public:
		TreasureBox();
		virtual void Init() override;
		virtual void Release() override;
		virtual void Update() override;
		virtual void Render() override;

	public:
		ObImage*	open = nullptr;
		TreasureState treasureState = TreasureState::none;
		Weapon*		weapon[treasureWeaponNum];
		Vector2		weaponDest[treasureWeaponNum];
	};
}
