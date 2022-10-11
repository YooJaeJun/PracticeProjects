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
		brute,
		rand,
		max
	};

	const int patternMax = static_cast<int>(BossPattern::max) - 1;
	const int circularMax = 60;
	const int shieldMax = 60;
	const int spiralMax = 60;
	const int clusterMax = 10;
	const int bruteMax = 720;
	const int randMax = 400;

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
		void Hit(const int damage, const Vector2& dir);
		void Hitting();
		virtual void StartDie() override;
		virtual void Spawn(const Vector2 wpos) override;

		void ChangePattern(const int curPattern);
		void InitCircular();
		void InitString();
		void InitShield();
		void InitSpiral();
		void InitCluster();
		void InitBrute();
		void InitRand();
		void UpdateBullet();
		void UpdateCircular();
		void UpdateString();
		void UpdateShield();
		void UpdateSpiral();
		void UpdateCluster();
		void UpdateBrute();
		void UpdateRand();

	public:
		WeaponData*				weapon;
		UI*						hpGuageBar;
		UI*						hpGuage;
		vector<Bullet*>			bullet;
		BossPattern             pattern;
		StringBulletData        stringBullet;
		Vector2					bulletSpawnPos;
		Vector2					bulletSpawnDir;
		float					timeSetMoveDir;
		float					timeSetTargetDir;
		float					timeSpiral;
		float					curSpiralIdx;
		bool					flagSpiralRespawn;
		float					timeCluster;
		float					timeBrute;
		float					timeRand;
		int						curRandIdx;
	};
}