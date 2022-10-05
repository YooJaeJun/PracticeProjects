#include "stdafx.h"

namespace Gungeon
{
	Player::Player()
	{
		Init();
	}

	void Player::Init()
	{
		InitVar();
		InitCol();
		InitAnim();
		InitWeapon();
		InitBullet();
		InitEffect();
		InitUI();
	}

	void Player::InitVar()
	{
		scalar = 300.0f;
		curHp = maxHp = 6;
		canFireBetween = true;
		isReloading = false;
		timeReload = 0.0f;
		timeRoll = 0.0f;
		curBulletIdx = 4;
		timeFire = 0.0f;
		timeHit = 0.0f;
		isHit = false;
		isHitAnim = false;
		timeHitAnim = 0.0f;
		flagFireCamShake = false;
		timeFireCamShake = 0.0f;
		godMode = false;
		timeLastPosForDust = 0.0f;
		money = 0;
		key = 0;
	}

	void Player::InitCol()
	{
		float playerScaleCoef = 3.0f;
		col = new ObCircle;
		col->isFilled = false;
		col->scale.x = 12.0f * playerScaleCoef;
		col->scale.y = 12.0f * playerScaleCoef;
		col->zOrder = ZOrder::object;
		col->color = Color(1.0f, 1.0f, 1.0f);

		foot = new ObRect;
		foot->scale = Vector2(col->scale.x, col->scale.y / 2.0f);
		foot->SetParentRT(*col);
		foot->SetLocalPosY(col->GetWorldPos().y - col->scale.y / 2.0f);
		foot->isFilled = false;
		foot->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	}

