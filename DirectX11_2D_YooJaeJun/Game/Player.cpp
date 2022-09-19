#include "stdafx.h"

Player::Player()
{
	scalar = 300.0f;
	curHp = maxHp = 6;

	float bulletCoef = 3.0f;

	for (auto& elem : bullet)
	{
		elem = new PlayerBullet;
		elem->col->scale.x = 8.0f * bulletCoef;
		elem->col->scale.y = 8.0f * bulletCoef;
		elem->idle = new ObImage(L"EnterTheGungeon/Player_0_Bullet_0.png");
		elem->idle->scale.x = 8.0f * bulletCoef;
		elem->idle->scale.y = 8.0f * bulletCoef;
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

	CAM->position.x = Utility::Saturate((dest.x + idle->GetWorldPos().x) / 2,
		idle->GetWorldPos().x - 200.0f,
		idle->GetWorldPos().x + 200.0f);
	CAM->position.y = Utility::Saturate((dest.y + idle->GetWorldPos().y) / 2,
		idle->GetWorldPos().y - 200.0f,
		idle->GetWorldPos().y + 200.0f);

	if (state == State::idle)
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
					elem->Spawn(Vector2(
						weapon->idle->GetWorldPivot().x + weapon->idle->scale.x / 2.0f,
						weapon->idle->GetWorldPivot().y),
						dir);
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
			idle->isVisible = false;
			roll->isVisible = true;
			roll->ChangeAnim(ANIMSTATE::ONCE, 0.05f);
		}
	}
	else if (state == State::roll)
	{
		Vector2 dir = dest - col->GetWorldPos();
		dir.Normalize();
		col->MoveWorldPos(dir * (scalar + 100.0f) * DELTA);
		if (TIMER->GetTick(timeRoll, 0.5f))
		{
			state = State::idle;
			idle->isVisible = true;
			roll->isVisible = false;
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