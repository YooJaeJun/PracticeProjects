#pragma once

namespace Gungeon
{
	class Weapon : public Character
	{
	public:
		Weapon();

		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void EquipRight();
		void EquipLeft();

	public:
		ObImage*	idle;
		GameObject* firePos;
		Effect*		fireEffect;
		float		timeFireEffect;
	};
}