	void Player::InitAnim()
	{
		int idx = 0;
		float playerScaleCoef = 3.0f;

		idle[dirB] = new ObImage(L"EnterTheGungeon/Player_0/Idle_Front.png");
		idle[dirL] = new ObImage(L"EnterTheGungeon/Player_0/Idle_Side.png");
		idle[dirR] = new ObImage(L"EnterTheGungeon/Player_0/Idle_Side.png");
		idle[dirLB] = new ObImage(L"EnterTheGungeon/Player_0/Idle_Side.png");
		idle[dirRB] = new ObImage(L"EnterTheGungeon/Player_0/Idle_Side.png");
		idle[dirT] = new ObImage(L"EnterTheGungeon/Player_0/Idle_Back.png");
		idle[dirLT] = new ObImage(L"EnterTheGungeon/Player_0/Idle_BackDiag.png");
		idle[dirRT] = new ObImage(L"EnterTheGungeon/Player_0/Idle_BackDiag.png");

		idx = 0;
		for (auto& elem : idle)
		{
			if (idx == dirL || idx == dirLB || idx == dirLT)
			{
				elem->reverseLR = true;
			}
			elem->maxFrame.x = 4;
			elem->scale.x = 72.0 / 4.0f * playerScaleCoef;
			elem->scale.y = 20.0f * playerScaleCoef;
			elem->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
			elem->SetParentRT(*col);
			elem->zOrder = ZOrder::object;
			idx++;
		}

		walk[dirB] = new ObImage(L"EnterTheGungeon/Player_0/Walk_Front.png");
		walk[dirL] = new ObImage(L"EnterTheGungeon/Player_0/Walk_Side.png");
		walk[dirR] = new ObImage(L"EnterTheGungeon/Player_0/Walk_Side.png");
		walk[dirLB] = new ObImage(L"EnterTheGungeon/Player_0/Walk_Side.png");
		walk[dirRB] = new ObImage(L"EnterTheGungeon/Player_0/Walk_Side.png");
		walk[dirT] = new ObImage(L"EnterTheGungeon/Player_0/Walk_Back.png");
		walk[dirLT] = new ObImage(L"EnterTheGungeon/Player_0/Walk_BackDiag.png");
		walk[dirRT] = new ObImage(L"EnterTheGungeon/Player_0/Walk_BackDiag.png");

		idx = 0;
		for (auto& elem : walk)
		{
			if (idx == dirL || idx == dirLB || idx == dirLT)
			{
				elem->reverseLR = true;
			}
			elem->isVisible = false;
			elem->maxFrame.x = 6;
			elem->scale.x = 102.0f / 6.0f * playerScaleCoef;
			elem->scale.y = 24.0f * playerScaleCoef;
			elem->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
			elem->SetParentRT(*col);
			elem->zOrder = ZOrder::object;
			idx++;
		}

		roll[dirB] = new ObImage(L"EnterTheGungeon/Player_0/Roll_Front.png");
		roll[dirL] = new ObImage(L"EnterTheGungeon/Player_0/Roll_Side.png");
		roll[dirR] = new ObImage(L"EnterTheGungeon/Player_0/Roll_Side.png");
		roll[dirLB] = new ObImage(L"EnterTheGungeon/Player_0/Roll_Side.png");
		roll[dirRB] = new ObImage(L"EnterTheGungeon/Player_0/Roll_Side.png");
		roll[dirT] = new ObImage(L"EnterTheGungeon/Player_0/Roll_Back.png");
		roll[dirLT] = new ObImage(L"EnterTheGungeon/Player_0/Roll_BackDiag.png");
		roll[dirRT] = new ObImage(L"EnterTheGungeon/Player_0/Roll_BackDiag.png");

		idx = 0;
		for (auto& elem : roll)
		{
			if (idx == dirL || idx == dirLB || idx == dirLT)
			{
				elem->reverseLR = true;
			}
			elem->isVisible = false;
			elem->maxFrame.x = 9;
			elem->scale.x = 180.0f / 9.0f * playerScaleCoef;
			elem->scale.y = 24.0f * playerScaleCoef;
			elem->uv = Vector4(0.0f, 0.0f, 1.0f / 9.0f, 1.0f);
			elem->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
			elem->SetParentRT(*col);
			elem->zOrder = ZOrder::object;
			idx++;
		}

		hit = nullptr;

		fall = new ObImage(L"EnterTheGungeon/Player_0/Fall.png");
		fall->isVisible = false;
		fall->maxFrame.x = 3;
		fall->scale.x = 48.0f / 3.0f * playerScaleCoef;
		fall->scale.y = 22.0f * playerScaleCoef;
		fall->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
		fall->SetParentRT(*col);
		fall->zOrder = ZOrder::object;

		die = new ObImage(L"EnterTheGungeon/Player_0/Die.png");
		die->isVisible = false;
		die->maxFrame.x = 8;
		die->scale.x = 160.0f / 8.0f * playerScaleCoef;
		die->scale.y = 24.0f * playerScaleCoef;
		die->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
		die->SetParentRT(*col);
		die->zOrder = ZOrder::object;

		respawn = new ObImage(L"EnterTheGungeon/Player_0/Respawn.png");
		respawn->isVisible = false;
		respawn->maxFrame.x = 3;
		respawn->scale.x = 48.0f / 3.0f * playerScaleCoef;
		respawn->scale.y = 22.0f * playerScaleCoef;
		respawn->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
		respawn->SetParentRT(*col);
		respawn->zOrder = ZOrder::object;

		kick = new ObImage(L"EnterTheGungeon/Player_0/Kick.png");
		kick->isVisible = false;
		kick->maxFrame.x = 3;
		kick->scale.x = 48.0f / 3.0f * playerScaleCoef;
		kick->scale.y = 22.0f * playerScaleCoef;
		kick->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
		kick->SetParentRT(*col);
		kick->zOrder = ZOrder::object;

		obtain = new ObImage(L"EnterTheGungeon/Player_0/Obtatin.png");
		obtain->isVisible = false;
		obtain->maxFrame.x = 3;
		obtain->scale.x = 48.0f / 3.0f * playerScaleCoef;
		obtain->scale.y = 22.0f * playerScaleCoef;
		obtain->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
		obtain->SetParentRT(*col);
		obtain->zOrder = ZOrder::object;
	}

