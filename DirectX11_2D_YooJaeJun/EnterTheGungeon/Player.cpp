#include "stdafx.h"

Player::Player()
{
	scalar = 300.0f;
	curHp = maxHp = 10000;

	float bulletCoef = 1.5f;

	for (auto& elem : bullet)
	{
		elem = new PlayerBullet;
		elem->col->scale.x = 19.0f * bulletCoef;
		elem->col->scale.y = 19.0f * bulletCoef;
		elem->idle = new ObImage(L"EnterTheGungeon/Player_0/Bullet_0.png");
		elem->idle->scale.x = 19.0f * bulletCoef;
		elem->idle->scale.y = 19.0f * bulletCoef;
		elem->idle->SetParentRT(*elem->col);
	}


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
}

void Player::Release()
{
	Unit::Release();
	for (auto& elem : bullet) elem->Release();
	uiReload->Release();
	uiReloadBar->Release();
	uiMagazine->Release();
	uiBullet[weapon0BulletMax]->Release();
	uiWeaponFrame->Release();
	uiWeapon->Release();
	uiBulletCount->Release();
	SafeDelete(weaponReloading);
}

void Player::Update()
{
	Unit::Update();

	target = INPUT->GetWorldMousePos();

	CAM->position.x = Utility::Saturate((target.x + idle[curTarget8Dir]->GetWorldPos().x) / 2,
		idle[curTarget8Dir]->GetWorldPos().x - 250.0f,
		idle[curTarget8Dir]->GetWorldPos().x + 250.0f);
	CAM->position.y = Utility::Saturate((target.y + idle[curTarget8Dir]->GetWorldPos().y) / 2,
		idle[curTarget8Dir]->GetWorldPos().y - 250.0f,
		idle[curTarget8Dir]->GetWorldPos().y + 250.0f);

	if (state == State::idle)
	{
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

		if (moveDir.x == 0.0f && moveDir.y == 0.0f)
		{
			idle[curTarget8Dir]->isVisible = true;
			for (auto& elem : walk) elem->isVisible = false;
		}
		else
		{
			for (auto& elem : idle) elem->isVisible = false;
			walk[curTarget8Dir]->isVisible = true;
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

				Vector2 dir = INPUT->GetWorldMousePos() - col->GetWorldPos();
				dir.Normalize();
				bullet[curBulletIdx++]->Spawn(firePos->GetWorldPos(),
					Vector2(RANDOM->Float(dir.x - 0.1f, dir.x + 0.1f),
						RANDOM->Float(dir.y - 0.1f, dir.y + 0.1f))
				);
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

				roll[curMove8Dir]->isVisible = true;
				roll[curMove8Dir]->ChangeAnim(ANIMSTATE::ONCE, 0.05f);
				
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
	else if (state == State::roll)
	{
		col->MoveWorldPos(moveDir * (scalar + 100.0f) * DELTA);

		if (TIMER->GetTick(timeRoll, 0.5f))
		{
			state = State::idle;
			idle[curTarget8Dir]->isVisible = true;
			for (auto& elem : walk) elem->isVisible = false;
			for (auto& elem : roll) elem->isVisible = false;

			godMode = false;
		}
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
		idle[curTarget8Dir]->color.w = 1.0f;
		walk[curTarget8Dir]->color.w = 1.0f;
	}

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
}

void Player::LateUpdate()
{
}

void Player::Render()
{
	respawn->Render();
	kick->Render();
	obtain->Render();
	for (auto& elem : bullet) elem->Render();
	Unit::Render();

	uiReload->Render();
	uiReloadBar->Render();
	uiMagazine->Render();
	for (auto& elem : uiBullet) elem->Render();
	uiWeaponFrame->Render();
	uiWeapon->Render();
	uiBulletCount->Render();
	weaponReloading->Render();
}