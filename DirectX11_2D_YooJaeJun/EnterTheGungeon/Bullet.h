#pragma once

namespace Gungeon
{
	class Bullet : public Character
	{
	public:
		Bullet();
		virtual void Init() override;
		virtual void Release() override;
		virtual void Update() override;
		virtual void Update(const bool notRotation) override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void Spawn(const Vector2& coord);
		void Spawn(const Vector2& coord, const Vector2& fireDir);
		void Hit(const float damage);
		virtual void Reload();

	public:
		ObImage*	idle = nullptr;
		bool		isFired = false;
		Vector2		moveDir;
		int			damage = 1;
		float		timeRespawn = 0.0f;
		Effect*		hitBomb = nullptr;
		float		angle = 0.0f;
		float		atkAngle = 0.0f;
		float		moveFactor = 1.0f;
		float		timeLife = 0.0f;
		float		intervalLife = 10.0f;
	};
}