	void Player::InitWeapon()
	{
		weapon.resize(3);
		curWeaponIdx = 0;

		int idx = 0;
		for (auto& elem : weapon)
		{
			float playerWeaponScaleCoef = 1.5f;
			elem = new Weapon;
			elem->col = new ObRect;
			elem->col->isVisible = false;
			elem->col->isFilled = false;
			elem->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
			elem->col->scale.x = 30.0f * playerWeaponScaleCoef;
			elem->col->scale.y = 22.0f * playerWeaponScaleCoef;
			elem->col->SetParentT(*col);

			elem->idle = new ObImage(L"EnterTheGungeon/Player_0/Weapon_0.png");
			if (idx != 0) elem->idle->isVisible = false;
			elem->idle->scale.x = 30.0f * playerWeaponScaleCoef;
			elem->idle->scale.y = 22.0f * playerWeaponScaleCoef;
			elem->idle->SetParentRT(*elem->col);
			elem->idle->zOrder = ZOrder::weapon;

			elem->firePos = new ObRect;
			elem->firePos->SetParentRT(*elem->idle);
			elem->firePos->scale = Vector2(10.0f, 10.0f);
			elem->firePos->zOrder = ZOrder::none;

			float playerWeaponEffectScaleCoef = 3.0f;
			elem->fireEffect = new Effect;
			elem->fireEffect->idle = new ObImage(L"EnterTheGungeon/Player_0/Effect_Fire_Weapon_0.png");
			elem->fireEffect->idle->isVisible = false;
			elem->fireEffect->idle->maxFrame.x = 3;
			elem->fireEffect->idle->scale = Vector2(45.0f / 3.0f, 11.0f) * playerWeaponEffectScaleCoef;
			elem->fireEffect->idle->SetParentRT(*elem->firePos);
			elem->fireEffect->idle->zOrder = ZOrder::none;
			elem->fireEffect->intervalDie = 0.2f;

			elem->imgReloading = new ObImage(L"EnterTheGungeon/Player_0/Weapon_0_reloading.png");
			elem->imgReloading->isVisible = false;
			elem->imgReloading->pivot = Vector2(0.4f, 0.25f);
			elem->imgReloading->maxFrame.x = 2;
			elem->imgReloading->scale.x = 42.0f / 2.0f * playerWeaponScaleCoef;
			elem->imgReloading->scale.y = 22.0f * playerWeaponScaleCoef;
			elem->imgReloading->SetParentRT(*elem->col);
			elem->imgReloading->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
			elem->imgReloading->zOrder = ZOrder::UI;

			elem->pivotDefault = Vector2(0.4f, 0.25f);
			elem->localPosDefault = Vector2(18.0f, -15.0f);
			elem->localFirePosDefault = Vector2(40.0f, 12.0f);
			weapon[curWeaponIdx]->Equip();


			elem->uiWeaponFrame = new UI;
			elem->uiWeaponFrame->img = new ObImage(L"EnterTheGungeon/Player_0/UI_GunFrame.png");
			elem->uiWeaponFrame->img->pivot = Vector2(0.4f, 0.25f);
			elem->uiWeaponFrame->img->scale.x = 188.0f;
			elem->uiWeaponFrame->img->scale.y = 116.0f;
			elem->uiWeaponFrame->anchor = Anchor::rightBottom;
			elem->uiWeaponFrame->Spawn(-240.0f, 50.0f);
			elem->uiWeaponFrame->img->space = Space::screen;
			elem->uiWeaponFrame->img->zOrder = ZOrder::UI;

			elem->uiBulletFrame = new UI;
			elem->uiBulletFrame->img = new ObImage(L"EnterTheGungeon/Player_0/UI_Magazine.png");
			elem->uiBulletFrame->img->scale = Vector2(28.0f, 99.0f);
			elem->uiBulletFrame->anchor = Anchor::rightBottom;
			elem->uiBulletFrame->Spawn(-40.0f, 80.0f);
			elem->uiBulletFrame->img->space = Space::screen;
			elem->uiBulletFrame->img->zOrder = ZOrder::UI;

			elem->bulletCount = 5;
			elem->uiBullet.resize(elem->bulletCount);

			int uiBulletIdx = 0;
			for (auto& elem : elem->uiBullet)
			{
				elem = new UI;
				elem->img = new ObImage(L"EnterTheGungeon/Player_0/UI_Bullet.png");
				elem->img->scale = Vector2(12.0f, 4.0f);
				elem->anchor = Anchor::rightBottom;
				elem->Spawn(-40.0f, 56.0f + uiBulletIdx * 12.0f);
				elem->img->space = Space::screen;
				elem->img->isVisible = false;
				uiBulletIdx++;
			}

			elem->uiWeapon = new UI;
			elem->uiWeapon->img = new ObImage(L"EnterTheGungeon/Player_0/UI_Weapon.png");
			elem->uiWeapon->img->pivot = Vector2(0.4f, 0.25f);
			elem->uiWeapon->img->scale.x = 60.0f;
			elem->uiWeapon->img->scale.y = 48.0f;
			elem->uiWeapon->anchor = Anchor::rightBottom;
			elem->uiWeapon->Spawn(-190.0f, 60.0f);
			elem->uiWeapon->img->space = Space::screen;
			elem->uiWeapon->img->zOrder = ZOrder::UI;

			elem->uiBulletCount = new UI;
			elem->uiBulletCount->img = new ObImage(L"EnterTheGungeon/Player_0/UI_BulletCount.png");
			elem->uiBulletCount->img->pivot = Vector2(0.4f, 0.25f);
			elem->uiBulletCount->img->scale.x = 60.0f;
			elem->uiBulletCount->img->scale.y = 28.0f;
			elem->uiBulletCount->anchor = Anchor::rightBottom;
			elem->uiBulletCount->Spawn(-140.0f, 150.0f);
			elem->uiBulletCount->img->space = Space::screen;
			elem->uiBulletCount->img->zOrder = ZOrder::UI;

			idx++;
		}

		for (auto& elem : weapon[curWeaponIdx]->uiBullet)
		{
			elem->img->isVisible = true;
		}
	}

