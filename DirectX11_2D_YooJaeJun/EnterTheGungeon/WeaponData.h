#pragma once

namespace Gungeon
{
	const int weaponTypeMax = 2;

	class WeaponData
	{
	public:
		WeaponData();

	public:
		Weapon*		data[weaponTypeMax];
	};
}