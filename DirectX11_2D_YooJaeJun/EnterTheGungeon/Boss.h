#pragma once

namespace Gungeon
{
	enum class BossPattern
	{
		none,
		circular,
		string,
		shield,
		spiral,
		cluster,
		wave,
		max
	};

	const int patternMax = static_cast<int>(BossPattern::max) - 1;
	const int circularMax = 60;
	const int shieldMax = 60;
	const int spiralMax = 60;
	const int clusterMax = 10;
	const int waveMax = 100;

	class Boss : public Unit
	{
	public:
		Boss();
		virtual void Init() override;
		void InitVar();
		void InitSelf();
		void InitWeapon();
		void InitBullet();
		void InitItem();
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

		void ChangePattern(const int curPattern);
		void InitCircular();
		void InitString();
		void InitShield();
		void InitSpiral();
		void InitCluster();
		void InitWave();
		void UpdateBullet();
		void UpdateCircular();
		void UpdateString();
		void UpdateShield();
		void UpdateSpiral();
		void UpdateCluster();
		void UpdateWave();

	public:
		UI*						hpGuageBar;
		UI*						hpGuage;
		vector<BossBullet*>		bullet;
		BossPattern             pattern;
		StringBulletData        stringBullet;
		float					timeSetMoveDir;
		float					timeSetTargetDir;
		float					timeSpiral;
		float					timeSpiralOne;
		bool					flagSpiralRespawn;
		float					timeCluster;
		float					timeWave;
	};
}