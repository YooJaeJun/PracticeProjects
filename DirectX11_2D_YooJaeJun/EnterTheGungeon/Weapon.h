#pragma once

namespace Gungeon
{
	enum class WeaponType
	{
		pistol,
		shotgun
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
		GameObject* firePos;
		Effect*		fireEffect;
		float		timeFireEffect;
		Vector2		pivotDefault;
		Vector2		localPosDefault;
		Vector2		localFirePosDefault;
		ObImage*	imgReloading;
		UI*			uiWeaponFrame;
		UI*			uiWeapon;
		UI*			uiBulletFrame;
		vector<UI*>	uiBullet;
		UI*			uiBulletCount;
		int			bulletCount;
		WeaponType	type;
	};
}