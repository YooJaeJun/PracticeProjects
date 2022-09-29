#pragma once

namespace Gungeon
{
	const int circularBulletMax = 60;

	enum class BossPattern
	{
		none, circular, string
	};

	class Boss : public Unit
	{
	public:
		Boss();

		virtual void Init() override;
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void ResizeScreen() override;

		void SetPattern();
		virtual void Idle() override;
		virtual void Hit(const int damage) override;
		virtual void Killed() override;
		virtual void Die() override;

	public:
		UI* hpGuageBar;
		UI* hpGuage;
		std::vector<BossBullet*>	bullet;
		BossPattern                 pattern;
		StringBulletData            stringBullet;
		float						timeSetMoveDir;
		float						timeSetTargetDir;
	};
}