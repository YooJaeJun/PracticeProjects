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
		void InitVar();
		void InitBullet();
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void ResizeScreen() override;

		virtual void Idle() override;
		virtual void Die() override;
		void PatternCircular();
		void PatternString();
		virtual void Hit(const int damage) override;
		void Hitting();
		virtual void StartDie() override;

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