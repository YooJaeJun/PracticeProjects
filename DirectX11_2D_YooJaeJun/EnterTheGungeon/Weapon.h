#pragma once

namespace Gungeon
{
	enum class WeaponType
	{
		pistol,
		shotgun,
		machineGun,
		max
	};

	class Weapon : public Item
	{
	public:
		Weapon();
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void ResizeScreen() override;

		void Equip();
		void EquipRight();
		void EquipLeft();

	private:
		void SwapUvY();

	public:
		GameObject* firePos = nullptr;
		Effect*		fireEffect = nullptr;
		float		timeFireEffect = 0.0f;
		Vector2		pivotDefault;
		Vector2		localPosDefault;
		Vector2		localFirePosDefault;
		ObImage*	imgReloading = nullptr;
		UI*			uiWeaponFrame = nullptr;
		UI*			uiWeapon = nullptr;
		UI*			uiBulletFrame = nullptr;
		vector<UI*>	uiBullet;
		UI*			uiBulletCount = nullptr;
		int			bulletCount = 0;
		WeaponType	type = WeaponType::pistol;
		float		intervalFire;

	};
}