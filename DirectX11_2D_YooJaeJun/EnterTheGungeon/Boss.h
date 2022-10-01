#pragma once

namespace Gungeon
{
	enum class BossPattern
	{
		none,
		circular,
		string,
		storm,
		tornado,
		rand,
		max
	};
	const int patternMax = static_cast<int>(BossPattern::max) - 1;
	const int circularMax = 60;
	const int stormMax = 60;
	const int tornadoMax = 60;
	const int randMax = 10;

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

		void Idle();
		void Walk();
		virtual void Die() override;
		void StartWalk();
		void StartIdle();
		virtual void Hit(const int damage) override;
		void Hitting();
		virtual void StartDie() override;

		void InitCircular();
		void InitString();
		void InitStorm();
		void InitTornado();
		void InitRand();
		void InitBulletOne(BossBullet* elem);
		void UpdateBullet();
		void UpdateCircular();
		void UpdateString();
		void UpdateStorm();
		void UpdateTornado();
		void UpdateRand();

	public:
		UI*							hpGuageBar;
		UI*							hpGuage;
		std::vector<BossBullet*>	bullet;
		BossPattern                 pattern;
		StringBulletData            stringBullet;
		float						timeSetMoveDir;
		float						timeSetTargetDir;
		float						timeTornado;
		float						timeTornadoOne;
		bool						flagTornadoRespawn;
		float						timeRand;
	};
}