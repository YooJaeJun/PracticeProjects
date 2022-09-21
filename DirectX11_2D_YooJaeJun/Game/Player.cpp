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
	timeFire = 0.0f;
	timeHit = 0.0f;
	isHit = false;
	isHitAnim = false;
	timeHitAnim = 0.0f;
}

void Player::Release()
{
	Unit::Release();
	for (auto& elem : bullet) elem->Release();
}

void Player::Update()
{
	Unit::Update();

	dest = INPUT->GetWorldMousePos();

	CAM->position.x = Utility::Saturate((dest.x + idle[curDir]->GetWorldPos().x) / 2,
		idle[curDir]->GetWorldPos().x - 250.0f,
		idle[curDir]->GetWorldPos().x + 250.0f);
	CAM->position.y = Utility::Saturate((dest.y + idle[curDir]->GetWorldPos().y) / 2,
		idle[curDir]->GetWorldPos().y - 250.0f,
		idle[curDir]->GetWorldPos().y + 250.0f);

	if (state == State::idle)
	{
		if (INPUT->KeyPress('A'))
		{
			moveDir.x = -1.0f;
			col->rotationY = PI;
		}
		else if (INPUT->KeyPress('D'))
		{
			moveDir.x = 1.0f;
			col->rotationY = 0.0f;
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

		if (moveDir.x == 0 && moveDir.y == 0)
		{
			idle[curDir]->isVisible = true;
			for(auto& elem : walk) elem->isVisible = false;
		}
		else
		{
			for (auto& elem : idle) elem->isVisible = false;
			walk[curDir]->isVisible = true;
		}

		moveDir.Normalize();
		col->MoveWorldPos(moveDir * scalar * DELTA);

		if (INPUT->KeyPress(VK_LBUTTON))
		{
			if (canFire)
			{
				for (auto& elem : bullet)
				{
					if (elem->isFired) continue;

					Vector2 dir = INPUT->GetWorldMousePos() - col->GetWorldPos();
					dir.Normalize();
					elem->Spawn(firePos->GetWorldPos(), dir);
					break;
				}
				canFire = false;
			}

			if (TIMER->GetTick(timeFire, 0.1f))
			{
				canFire = true;
			}
		}
		else if (INPUT->KeyPress(VK_RBUTTON))
		{
			state = State::roll;
			for (auto& elem : idle) elem->isVisible = false;
			for (auto& elem : walk) elem->isVisible = false;
			roll[curDir]->isVisible = true;
			roll[curDir]->ChangeAnim(ANIMSTATE::ONCE, 0.05f);
			godMode = true;
		}
	}
	else if (state == State::roll)
	{
		col->MoveWorldPos(moveDir * (scalar + 100.0f) * DELTA);
		if (TIMER->GetTick(timeRoll, 0.5f))
		{
			state = State::idle;
			idle[curDir]->isVisible = true;
			for (auto& elem : walk) elem->isVisible = false;
			for (auto& elem : roll) elem->isVisible = false;
			godMode = false;
		}
	}

	if (isHit)
	{
		if (TIMER->GetTick(timeHit, 1.5f))
		{
			isHit = false;
		}
	}

	respawn->Update();
	for (auto& elem : bullet) if (elem) elem->Update();
}

void Player::LateUpdate()
{
	Unit::LateUpdate();

	for (auto& elem : bullet) if (elem) elem->LateUpdate();
}

void Player::Render()
{
	respawn->Render();
	for (auto& elem : bullet) if (elem) elem->Render();
	Unit::Render();
}