	void Player::InitBullet()
	{
		float bulletCoef = 1.5f;
		bullet.resize(5);

		for (auto& elem : bullet)
		{
			elem = new PlayerBullet;
			elem->col->scale.x = 19.0f * bulletCoef;
			elem->col->scale.y = 19.0f * bulletCoef;
			elem->idle = new ObImage(L"EnterTheGungeon/Player_0/Bullet_0.png");
			elem->idle->scale = col->scale * 0.8f;
			elem->idle->SetParentRT(*elem->col);
		}
	}

	void Player::InitEffect()
	{
		float playerScaleCoef = 2.0f;
		shadow = new ObImage(L"EnterTheGungeon/Player_0/Shadow.png");
		shadow->scale.x = 16.0f * playerScaleCoef;
		shadow->scale.y = 5.0f * playerScaleCoef;
		shadow->SetParentRT(*col);
		shadow->SetWorldPosY(-28.0f);
		shadow->zOrder = ZOrder::shadow;

		float dustCoef = 2.0f;
		dust = new Effect;
		dust->idle = new ObImage(L"EnterTheGungeon/Player_0/Dust.png");
		dust->idle->maxFrame.x = 4;
		dust->idle->scale.x = 44.0f / 3.0f * dustCoef;
		dust->idle->scale.y = 10.0f * dustCoef;
		dust->idle->isVisible = false;
		dust->intervalDie = 0.3f;
	}

