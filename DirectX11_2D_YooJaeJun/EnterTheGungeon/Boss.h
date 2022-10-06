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
		void Hit(const int damage, const Vector2& dir);
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
		WeaponData*				weapon;
		Weapon*					w;		// data index 실수 막기 위함
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
		float					timeWave;
	};
}