#include "stdafx.h"

Player::Player()
{
	Init();
}

void Player::Init()
{
	int idx = 0;

	scalar = 300.0f;
	curHp = maxHp = 6;
	canFire = true;
	reloading = false;
	timeReload = 0.0f;
	curBulletIdx = 0;
	timeFire = 0.0f;
	timeHit = 0.0f;
	isHit = false;
	isHitAnim = false;
	timeHitAnim = 0.0f;
	flagFireCamShake = false;
	timeFireCamShake = 0.0f;
	godMode = false;
	isWalking = false;


	float playerScaleCoef = 3.0f;
	col = new ObCircle;
	col->isFilled = false;
	col->scale.x = 12.0f * playerScaleCoef;
	col->scale.y = 12.0f * playerScaleCoef;
	col->zOrder = ZOrder::object;

	col->color = Color(1.0f, 1.0f, 1.0f);

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


	float playerWeaponScaleCoef = 1.5f;
	weapon = new Weapon;
	weapon->col = new ObRect;
	weapon->col->isVisible = false;
	weapon->col->isFilled = false;
	weapon->col->pivot = Vector2(0.4f, 0.25f);
	weapon->col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
	weapon->col->scale.x = 30.0f * playerWeaponScaleCoef;
	weapon->col->scale.y = 22.0f * playerWeaponScaleCoef;
	weapon->col->SetParentT(*col);
	weapon->col->SetLocalPosX(18.0f);
	weapon->col->SetLocalPosY(-15.0f);
	weapon->idle = new ObImage(L"EnterTheGungeon/Player_0/Weapon_0.png");
	weapon->idle->pivot = Vector2(0.4f, 0.25f);
	weapon->idle->scale.x = 30.0f * playerWeaponScaleCoef;
	weapon->idle->scale.y = 22.0f * playerWeaponScaleCoef;
	weapon->idle->SetParentRT(*weapon->col);
	weapon->idle->zOrder = ZOrder::weapon;

	weapon->firePos = new ObRect;
	weapon->firePos->SetParentRT(*weapon->idle);
	weapon->firePos->SetLocalPos(Vector2(30.0f, 12.0f));
	weapon->firePos->zOrder = ZOrder::none;
	weapon->firePos->scale = Vector2(20.0f, 20.0f);

	float playerWeaponEffectScaleCoef = 3.0;
	weapon->fireEffect = new Effect;
	weapon->fireEffect->idle = new ObImage(L"EnterTheGungeon/Player_0/Effect_Fire_Weapon_0.png");
	weapon->fireEffect->idle->isVisible = false;
	weapon->fireEffect->idle->scale.x = 15.0f * playerWeaponEffectScaleCoef;
	weapon->fireEffect->idle->scale.y = 11.0f * playerWeaponEffectScaleCoef;
	weapon->fireEffect->idle->SetParentRT(*weapon->firePos);
	weapon->fireEffect->idle->zOrder = ZOrder::none;

	shadow = new ObImage(L"EnterTheGungeon/Player_0/Shadow.png");
	shadow->scale.x = 16.0f * playerScaleCoef;
	shadow->scale.y = 5.0f * playerScaleCoef;
	shadow->SetParentRT(*col);
	shadow->SetWorldPosY(-28.0f);
	shadow->zOrder = ZOrder::shadow;

	foot = new ObRect;
	foot->scale = Vector2(col->scale.x, col->scale.y / 2.0f);
	foot->SetParentRT(*col);
	foot->SetLocalPosY(col->GetWorldPos().y - col->scale.y + 10.0f);

	float dustCoef = 2.0f;
	dust = new Effect;
	dust->idle = new ObImage(L"EnterTheGungeon/Player_0/Dust.png");
	dust->idle->maxFrame.x = 4;
	dust->idle->scale.x = 44.0f / 3.0f * dustCoef;
	dust->idle->scale.y = 10.0f * dustCoef;

	timeLastPosForDust = 0.0f;


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


	uiMagazine = new UI;
	uiMagazine->img = new ObImage(L"EnterTheGungeon/Player_0/UI_Magazine.png");
	uiMagazine->img->scale = Vector2(28.0f, 99.0f);
	uiMagazine->anchor = Anchor::RIGHTBOTTOM;
	uiMagazine->Spawn(-40.0f, 80.0f);
	uiMagazine->img->space = Space::screen;
	uiMagazine->img->zOrder = ZOrder::UI;

	idx = 0;
	for (auto& elem : uiBullet)
	{
		elem = new UI;
		elem->img = new ObImage(L"EnterTheGungeon/Player_0/UI_Bullet.png");
		elem->img->scale = Vector2(12.0f, 4.0f);
		elem->anchor = Anchor::RIGHTBOTTOM;
		elem->Spawn(-40.0f, 104.0f - idx * 12.0f);
		elem->img->space = Space::screen;
		idx++;
	}

	uiWeaponFrame = new UI;
	uiWeaponFrame->img = new ObImage(L"EnterTheGungeon/Player_0/UI_GunFrame.png");
	uiWeaponFrame->img->pivot = Vector2(0.4f, 0.25f);
	uiWeaponFrame->img->scale.x = 188.0f;
	uiWeaponFrame->img->scale.y = 116.0f;
	uiWeaponFrame->anchor = Anchor::RIGHTBOTTOM;
	uiWeaponFrame->Spawn(-240.0f, 50.0f);
	uiWeaponFrame->img->space = Space::screen;
	uiWeaponFrame->img->zOrder = ZOrder::UI;

	uiWeapon = new UI;
	uiWeapon->img = new ObImage(L"EnterTheGungeon/Player_0/UI_Weapon.png");
	uiWeapon->img->pivot = Vector2(0.4f, 0.25f);
	uiWeapon->img->scale.x = 60.0f;
	uiWeapon->img->scale.y = 48.0f;
	uiWeapon->anchor = Anchor::RIGHTBOTTOM;
	uiWeapon->Spawn(-190.0f, 60.0f);
	uiWeapon->img->space = Space::screen;
	uiWeapon->img->zOrder = ZOrder::UI;

	uiBulletCount = new UI;
	uiBulletCount->img = new ObImage(L"EnterTheGungeon/Player_0/UI_BulletCount.png");
	uiBulletCount->img->pivot = Vector2(0.4f, 0.25f);
	uiBulletCount->img->scale.x = 60.0f;
	uiBulletCount->img->scale.y = 28.0f;
	uiBulletCount->anchor = Anchor::RIGHTBOTTOM;
	uiBulletCount->Spawn(-140.0f, 150.0f);
	uiBulletCount->img->space = Space::screen;
	uiBulletCount->img->zOrder = ZOrder::UI;


	weaponReloading = new Weapon;
	weaponReloading->idle = new ObImage(L"EnterTheGungeon/Player_0/Weapon_0_reloading.png");
	weaponReloading->idle->isVisible = false;
	weaponReloading->idle->pivot = Vector2(0.4f, 0.25f);
	weaponReloading->idle->maxFrame.x = 2;
	weaponReloading->idle->scale.x = 42.0f / 2.0f * playerWeaponScaleCoef;
	weaponReloading->idle->scale.y = 22.0f * playerWeaponScaleCoef;
	weaponReloading->idle->SetParentRT(*weapon->col);
	weaponReloading->idle->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	weaponReloading->idle->zOrder = ZOrder::UI;


	float bulletCoef = 1.5f;
	for (auto& elem : bullet)
	{
		elem = new PlayerBullet;
		elem->col->scale.x = 19.0f * bulletCoef;
		elem->col->scale.y = 19.0f * bulletCoef;
		elem->idle = new ObImage(L"EnterTheGungeon/Player_0/Bullet_0.png");
		elem->idle->scale = col->scale * 0.8f;
		elem->idle->SetParentRT(*elem->col);
	}

	uiHeartNone.resize(maxHp / 2);
	uiHeartHalf.resize(maxHp / 2);
	uiHeartFull.resize(maxHp / 2);
	float heartCoef = 1.0f;
	idx = 0;
	for (auto& elem : uiHeartNone)
	{
		elem = new UI;
		elem->img = new ObImage(L"EnterTheGungeon/Player_0/HeartNone.png");
		elem->anchor = Anchor::LEFTTOP;
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
		elem->anchor = Anchor::LEFTTOP;
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
		elem->anchor = Anchor::LEFTTOP;
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
		elem->anchor = Anchor::LEFTTOP;
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
	uiKey->anchor = Anchor::LEFTTOP;
	uiKey->Spawn(10.0f, -160.0f);
	uiKey->img->pivot = OFFSET_L;
	uiKey->img->scale.x = 56.0f;
	uiKey->img->scale.y = 48.0f;
	uiKey->img->space = Space::screen;
	uiKey->img->zOrder = ZOrder::UI;

	uiGold = new UI;
	uiGold->img = new ObImage(L"EnterTheGungeon/Player_0/UI_Gold.png");
	uiGold->anchor = Anchor::LEFTTOP;
	uiGold->Spawn(120.0f, -160.0f);
	uiGold->img->pivot = OFFSET_L;
	uiGold->img->scale.x = 40.0f;
	uiGold->img->scale.y = 40.0f;
	uiGold->img->space = Space::screen;
	uiGold->img->zOrder = ZOrder::UI;

	uiFireBottle = new UI;
	uiFireBottle->img = new ObImage(L"EnterTheGungeon/Player_0/UI_FireBottle.png");
	uiFireBottle->anchor = Anchor::LEFTBOTTOM;
	uiFireBottle->Spawn(85.0f, 70.0f);
	uiFireBottle->img->pivot = OFFSET_L;
	uiFireBottle->img->scale.x = 36.0f;
	uiFireBottle->img->scale.y = 76.0f;
	uiFireBottle->img->space = Space::screen;
	uiFireBottle->img->zOrder = ZOrder::UI;

	uiFireBottleFrame = new UI;
	uiFireBottleFrame->img = new ObImage(L"EnterTheGungeon/Player_0/UI_FireBottleFrame.png");
	uiFireBottleFrame->anchor = Anchor::LEFTBOTTOM;
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
	uiMagazine->Release();
	for(auto& elem : uiBullet) elem->Release();
	uiWeaponFrame->Release();
	uiWeapon->Release();
	uiBulletCount->Release();
	SafeDelete(weaponReloading);
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

	targetPos = INPUT->GetWorldMousePos();

	CAM->position.x = Utility::Saturate((targetPos.x + idle[curTargetDirState]->GetWorldPos().x) / 2,
		idle[curTargetDirState]->GetWorldPos().x - 250.0f,
		idle[curTargetDirState]->GetWorldPos().x + 250.0f);
	CAM->position.y = Utility::Saturate((targetPos.y + idle[curTargetDirState]->GetWorldPos().y) / 2,
		idle[curTargetDirState]->GetWorldPos().y - 250.0f,
		idle[curTargetDirState]->GetWorldPos().y + 250.0f);

	switch (state)
	{
	case State::idle:
		Idle();
		break;
	case State::roll:
		Roll();
		break;
	case State::die:
		Die();
		break;
	default:
		break;
	}

	if (reloading)
	{
		uiReloadBar->img->MoveLocalPos(Vector2(80.0f * DELTA, 0.0f));
		weapon->idle->isVisible = false;
		weaponReloading->idle->isVisible = true;

		if (TIMER->GetTick(timeReload, 1.5f))
		{
			weapon->idle->isVisible = true;
			weaponReloading->idle->isVisible = false;
			uiReload->img->isVisible = false;
			uiReloadBar->img->isVisible = false;
			reloading = false;
			uiReloadBar->img->SetLocalPosX(-60.0f);
			for (auto& elem : uiBullet) elem->img->isVisible = true;
		}
	}

	if (isHit)
	{
		DecreaseHeart();

		if (TIMER->GetTick(timeHit, 1.5f))
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

		if (TIMER->GetTick(timeHitAnim, 1.5f))
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

	if (TIMER->GetTick(timeLastPosForDust, 0.4f))
	{
		dust->idle->SetWorldPos(foot->GetWorldPos());
		dust->idle->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
		dust->Update();
	}

	for (auto& elem : roll) elem->Update();
	respawn->Update();
	kick->Update();
	obtain->Update();
	for (auto& elem : bullet) elem->Update();
	uiReload->Update();
	uiReloadBar->Update();
	uiMagazine->Update();
	for (auto& elem : uiBullet) elem->Update();
	uiWeaponFrame->Update();
	uiWeapon->Update();
	uiBulletCount->Update();
	weaponReloading->Update();
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
	uiMagazine->Render();
	for (auto& elem : uiBullet) elem->Render();
	uiWeaponFrame->Render();
	uiWeapon->Render();
	uiBulletCount->Render();
	weaponReloading->Render();
	for (auto& elem : uiHeartNone) elem->Render();
	for (auto& elem : uiHeartHalf) elem->Render();
	for (auto& elem : uiHeartFull) elem->Render();
	for (auto& elem : uiBlank) elem->Render();
	uiKey->Render();
	uiGold->Render();
	uiFireBottle->Render();
	uiFireBottleFrame->Render();
}

void Player::ResizeScreen()
{
	int idx = 0;

	uiMagazine->Spawn(-40.0f, 80.0f);
	uiWeaponFrame->Spawn(-240.0f, 50.0f);
	uiWeapon->Spawn(-190.0f, 60.0f);
	uiBulletCount->Spawn(-140.0f, 150.0f);

	idx = 0;
	for (auto& elem : uiBullet)
	{
		elem->Spawn(-40.0f, 104.0f - idx * 12.0f);
		idx++;
	}

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

void Player::Idle()
{
	Unit::Idle();

	col->GetWorldPos();

	if (INPUT->KeyPress('A'))
	{
		moveDir.x = -1.0f;
		// col->rotationY = PI;
	}
	else if (INPUT->KeyPress('D'))
	{
		moveDir.x = 1.0f;
		// col->rotationY = 0.0f;
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

	SetMoveDir();

	if (moveDir.x == 0.0f && moveDir.y == 0.0f)
	{
		idle[curTargetDirState]->isVisible = true;
		for (auto& elem : walk) elem->isVisible = false;
		isWalking = false;
	}
	else
	{
		for (auto& elem : idle) elem->isVisible = false;
		walk[curTargetDirState]->isVisible = true;
		isWalking = true;
	}

	if (INPUT->KeyPress(VK_LBUTTON))
	{
		if (curBulletIdx >= weapon0BulletMax)
		{
			curBulletIdx = 0;
			canFire = false;
			reloading = true;
			uiReload->img->isVisible = true;
			uiReloadBar->img->isVisible = true;
		}
		else if (canFire)
		{
			uiBullet[curBulletIdx]->img->isVisible = false;

			Vector2 dir = INPUT->GetWorldMousePos() - Pos();
			dir.Normalize();
			bullet[curBulletIdx++]->Spawn(weapon->firePos->GetWorldPos(),
				Vector2(RANDOM->Float(dir.x - 0.1f, dir.x + 0.1f),
					RANDOM->Float(dir.y - 0.1f, dir.y + 0.1f))
			);
			weapon->fireEffect->idle->isVisible = true;

			canFire = false;
		}

		if (false == reloading)
		{
			flagFireCamShake = true;

			if (TIMER->GetTick(timeFire, 0.2f))
			{
				canFire = true;
			}
		}
		originCamPos = CAM->position;
	}
	else if (INPUT->KeyPress(VK_RBUTTON))
	{
		if (false == (moveDir.x == 0.0f && moveDir.y == 0.0f))
		{
			state = State::roll;
			for (auto& elem : idle) elem->isVisible = false;
			for (auto& elem : walk) elem->isVisible = false;

			SetMoveDir();

			roll[curMoveDirState]->isVisible = true;
			roll[curMoveDirState]->ChangeAnim(ANIMSTATE::ONCE, 0.05f);

			godMode = true;
		}
	}

	if (flagFireCamShake)
	{
		CAM->position = Vector2(RANDOM->Float(CAM->position.x - 2.0f, CAM->position.x + 2.0f),
			RANDOM->Float(CAM->position.y - 2.0f, CAM->position.y + 2.0f));

		if (TIMER->GetTick(timeFireCamShake, 0.2f))
		{
			CAM->position = originCamPos;
			flagFireCamShake = false;
		}
	}
}

void Player::Roll()
{
	col->MoveWorldPos(moveDir * (scalar + 120.0f) * DELTA);

	if (TIMER->GetTick(timeRoll, 0.5f))
	{
		state = State::idle;
		idle[curTargetDirState]->isVisible = true;
		for (auto& elem : walk) elem->isVisible = false;
		for (auto& elem : roll) elem->isVisible = false;

		godMode = false;
	}
}

void Player::Killed()
{
	Unit::Killed();

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

void Player::Die()
{
	Unit::Die();
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