	void Player::InitUI()
	{
		int idx = 0;

		uiReload = new UI;
		uiReload->img = new ObImage(L"EnterTheGungeon/Player_0/UI_Reload.png");
		uiReload->img->isVisible = false;
		uiReload->img->scale = Vector2(144.0f, 20.0f);
		uiReload->img->SetParentT(*col);
		uiReload->img->SetLocalPosX(0.0f);
		uiReload->img->SetLocalPosY(60.0f);
		uiReload->img->zOrder = ZOrder::UI;

		uiReloadBar = new UI;
		uiReloadBar->img = new ObImage(L"EnterTheGungeon/Player_0/UI_ReloadBar.png");
		uiReloadBar->img->isVisible = false;
		uiReloadBar->img->scale = Vector2(4.0f, 20.0f);
		uiReloadBar->img->SetParentT(*col);
		uiReloadBar->img->SetLocalPosX(-60.0f);
		uiReloadBar->img->SetLocalPosY(60.0f);
		uiReloadBar->img->zOrder = ZOrder::UI;

		uiHeartNone.resize(maxHp / 2);
		uiHeartHalf.resize(maxHp / 2);
		uiHeartFull.resize(maxHp / 2);

		float heartCoef = 1.0f;
		idx = 0;
		for (auto& elem : uiHeartNone)
		{
			elem = new UI;
			elem->img = new ObImage(L"EnterTheGungeon/Player_0/HeartNone.png");
			elem->anchor = Anchor::leftTop;
			elem->Spawn(10.0f + idx * 60.0f, -40.0f);
			elem->img->pivot = OFFSET_L;
			elem->img->scale.x = 52.0f * heartCoef;
			elem->img->scale.y = 44.0f * heartCoef;
			elem->img->space = Space::screen;
			elem->img->zOrder = ZOrder::UI;
			idx++;
		}
		idx = 0;
		for (auto& elem : uiHeartHalf)
		{
			elem = new UI;
			elem->img = new ObImage(L"EnterTheGungeon/Player_0/HeartHalf.png");
			elem->anchor = Anchor::leftTop;
			elem->Spawn(10.0f + idx * 60.0f, -40.0f);
			elem->img->pivot = OFFSET_L;
			elem->img->scale.x = 52.0f * heartCoef;
			elem->img->scale.y = 44.0f * heartCoef;
			elem->img->space = Space::screen;
			elem->img->zOrder = ZOrder::UI;
			idx++;
		}
		idx = 0;
		for (auto& elem : uiHeartFull)
		{
			elem = new UI;
			elem->img = new ObImage(L"EnterTheGungeon/Player_0/HeartFull.png");
			elem->anchor = Anchor::leftTop;
			elem->Spawn(10.0f + idx * 60.0f, -40.0f);
			elem->img->pivot = OFFSET_L;
			elem->img->scale.x = 52.0f * heartCoef;
			elem->img->scale.y = 44.0f * heartCoef;
			elem->img->space = Space::screen;
			elem->img->zOrder = ZOrder::UI;
			idx++;
		}

		idx = 0;
		uiBlank.resize(2);
		for (auto& elem : uiBlank)
		{
			elem = new UI;
			elem->img = new ObImage(L"EnterTheGungeon/Player_0/UI_Blank.png");
			elem->anchor = Anchor::leftTop;
			elem->Spawn(10.0f + idx * 50.0f, -100.0f);
			elem->img->pivot = OFFSET_L;
			elem->img->scale.x = 40.0f;
			elem->img->scale.y = 40.0f;
			elem->img->space = Space::screen;
			elem->img->zOrder = ZOrder::UI;
			idx++;
		}

		uiKey = new UI;
		uiKey->img = new ObImage(L"EnterTheGungeon/Player_0/UI_Key.png");
		uiKey->anchor = Anchor::leftTop;
		uiKey->Spawn(10.0f, -160.0f);
		uiKey->img->pivot = OFFSET_L;
		uiKey->img->scale.x = 56.0f;
		uiKey->img->scale.y = 48.0f;
		uiKey->img->space = Space::screen;
		uiKey->img->zOrder = ZOrder::UI;

		uiGold = new UI;
		uiGold->img = new ObImage(L"EnterTheGungeon/Player_0/UI_Gold.png");
		uiGold->anchor = Anchor::leftTop;
		uiGold->Spawn(120.0f, -160.0f);
		uiGold->img->pivot = OFFSET_L;
		uiGold->img->scale.x = 40.0f;
		uiGold->img->scale.y = 40.0f;
		uiGold->img->space = Space::screen;
		uiGold->img->zOrder = ZOrder::UI;

		uiFireBottle = new UI;
		uiFireBottle->img = new ObImage(L"EnterTheGungeon/Player_0/UI_FireBottle.png");
		uiFireBottle->anchor = Anchor::leftBottom;
		uiFireBottle->Spawn(85.0f, 70.0f);
		uiFireBottle->img->pivot = OFFSET_L;
		uiFireBottle->img->scale.x = 36.0f;
		uiFireBottle->img->scale.y = 76.0f;
		uiFireBottle->img->space = Space::screen;
		uiFireBottle->img->zOrder = ZOrder::UI;

		uiFireBottleFrame = new UI;
		uiFireBottleFrame->img = new ObImage(L"EnterTheGungeon/Player_0/UI_FireBottleFrame.png");
		uiFireBottleFrame->anchor = Anchor::leftBottom;
		uiFireBottleFrame->Spawn(10.0f, 70.0f);
		uiFireBottleFrame->img->pivot = OFFSET_L;
		uiFireBottleFrame->img->scale.x = 180.0f;
		uiFireBottleFrame->img->scale.y = 112.0f;
		uiFireBottleFrame->img->space = Space::screen;
		uiFireBottleFrame->img->zOrder = ZOrder::UI;
	}

	void Player::Release()
	{
		Unit::Release();
		for (auto& elem : roll) SafeDelete(elem);
		for (auto& elem : bullet) elem->Release();
		uiReload->Release();
		uiReloadBar->Release();
		for (auto& elem : uiHeartNone) elem->Release();
		for (auto& elem : uiHeartHalf) elem->Release();
		for (auto& elem : uiHeartFull) elem->Release();
		for (auto& elem : uiBlank) elem->Release();
		uiKey->Release();
		uiGold->Release();
		uiFireBottle->Release();
		uiFireBottleFrame->Release();
	}

	void Player::Update()
	{
		Unit::Update();

		SetTargetAndCamera();

		switch (state)
		{
		case State::idle:
			Idle();
			break;
		case State::walk:
			Walk();
			break;
		case State::roll:
			Roll();
			break;
		case State::die:
			Die();
			break;
		}

		dust->Update();
		for (auto& elem : roll) elem->Update();
		respawn->Update();
		kick->Update();
		obtain->Update();
		for (auto& elem : bullet) elem->Update();
		uiReload->Update();
		uiReloadBar->Update();
		for (auto& elem : uiHeartNone) elem->Update();
		for (auto& elem : uiHeartHalf) elem->Update();
		for (auto& elem : uiHeartFull) elem->Update();
		for (auto& elem : uiBlank) elem->Update();
		uiKey->Update();
		uiGold->Update();
		uiFireBottle->Update();
		uiFireBottleFrame->Update();
	}

	void Player::LateUpdate()
	{
	}

