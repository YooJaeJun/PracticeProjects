#include "stdafx.h"

Player::Player()
{
	col = new ObCircle();
	col->scale.x = 15.0f * 2.0f;
	col->scale.y = 15.0f * 2.0f;
	col->color = Color(1.0f, 1.0f, 1.0f);
	col->isFilled = false;
	Spawn();

	idle = new ObImage(L"EnterTheGungeon/Player_0_Idle.png");
	idle->maxFrame.x = 3;
	idle->scale.x = 48.0f / 3.0f * 2.0f;
	idle->scale.y = 22.0f * 2.0f;
	idle->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
	idle->SetParentRT(*col);

	walk = new ObImage(L"EnterTheGungeon/Player_0_Idle.png");
	walk->maxFrame.x = 3;
	walk->scale.x = 48.0f / 3 * 2.0f;
	walk->scale.y = 22.0f * 2.0f;
	walk->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
	walk->SetParentRT(*col);

	roll = new ObImage(L"EnterTheGungeon/Player_0_Idle.png");
	roll->maxFrame.x = 3;
	roll->scale.x = 48.0f / 3 * 2.0f;
	roll->scale.y = 22.0f * 2.0f;
	roll->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
	roll->SetParentRT(*col);

	hit = new ObImage(L"EnterTheGungeon/Player_0_Idle.png");
	hit->maxFrame.x = 3;
	hit->scale.x = 48.0f / 3 * 2.0f;
	hit->scale.y = 22.0f * 2.0f;
	hit->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
	hit->SetParentRT(*col);

	die = new ObImage(L"EnterTheGungeon/Player_0_Idle.png");
	die->maxFrame.x = 3;
	die->scale.x = 48.0f / 3 * 2.0f;
	die->scale.y = 22.0f * 2.0f;
	die->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
	die->SetParentRT(*col);

	respawn = new ObImage(L"EnterTheGungeon/Player_0_Idle.png");
	respawn->maxFrame.x = 3;
	respawn->scale.x = 48.0f / 3 * 2.0f;
	respawn->scale.y = 22.0f * 2.0f;
	respawn->ChangeAnim(ANIMSTATE::LOOP, 0.2f);
	respawn->SetParentRT(*col);

	weapon = new Weapon;
	weapon->col->pivot = OFFSET_LB;
	weapon->col->scale.x = 29.0f;
	weapon->col->scale.y = 21.0f;
	weapon->col->SetParentRT(*col);
	weapon->col->SetLocalPosX(10.0f);
	weapon->col->SetLocalPosY(-15.0f);

	weapon->idle = new ObImage(L"EnterTheGungeon/Weapon_0.png");
	weapon->idle->pivot = OFFSET_LB;
	weapon->idle->scale.x = 29.0f;
	weapon->idle->scale.y = 21.0f;
	weapon->idle->SetParentRT(*weapon->col);

	scalar = 300.0f;
	curHp = maxHp = 3;

	for (auto& elem : bullet)
	{
		elem = new PlayerBullet;
		elem->col->scale.x = 8.0f;
		elem->col->scale.y = 8.0f;
		// elem->col->isVisible = false;
		elem->img = new ObImage(L"EnterTheGungeon/Player_0_Bullet_0.png");
		elem->img->scale.x = 8.0f;
		elem->img->scale.y = 8.0f;
		elem->img->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		elem->img->SetParentRT(*elem->col);
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
	for (auto& elem : bullet) elem->Release();
	Character::Release();
}

void Player::Update()
{
	CAM->position.x = Utility::Saturate((INPUT->GetWorldMousePos().x + idle->GetWorldPos().x) / 2,
		idle->GetWorldPos().x - 100.0f,
		idle->GetWorldPos().x + 100.0f);
	CAM->position.y = Utility::Saturate((INPUT->GetWorldMousePos().y + idle->GetWorldPos().y) / 2,
		idle->GetWorldPos().y - 100.0f,
		idle->GetWorldPos().y + 100.0f);

	weapon->col->rotation = Utility::DirToRadian(INPUT->GetWorldMousePos() - weapon->col->GetWorldPos());

	if (state == State::die)
	{
		isHit = false;
		scalar = 0.0f;
	}
	else if (state == State::idle)
	{
		if (isHitAnim)
		{
			idle->isVisible = false;
			hit->isVisible = true;

			if (TIMER->GetTick(timeHitAnim, 0.4f))	// 히트 애니용
			{
				hit->isVisible = false;
				idle->isVisible = true;

				isHitAnim = false;
			}
		}
		else
		{
			idle->isVisible = true;
			hit->isVisible = false;
		}

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
	}

	if (isHit)
	{
		Color c = Color(0.5f, 0.5f, 0.5f, RANDOM->Float());
		idle->color =
			walk->color =
			roll->color =
			hit->color =
			die->color =
			c;

		col->SetWorldPosX(col->GetWorldPos().x + RANDOM->Float(-1.0f, 1.0f));
		col->SetWorldPosY(col->GetWorldPos().y + RANDOM->Float(-1.0f, 1.0f));

		if (TIMER->GetTick(timeHit, 1.5f))
		{
			Color c = Color(0.5f, 0.5f, 0.5f, 1.0f);
			idle->color =
				hit->color =
				c;

			timeHit = 0.0f;
			isHit = false;
		}
	}


	if (INPUT->KeyPress(VK_LBUTTON))
	{
		if (canFire)
		{
			for (auto& elem : bullet)
			{
				if (elem->isFired) continue;

				Vector2 dir = INPUT->GetWorldMousePos() - col->GetWorldPos();
				dir.Normalize();
				elem->Spawn(Vector2(weapon->idle->GetWorldPivot().x + weapon->idle->scale.x / 2.0f,
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

	weapon->Update();
	idle->Update();
	walk->Update();
	roll->Update();
	hit->Update();
	die->Update();
	respawn->Update();
	for (auto& elem : bullet) elem->Update();
	Character::Update();
}

void Player::LateUpdate()
{
	for (auto& elem : bullet)
	{
		if (false == elem->isFired) continue;

		Vector2 dist = elem->col->GetWorldPos() - col->GetWorldPos();
		if (dist.x < -1200.0f || dist.x > 1200.0f ||
			dist.y < -1200.0f || dist.y > 1200.0f)
		{
			elem->Reload();
		}
	}
	for (auto& elem : bullet) elem->LateUpdate();
}

void Player::Render()
{
	weapon->Render();
	idle->Render();
	walk->Render();
	roll->Render();
	die->Render();
	respawn->Render();
	Character::Render();
	for (auto& elem : bullet) elem->Render();
}


void Player::Spawn()
{
	col->SetWorldPosX(0.0f);
	col->SetWorldPosY(0.0f);
}

void Player::Hit(const float damage)
{
	if (false == isHit)
	{
		// hp -= damage;	// 게이지 개념으로
		if (damage > 0)
		{
			isHit = true;
			isHitAnim = true;

			idle->isVisible = false;
			hit->isVisible = true;
			die->isVisible = false;

			hit->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
		}
	}
}

void Player::Die()
{
	if (state != State::die)
	{
		state = State::die;
		col->scale.x = 0.0f;
		col->scale.y = 0.0f;

		idle->isVisible = false;
		hit->isVisible = false;
		die->isVisible = true;
	}
}