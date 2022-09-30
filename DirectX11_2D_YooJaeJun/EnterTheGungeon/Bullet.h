#pragma once

namespace Gungeon
{
	const float defaultSpawnPos = 3000.0f;

	class Bullet : public Character
	{
	public:
		Bullet();

		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void Spawn(const Vector2& coord, const Vector2& fireDir);
		void Hit(const float damage);
		virtual void Reload();

	public:
		ObImage*	idle;
		bool		isFired;
		Vector2		moveDir;
		int			damage;
		float		timeRespawn;
		Effect*		hitBomb;
	};
}