	void Player::Render()
	{
		dust->Render();

		Unit::Render();

		for (auto& elem : roll) elem->Render(); // RENDER->push(elem);
		respawn->Render(); //RENDER->push(respawn);
		kick->Render(); //RENDER->push(kick);
		obtain->Render(); //RENDER->push(obtain);
		for (auto& elem : bullet) elem->Render();

		uiReload->Render();
		uiReloadBar->Render();
		for (auto& elem : uiHeartNone) elem->Render();
		for (auto& elem : uiHeartHalf) elem->Render();
		for (auto& elem : uiHeartFull) elem->Render();
		for (auto& elem : uiBlank) elem->Render();
		uiKey->Render();
		uiGold->Render();
		uiFireBottle->Render();
		uiFireBottleFrame->Render();

		DWRITE->RenderText(to_wstring(money),
			RECT{ 170, 140, (long)app.GetWidth(), (long)app.GetHeight() },
			40.0f,
			L"Alagard");

		DWRITE->RenderText(to_wstring(key),
			RECT{ 80, 140, (long)app.GetWidth(), (long)app.GetHeight() },
			40.0f,
			L"Alagard");
	}

	void Player::ResizeScreen()
	{
		int idx = 0;

		weapon[curWeaponIdx]->ResizeScreen();

		idx = 0;
		for (auto& elem : uiHeartNone)
		{
			elem->Spawn(10.0f + idx * 60.0f, -40.0f);
			idx++;
		}
		idx = 0;
		for (auto& elem : uiHeartHalf)
		{
			elem->Spawn(10.0f + idx * 60.0f, -40.0f);
			idx++;
		}
		idx = 0;
		for (auto& elem : uiHeartFull)
		{
			elem->Spawn(10.0f + idx * 60.0f, -40.0f);
			idx++;
		}
	}

	void Player::SetTargetAndCamera()
	{
		targetPos = INPUT->GetWorldMousePos();

		CAM->position.x = Utility::Saturate((targetPos.x + idle[curTargetDirState]->GetWorldPos().x) / 2,
			idle[curTargetDirState]->GetWorldPos().x - 250.0f,
			idle[curTargetDirState]->GetWorldPos().x + 250.0f);
		CAM->position.y = Utility::Saturate((targetPos.y + idle[curTargetDirState]->GetWorldPos().y) / 2,
			idle[curTargetDirState]->GetWorldPos().y - 250.0f,
			idle[curTargetDirState]->GetWorldPos().y + 250.0f);
	}

	void Player::Idle()
	{
		Unit::SetTarget();

		Move();
		SetMoveDirState();
		StartWalk();
		Action();

		if (flagFireCamShake)
		{
			ShakeCam(timeFireCamShake);
		}

		Reloading();
		Hitting();
		Dusting();
	}

	void Player::Walk()
	{
		Unit::SetTarget();

		Move();
		SetMoveDirState();
		StartIdle();
		Action();

		if (flagFireCamShake)
		{
			ShakeCam(timeFireCamShake);
		}

		Reloading();
		Hitting();
		Dusting();
	}

	void Player::Roll()
	{
		timeRoll += DELTA;

		col->MoveWorldPos(moveDir * (scalar * 2.0f) * cos(timeRoll / 0.63f * DIV2PI) * DELTA);

		if (timeRoll > 0.63f)
		{
			StartIdle();
			state = State::idle;

			weapon[curWeaponIdx]->idle->isVisible = true;
			scalar = 300.0f;

			godMode = false;
		}

		Reloading();
		Hitting();
		Dusting();
	}

	void Player::Die()
	{
		Unit::Die();
		dust->idle->isVisible = false;

		for (auto& elem : weapon)
		{
			elem->idle->isVisible = false;
		}
	}

	void Player::Move()
	{
		if (INPUT->KeyPress('A'))
		{
			moveDir.x = -1.0f;
		}
		else if (INPUT->KeyPress('D'))
		{
			moveDir.x = 1.0f;
		}
		else
		{
			moveDir.x = 0.0f;
		}

		if (INPUT->KeyPress('W'))
		{
			moveDir.y = 1.0f;
		}
		else if (INPUT->KeyPress('S'))
		{
			moveDir.y = -1.0f;
		}
		else
		{
			moveDir.y = 0.0f;
		}

		moveDir.Normalize();
		col->MoveWorldPos(moveDir * scalar * DELTA);
	}

	void Player::Action()
	{
		if (INPUT->KeyPress(VK_LBUTTON))
		{
			Fire();
		}
		else if (INPUT->KeyPress(VK_RBUTTON))
		{
			StartRoll();
		}
	}

