#pragma once
const int weapon0BulletMax = 5;

class Player : public Unit
{
public:
	Player();

	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Idle() override;
	void Roll();
	virtual void Die() override;

public:
	ObImage*		roll[8];
	ObImage*		respawn;
	ObImage*		kick;
	ObImage*		obtain;
	PlayerBullet*	bullet[weapon0BulletMax];
	bool			canFire;
	bool			reloading;
	float			timeReload;
	int				curBulletIdx;
	float			timeRoll;
	bool			flagFireCamShake;
	Vector2			originCamPos;
	float			timeFireCamShake;
	UI*				uiReload;
	UI*				uiReloadBar;
	UI*				uiMagazine;
	UI*				uiBullet[weapon0BulletMax];
	UI*				uiWeaponFrame;
	UI*				uiWeapon;
	UI*				uiBulletCount;
	Weapon*			weaponReloading;
	bool			godMode;
};

