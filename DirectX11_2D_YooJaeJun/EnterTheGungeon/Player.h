#pragma once

namespace Gungeon
{
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
		void Action();
		void Fire();
		void FireCamShake();
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

	public:
		ObImage*				roll[8];
		ObImage*				respawn;
		ObImage*				kick;
		ObImage*				obtain;
		vector<PlayerBullet*>	bullet;
		bool					canFireBetween;
		bool					isReloading;
		float					timeReload;
		int						curBulletIdx;
		float					timeRoll;
		bool					flagFireCamShake;
		Vector2					originCamPos;
		float					timeFireCamShake;
		UI*						uiReload;
		UI*						uiReloadBar;
		bool					godMode;
		float					timeLastPosForDust;
		Effect*					dust;
		vector<UI*>				uiHeartFull;
		vector<UI*>				uiHeartHalf;
		vector<UI*>				uiHeartNone;
		vector<UI*>				uiBlank;
		UI*						uiKey;
		UI*						uiGold;
		UI*						uiFireBottle;
		UI*						uiFireBottleFrame;
		int						money;
		int						key;
	};
}