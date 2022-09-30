#pragma once

namespace Gungeon
{
	const int patternMax = 4;
	const int circularMax = 60;
	const int stormMax = 60;

	enum class BossPattern
	{
		none, 
		circular, 
		string, 
		storm
	};

	class Boss : public Unit
	{
	public:
		Boss();

		virtual void Init() override;
		void InitVar();
		void InitBullet();
		void InitBulletOne(BossBullet* elem);
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void ResizeScreen() override;

		void Idle();
		virtual void Die() override;
		void PatternCircular();
		void PatternString();
		void PatternStorm();
		virtual void Hit(const int damage) override;
		void Hitting();
		virtual void StartDie() override;

	public:
		UI*							hpGuageBar;
		UI*							hpGuage;
		std::vector<BossBullet*>	bullet;
		BossPattern                 pattern;
		StringBulletData            stringBullet;
		float						timeSetMoveDir;
		float						timeSetTargetDir;
	};
}