	void Player::Fire()
	{
		if (false == isReloading)
		{
			flagFireCamShake = true;

			if (TIMER->GetTick(timeFire, 0.2f) || 
				curBulletIdx == weapon[curWeaponIdx]->bulletCount - 1)	// 처음
			{
				canFireBetween = true;
			}
		}

		if (curBulletIdx < 0)
		{
			curBulletIdx = weapon[curWeaponIdx]->bulletCount - 1;
			canFireBetween = false;
			isReloading = true;
			uiReload->img->isVisible = true;
			uiReloadBar->img->isVisible = true;
		}
		else if (canFireBetween)
		{
			weapon[curWeaponIdx]->fireEffect->Spawn(weapon[curWeaponIdx]->firePos->GetWorldPos());
			weapon[curWeaponIdx]->uiBullet[curBulletIdx]->img->isVisible = false;

			Vector2 dir = INPUT->GetWorldMousePos() - Pos();
			dir.Normalize();
			bullet[curBulletIdx]->Spawn(weapon[curWeaponIdx]->firePos->GetWorldPos(),
				Vector2(RANDOM->Float(dir.x - 0.1f, dir.x + 0.1f),
					RANDOM->Float(dir.y - 0.1f, dir.y + 0.1f))
			);

			curBulletIdx--;

			canFireBetween = false;

			SOUND->Stop("GUN");
			SOUND->Play("GUN");
		}

		originCamPos = CAM->position;
	}
	
	// 피격 시, 발사 시
	void Player::ShakeCam(float& time)
	{
		CAM->position = Vector2(RANDOM->Float(CAM->position.x - 2.0f, CAM->position.x + 2.0f),
			RANDOM->Float(CAM->position.y - 2.0f, CAM->position.y + 2.0f));

		if (TIMER->GetTick(time, 0.2f))
		{
			CAM->position = originCamPos;
			flagFireCamShake = false;
		}
	}

	void Player::StartWalk()
	{
		if (false == (moveDir.x == 0.0f && moveDir.y == 0.0f))
		{
			state = State::walk;

			for (auto& elem : idle) elem->isVisible = false;
			walk[curTargetDirState]->isVisible = true;
			for (auto& elem : roll) elem->isVisible = false;
		}
		else
		{
			idle[curTargetDirState]->isVisible = true;
			for (auto& elem : walk) elem->isVisible = false;
			for (auto& elem : roll) elem->isVisible = false;
		}
	}

	void Player::StartIdle()
	{
		if (moveDir.x == 0.0f && moveDir.y == 0.0f)
		{
			state = State::idle;

			idle[curTargetDirState]->isVisible = true;
			for (auto& elem : walk) elem->isVisible = false;
			for (auto& elem : roll) elem->isVisible = false;
		}
		else
		{
			for (auto& elem : idle) elem->isVisible = false;
			walk[curTargetDirState]->isVisible = true;
			for (auto& elem : roll) elem->isVisible = false;
		}
	}

	void Player::StartRoll()
	{
		if (false == (moveDir.x == 0.0f && moveDir.y == 0.0f))
		{
			state = State::roll;
			for (auto& elem : idle) elem->isVisible = false;
			for (auto& elem : walk) elem->isVisible = false;
			weapon[curWeaponIdx]->idle->isVisible = false;

			SetMoveDirState();

			roll[curMoveDirState]->isVisible = true;
			roll[curMoveDirState]->ChangeAnim(ANIMSTATE::ONCE, 0.07f);

			timeRoll = 0.0f;

			godMode = true;
		}
	}

	void Player::StartDie()
	{
		Unit::StartDie();

		DecreaseHeart();

		for (auto& elem : roll)
		{
			elem->isVisible = false;
		}

		for (auto& elem : bullet)
		{
			elem->col->colOnOff = false;
			elem->col->isVisible = false;
			elem->idle->colOnOff = false;
			elem->idle->isVisible = false;
		}
	}

	void Player::Reloading()
	{
		if (isReloading)
		{
			uiReloadBar->img->MoveLocalPos(Vector2(80.0f * DELTA, 0.0f));
			weapon[curWeaponIdx]->idle->isVisible = false;
			weapon[curWeaponIdx]->imgReloading->isVisible = true;

			if (TIMER->GetTick(timeReload, 1.5f))
			{
				weapon[curWeaponIdx]->idle->isVisible = true;
				weapon[curWeaponIdx]->imgReloading->isVisible = false;
				uiReload->img->isVisible = false;
				uiReloadBar->img->isVisible = false;
				isReloading = false;
				uiReloadBar->img->SetLocalPosX(-60.0f);
				for (auto& elem : weapon[curWeaponIdx]->uiBullet) elem->img->isVisible = true;
			}
		}
	}

