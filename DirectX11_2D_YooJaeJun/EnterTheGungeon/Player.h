#pragma once

namespace Gungeon
{
	const int curWeaponMax = 3;
	const int dustMax = 2;

	class Player : public Unit
	{
	public:
		Player();
		virtual void Init() override;
		void InitVar();
		void InitCol();
		void InitAnim();
		void InitWeapon();
		void InitBullet();
		void InitEffect();
		void InitUI();
		virtual void Release() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void ResizeScreen() override;
		void SetTargetAndCamera();
		void Idle();
		void Walk();
		void Roll();
		virtual void Die() override;
		void Move();
		void SetFireInterval();
		void FireProcess();
		void Fire();
		void ShakeCam(float& time);
		void StartWalk();
		void StartIdle();
		void StartRoll();
		virtual void StartDie() override;
		void Reloading();
		void Hitting();
		void Dusting();
		void DecreaseHeart();
		void PlusMoney(const int n);
		void EquipWeapon(Weapon* other);
		virtual void ColToggle() override;

	public:
		ObImage*			roll;
		ObImage*			kick;
		ObImage*			obtain;
		Weapon*				weapons[curWeaponMax];
		int					curWeaponMax;
		int					curWeaponIdx;
		bool				canFireOnce[(int)WeaponType::max + 1];
		float				fireInterval;
		bool				isReloading;
		float				timeReload;
		int					curBulletIdx;
		float				timeRoll;
		bool				flagFireCamShake;
		float				timeFireCamShake;
		float				timeHitCamShake;
		UI*					uiReload;
		UI*					uiReloadBar;
		bool				godMode;
		float				timeLastPosForDust;
		Effect*				dust[dustMax];
		int					curDustIdx;
		UI*					uiWeaponFrame;
		vector<UI*>			uiHeartFull;
		vector<UI*>			uiHeartHalf;
		vector<UI*>			uiHeartNone;
		vector<UI*>			uiBlank;
		UI*					uiKey;
		UI*					uiGold;
		UI*					uiFireBottle;
		UI*					uiFireBottleFrame;
		int					money;
		int					key;
	};
}