#pragma once

namespace Gungeon
{
	class Effect : public Character
	{
	public:
		Effect();
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void Spawn(const Vector2 wpos) override;
		void Idle();
		void Die();

	public:
		ObImage*	idle;
		float		timeDie;
		float		intervalDie;
	};
}