	void Player::Hitting()
	{
		if (isHit)
		{
			DecreaseHeart();

			if (TIMER->GetTick(timeHit, 1.0f))
			{
				isHit = false;
			}
		}

		if (isHitAnim)
		{
			Color c = Color(RANDOM->Float(0.6f, 1.0f), 0.5f, 0.5f, RANDOM->Float(0.2f, 1.0f));
			for (auto& elem : idle) elem->color = c;
			for (auto& elem : walk) elem->color = c;
			for (auto& elem : roll) elem->color = c;

			CAM->position = Vector2(RANDOM->Float(CAM->position.x - 2.0f, CAM->position.x + 2.0f),
				RANDOM->Float(CAM->position.y - 2.0f, CAM->position.y + 2.0f));


			if (TIMER->GetTick(timeHitAnim, 1.0f))
			{
				Color c = Color(0.5f, 0.5f, 0.5f, 1.0f);
				for (auto& elem : idle) elem->color = c;
				for (auto& elem : walk) elem->color = c;
				for (auto& elem : roll) elem->color = c;

				CAM->position = originCamPos;
				flagFireCamShake = false;

				isHitAnim = false;
			}
		}
		else
		{
			idle[curTargetDirState]->color.w = 1.0f;
			walk[curTargetDirState]->color.w = 1.0f;
		}
	}

	void Player::Dusting()
	{
		if (TIMER->GetTick(timeLastPosForDust, 0.6f))
		{
			dust->Spawn(foot->GetWorldPos());
		}
	}

	void Player::DecreaseHeart()
	{
		if (curHp & 1)
		{
			uiHeartFull[curHp / 2]->img->isVisible = false;
		}
		else
		{
			uiHeartHalf[curHp / 2]->img->isVisible = false;
		}
	}

	void Player::PlusMoney(const int n)
	{
		money += n;
	}

	void Player::EquipWeapon(Weapon* other)
	{
		// 이전 무기 끄기
		Weapon*& beforeWeapon = weapon[curWeaponIdx];
		beforeWeapon->idle->isVisible = false;
		beforeWeapon->imgReloading->isVisible = false;
		for (auto& elem : beforeWeapon->uiBullet)
		{
			if (elem)
			{
				elem->img->isVisible = false;
			}
		}
		if (beforeWeapon->uiWeapon)
		{
			beforeWeapon->uiWeapon->img->isVisible = false;
		}
		if (beforeWeapon->uiBulletFrame)
		{
			beforeWeapon->uiBulletFrame->img->isVisible = false;
		}


		curWeaponIdx++;


		// 새 무기
		Weapon*& afterWeapon = weapon[curWeaponIdx];
		afterWeapon = other;
		afterWeapon->col->SetParentT(*col);
		afterWeapon->idle->isVisible = true;
		if (targetDir.x < 0.0f)
		{
			afterWeapon->EquipLeft();
		}
		else
		{
			afterWeapon->EquipRight();
		}

		// bullet
		curBulletIdx = afterWeapon->bulletCount - 1;
		bullet.resize(afterWeapon->bulletCount);
		float bulletCoef = 1.5f;
		for (auto& elem : bullet)
		{
			if (elem) continue;
			elem = new PlayerBullet;
			elem->col->scale.x = 19.0f * bulletCoef;
			elem->col->scale.y = 19.0f * bulletCoef;
			elem->idle = new ObImage(L"EnterTheGungeon/Player_0/Bullet_0.png");
			elem->idle->scale = col->scale * 0.8f;
			elem->idle->SetParentRT(*elem->col);
		}

		// UI Bullet
		afterWeapon->uiBullet.resize(afterWeapon->bulletCount);
		int uiBulletIdx = 0;
		for (auto& elem : afterWeapon->uiBullet)
		{
			elem = new UI;
			elem->img = new ObImage(L"EnterTheGungeon/Player_0/UI_Bullet.png");
			elem->img->scale = Vector2(12.0f, 4.0f);
			elem->anchor = Anchor::rightBottom;
			elem->Spawn(-40.0f, 56.0f + uiBulletIdx * 12.0f);
			elem->img->space = Space::screen;
			elem->img->isVisible = true;
			uiBulletIdx++;
		}
		
		if (afterWeapon->uiWeapon)
		{
			afterWeapon->uiWeapon->img->isVisible = true;
		}
		if (afterWeapon->uiBulletFrame)
		{
			afterWeapon->uiBulletFrame->img->isVisible = true;
		}
	}
}