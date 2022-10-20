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
		void Cinematic();
		void Move();
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
		void SetWeaponFrameToOrigin();
		virtual void ColToggle() override;

	public:
		ObImage*			roll = nullptr;
		ObImage*			kick = nullptr;
		ObImage*			obtain = nullptr;
		Weapon*				weapons[curWeaponMax];
		int					curWeaponMax = 0;
		int					curWeaponIdx = 0;
		bool				canFireOnce[(int)WeaponType::max];
		bool				isReloading = false;
		float				timeReload = 0.0f;
		int					curBulletIdx = 0;
		float				timeRoll = 0.0f;
		bool				flagFireCamShake = false;
		float				timeFireCamShake = 0.0f;
		float				timeHitCamShake = 0.0f;
		UI*					uiReload = nullptr;
		UI*					uiReloadBar = nullptr;
		bool				godMode = false;
		float				timeLastPosForDust = 0.0f;
		Effect*				dust[dustMax];
		int					curDustIdx = 0;
		UI*					uiWeaponFrame = nullptr;
		vector<UI*>			uiHeartFull;
		vector<UI*>			uiHeartHalf;
		vector<UI*>			uiHeartNone;
		vector<UI*>			uiBlank;
		UI*					uiKey = nullptr;
		UI*					uiGold = nullptr;
		int					money = 0;
		int					key = 0;
		bool				flagLbutton = false;
		float				timeWeaponFrameToOrigin = 0.0f;
	};
}