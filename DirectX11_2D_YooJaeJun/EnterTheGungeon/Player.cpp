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
		for (auto& elem : canFireOnce) elem = true;
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
		timeHitCamShake = 0.0f;
		godMode = false;
		timeLastPosForDust = 0.0f;
		money = 0;
		key = 0;
	}

	void Player::InitCol()
	{
		float scaleFactor = 3.0f;
		col = new ObCircle;
		col->isFilled = false;
		col->scale.x = 12.0f * scaleFactor;
		col->scale.y = 12.0f * scaleFactor;
		col->zOrder = ZOrder::object;
		col->color = Color(1.0f, 1.0f, 1.0f);

		colTile = new ObRect;
		colTile->scale = Vector2(col->scale.x, col->scale.y / 2.0f);
		colTile->SetParentRT(*col);
		colTile->SetLocalPosY(col->GetWorldPos().y - col->scale.y / 2.0f);
		colTile->isFilled = false;
		colTile->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	}

	void Player::InitAnim()
	{
		int idx = 0;
		float scaleFactor = 3.0f;

		spawn = new ObImage(L"EnterTheGungeon/Player_0/Spawn.png");
		spawn->isVisible = false;
		spawn->maxFrame.x = 3;
		spawn->scale.x = 48.0f / 3.0f * scaleFactor;
		spawn->scale.y = 22.0f * scaleFactor;
		spawn->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
		spawn->SetParentRT(*col);
		spawn->zOrder = ZOrder::object;

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
			elem->scale.x = 72.0 / 4.0f * scaleFactor;
			elem->scale.y = 20.0f * scaleFactor;
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
			elem->scale.x = 102.0f / 6.0f * scaleFactor;
			elem->scale.y = 24.0f * scaleFactor;
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
			elem->scale.x = 180.0f / 9.0f * scaleFactor;
			elem->scale.y = 24.0f * scaleFactor;
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
		fall->scale.x = 48.0f / 3.0f * scaleFactor;
		fall->scale.y = 22.0f * scaleFactor;
		fall->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
		fall->SetParentRT(*col);
		fall->zOrder = ZOrder::object;

		die = new ObImage(L"EnterTheGungeon/Player_0/Die.png");
		die->isVisible = false;
		die->maxFrame.x = 8;
		die->scale.x = 160.0f / 8.0f * scaleFactor;
		die->scale.y = 24.0f * scaleFactor;
		die->ChangeAnim(ANIMSTATE::ONCE, 0.2f);
		die->SetParentRT(*col);
		die->zOrder = ZOrder::object;

		kick = new ObImage(L"EnterTheGungeon/Player_0/Kick.png");
		kick->isVisible = false;
		kick->maxFrame.x = 3;
		kick->scale.x = 48.0f / 3.0f * scaleFactor;
		kick->scale.y = 22.0f * scaleFactor;
		kick->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
		kick->SetParentRT(*col);
		kick->zOrder = ZOrder::object;

		obtain = new ObImage(L"EnterTheGungeon/Player_0/Obtain.png");
		obtain->isVisible = false;
		obtain->maxFrame.x = 3;
		obtain->scale.x = 48.0f / 3.0f * scaleFactor;
		obtain->scale.y = 22.0f * scaleFactor;
		obtain->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
		obtain->SetParentRT(*col);
		obtain->zOrder = ZOrder::object;
	}

	void Player::InitWeapon()
	{
		curWeaponIdx = 0;
		weapons[curWeaponIdx] = new Weapon1;
		weapons[curWeaponIdx]->col->SetParentRT(*col);
		weapons[curWeaponIdx]->col->SetLocalPos(Vector2(10.0f, -15.0f));
		weapons[curWeaponIdx]->idle->SetParentRT(*weapons[curWeaponIdx]->col);
		weapons[curWeaponIdx]->idle->isVisible = true;
		weapons[curWeaponIdx]->firePos->SetLocalPos(Vector2(weapons[curWeaponIdx]->col->scale.x / 2.0f, 0.0f));
		weapons[curWeaponIdx]->fireEffect->idle->SetParentRT(*weapons[curWeaponIdx]->firePos);
		weapons[curWeaponIdx]->imgReloading->SetParentRT(*weapons[curWeaponIdx]->col);
		weapons[curWeaponIdx]->Equip();

		for (auto& elem : weapons[curWeaponIdx]->uiBullet)
		{
			elem->img->isVisible = true;
		}

		weapons[curWeaponIdx]->uiBulletFrame->img->isVisible = true;
		weapons[curWeaponIdx]->uiWeapon->img->isVisible = true;
		weapons[curWeaponIdx]->uiBulletCount->img->isVisible = true;
	}

	void Player::InitBullet()
	{
		bullet.resize(5);
		for (auto& elem : bullet)
		{
			elem = new PlayerBullet;
		}
	}

	void Player::InitEffect()
	{
		float scaleFactor = 2.0f;
		shadow = new ObImage(L"EnterTheGungeon/Player_0/Shadow.png");
		shadow->scale.x = 16.0f * scaleFactor;
		shadow->scale.y = 5.0f * scaleFactor;
		shadow->SetParentRT(*col);
		shadow->SetWorldPosY(-30.0f);
		shadow->zOrder = ZOrder::shadow;

		float dustScaleFactor = 2.0f;
		dust = new Effect;
		dust->idle = new ObImage(L"EnterTheGungeon/Player_0/Dust.png");
		dust->idle->maxFrame.x = 4;
		dust->idle->scale.x = 44.0f / 3.0f * dustScaleFactor;
		dust->idle->scale.y = 10.0f * dustScaleFactor;
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

		uiWeaponFrame = new UI;
		uiWeaponFrame->img = new ObImage(L"EnterTheGungeon/Weapon/UI_WeaponFrame.png");
		uiWeaponFrame->img->scale.x = 188.0f;
		uiWeaponFrame->img->scale.y = 116.0f;
		uiWeaponFrame->img->pivot = OFFSET_RB;
		uiWeaponFrame->anchor = Anchor::rightBottom;
		uiWeaponFrame->Spawn(-70.0f, 30.0f);
		uiWeaponFrame->img->space = Space::screen;
		uiWeaponFrame->img->zOrder = ZOrder::UI;
		uiWeaponFrame->img->isVisible = true;

		for (auto& elem : weapons[curWeaponIdx]->uiBullet)
		{
			elem->img->isVisible = true;
		}


		uiHeartNone.resize(maxHp / 2);
		uiHeartHalf.resize(maxHp / 2);
		uiHeartFull.resize(maxHp / 2);

		float heartScaleFactor = 1.0f;
		idx = 0;
		for (auto& elem : uiHeartNone)
		{
			elem = new UI;
			elem->img = new ObImage(L"EnterTheGungeon/Player_0/HeartNone.png");
			elem->anchor = Anchor::leftTop;
			elem->Spawn(10.0f + idx * 60.0f, -40.0f);
			elem->img->pivot = OFFSET_L;
			elem->img->scale.x = 52.0f * heartScaleFactor;
			elem->img->scale.y = 44.0f * heartScaleFactor;
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
			elem->img->scale.x = 52.0f * heartScaleFactor;
			elem->img->scale.y = 44.0f * heartScaleFactor;
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
			elem->img->scale.x = 52.0f * heartScaleFactor;
			elem->img->scale.y = 44.0f * heartScaleFactor;
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
		weapons[curWeaponIdx]->Release();
		uiReload->Release();
		uiReloadBar->Release();
		SafeRelease(uiWeaponFrame);
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

		LIGHT->SetLightPos(col->GetWorldPivot());

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
		spawn->Update();
		kick->Update();
		obtain->Update();

		weapons[curWeaponIdx]->Update();
		for (auto& elem : bullet) elem->Update();
		uiReload->Update();
		uiReloadBar->Update();
		if (uiWeaponFrame) uiWeaponFrame->Update();
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
		spawn->Render(); //RENDER->push(respawn);
		kick->Render(); //RENDER->push(kick);
		obtain->Render(); //RENDER->push(obtain);
		for (auto& elem : bullet) elem->Render();

		weapons[curWeaponIdx]->Render();
		uiReload->Render();
		uiReloadBar->Render();
		if (uiWeaponFrame) uiWeaponFrame->Render();
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

		weapons[curWeaponIdx]->ResizeScreen();

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
		Unit::SetTarget(weapons[curWeaponIdx]);
		Unit::Idle();
		Move();

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
		Unit::SetTarget(weapons[curWeaponIdx]);
		Unit::Walk();
		Move();

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

			weapons[curWeaponIdx]->idle->isVisible = true;
			weapons[curWeaponIdx]->firePos->isVisible = true;

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

		weapons[curWeaponIdx]->idle->isVisible = false;
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

		if (moveDir.x != 0.0f || moveDir.y != 0.0f)
		{
			moveDir.Normalize();
			col->MoveWorldPos(moveDir * scalar * DELTA);
		}
	}

	void Player::Action()
	{
		float fireInterval;
		switch (weapons[curWeaponIdx]->type)
		{
		case WeaponType::pistol:
			fireInterval = 0.2f;
			break;
		case WeaponType::shotgun:
			fireInterval = 0.7f;
			break;
		default:
			fireInterval = 0.1f;
			break;
		}

		int firstFire = weapons[curWeaponIdx]->bulletCount - 1;

		if (curBulletIdx == firstFire ||
			TIMER->GetTick(timeFire, fireInterval))
		{
			if (curBulletIdx < 0)
			{
				isReloading = true;

				curBulletIdx = weapons[curWeaponIdx]->bulletCount - 1;

				for (auto& elem : canFireOnce) elem = false;

				uiReload->img->isVisible = true;
				uiReloadBar->img->isVisible = true;
			}

			if (INPUT->KeyPress(VK_LBUTTON) || INPUT->KeyDown(VK_LBUTTON))
			{
				Fire();
			}
		}

		if (INPUT->KeyDown(VK_RBUTTON))
		{
			StartRoll();
		}
	}

	void Player::Fire()
	{
		if (false == isReloading)
		{
			canFireOnce[(int)weapons[curWeaponIdx]->type] = true;
			flagFireCamShake = true;
		}

		Vector2 dir = INPUT->GetWorldMousePos() - Pos();
		dir.Normalize();

		switch (weapons[curWeaponIdx]->type)
		{
		case WeaponType::pistol:

			if (canFireOnce[(int)WeaponType::pistol])
			{
				weapons[curWeaponIdx]->fireEffect->Spawn(weapons[curWeaponIdx]->firePos->GetWorldPos());
				weapons[curWeaponIdx]->uiBullet[curBulletIdx]->img->isVisible = false;

				bullet[curBulletIdx]->Spawn(
					weapons[curWeaponIdx]->firePos->GetWorldPos(),
					Vector2(RANDOM->Float(dir.x - 0.1f, dir.x + 0.1f),
						RANDOM->Float(dir.y - 0.1f, dir.y + 0.1f))
				);

				SOUND->Stop("GUN");
				SOUND->Play("GUN");

				canFireOnce[(int)WeaponType::pistol] = false;

				curBulletIdx--;
			}

			break;

		case WeaponType::shotgun:

			if (canFireOnce[(int)WeaponType::shotgun])
			{
				weapons[curWeaponIdx]->fireEffect->Spawn(weapons[curWeaponIdx]->firePos->GetWorldPos());
				weapons[curWeaponIdx]->uiBullet[curBulletIdx]->img->isVisible = false;

				for (int bulletOnce = 6; bulletOnce >= 0; bulletOnce--)
				{
					bullet[bulletOnce]->scalar = RANDOM->Float(800.0f, 1000.0f);

					bullet[bulletOnce]->Spawn(
						weapons[curWeaponIdx]->firePos->GetWorldPos(),
						Vector2(RANDOM->Float(dir.x - 0.2f, dir.x + 0.2f),
							RANDOM->Float(dir.y - 0.2f, dir.y + 0.2f))
					);
				}

				SOUND->Stop("GUN");
				SOUND->Play("GUN");

				canFireOnce[(int)WeaponType::shotgun] = false;

				curBulletIdx--;
			}

			break;
		}

		// originCamPos = CAM->position;
	}
	
	// 발사 시, 피격 시
	void Player::ShakeCam(float& time)
	{
		CAM->position = Vector2(RANDOM->Float(CAM->position.x - 2.0f, CAM->position.x + 2.0f),
			RANDOM->Float(CAM->position.y - 2.0f, CAM->position.y + 2.0f));

		if (TIMER->GetTick(time, 0.2f))
		{
			// CAM->position = originCamPos;
			flagFireCamShake = false;
		}
	}

	void Player::StartWalk()
	{
		Unit::StartWalk();
		for (auto& elem : roll) elem->isVisible = false;
	}

	void Player::StartIdle()
	{
		Unit::StartIdle();
		for (auto& elem : roll) elem->isVisible = false;
	}

	void Player::StartRoll()
	{
		if (false == (moveDir.x == 0.0f && moveDir.y == 0.0f))
		{
			state = State::roll;

			for (auto& elem : idle) elem->isVisible = false;
			for (auto& elem : walk) elem->isVisible = false;
			weapons[curWeaponIdx]->idle->isVisible = false;
			weapons[curWeaponIdx]->imgReloading->isVisible = false;
			weapons[curWeaponIdx]->firePos->isVisible = false;

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

		weapons[curWeaponIdx]->col->isVisible = false;
		weapons[curWeaponIdx]->idle->isVisible = false;
		weapons[curWeaponIdx]->firePos->isVisible = false;

		DecreaseHeart();

		for (auto& elem : roll)
		{
			elem->isVisible = false;
		}

		for (auto& elem : bullet)
		{
			elem->col->isVisible = false;
			elem->idle->isVisible = false;
		}
	}

	void Player::Reloading()
	{
		if (isReloading)
		{
			uiReloadBar->img->MoveLocalPos(Vector2(80.0f * DELTA, 0.0f));
			weapons[curWeaponIdx]->idle->isVisible = false;
			weapons[curWeaponIdx]->imgReloading->isVisible = true;

			if (TIMER->GetTick(timeReload, 1.5f))
			{
				weapons[curWeaponIdx]->idle->isVisible = true;
				weapons[curWeaponIdx]->imgReloading->isVisible = false;
				uiReload->img->isVisible = false;
				uiReloadBar->img->isVisible = false;
				isReloading = false;
				uiReloadBar->img->SetLocalPosX(-60.0f);
				for (auto& elem : weapons[curWeaponIdx]->uiBullet) elem->img->isVisible = true;
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

			ShakeCam(timeHitCamShake);

			if (TIMER->GetTick(timeHitAnim, 1.0f))
			{
				Color c = Color(0.5f, 0.5f, 0.5f, 1.0f);
				for (auto& elem : idle) elem->color = c;
				for (auto& elem : walk) elem->color = c;
				for (auto& elem : roll) elem->color = c;

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
			dust->Spawn(colTile->GetWorldPos());
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
		Weapon*& beforeWeapon = weapons[curWeaponIdx];
		beforeWeapon->idle->isVisible = false;
		beforeWeapon->firePos->isVisible = false;
		beforeWeapon->imgReloading->isVisible = false;
		for (auto& elem : beforeWeapon->uiBullet)
		{
			elem->img->isVisible = false;
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
		Weapon*& afterWeapon = weapons[curWeaponIdx];
		afterWeapon = other;
		afterWeapon->col->SetParentT(*col);
		afterWeapon->idle->isVisible = true;
		beforeWeapon->firePos->isVisible = true;

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
		bullet.clear();
		bullet.resize(afterWeapon->bulletCount);
		for (auto& elem : bullet)
		{
			elem = new PlayerBullet;
		}

		// UI Bullet
		for (auto& elem : afterWeapon->uiBullet)
		{
			elem->img->isVisible = true;
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