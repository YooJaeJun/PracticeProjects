#include "stdafx.h"

Airplane::Airplane()
{
	Init();
}

void Airplane::Init()
{
	Character::Init();
	scaleCoef = Vector2(0.8f, 0.8f);

	col = new ObRect();
	col->pivot = OFFSET_T;
	idleImgSize = Vector2(224.0f, 40.0f);
	col->scale = Vector2(idleImgSize.x / 7.0f, idleImgSize.y) * scaleCoef;
	col->color = Color(1.0f, 1.0f, 1.0f);
	col->isFilled = false;
	Spawn();

	idle = new ObImage(L"LeftRight.png");
	idle->pivot = OFFSET_T;
	idle->maxFrame.x = 7;
	idle->scale = Vector2(idleImgSize.x / idle->maxFrame.x, idleImgSize.y) * 3.0f;
	idle->SetWorldPosY(idle->scale.y / 2.5f);
	idle->uv = Vector4(3.0f / idle->maxFrame.x, 0.0f, 4.0f / idle->maxFrame.x, 1.0f);
	idle->ChangeAnim(ANIMSTATE::STOP, 0.1f);
	idle->SetParentRT(*col);

	boost = new ObImage(L"Start.png");
	boost->pivot = OFFSET_T;
	idleImgSize = Vector2(352.0f, 120.0f);
	boost->maxFrame.x = 11;
	boost->scale = Vector2(idleImgSize.x / boost->maxFrame.x, idleImgSize.y) * 2.4f;
	boost->SetWorldPosY(idle->scale.y / 2.5f);
	boost->uv = Vector4(0.0f, 0.0f, 1.0f / boost->maxFrame.x, 1.0f);
	boost->isVisible = false;
	boost->ChangeAnim(ANIMSTATE::LOOP, 0.05f);
	boost->SetParentRT(*col);

	hit = new ObImage(L"Cookie/Hit.png");
	hit->pivot = OFFSET_T;
	hit->maxFrame.x = 5;
	hit->scale = Vector2(1610.0f / hit->maxFrame.x, 322.0f);
	hit->uv = Vector4(0.0f, 0.0f, 1.0f / hit->maxFrame.x, 1.0f);
	hit->isVisible = false;
	hit->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
	hit->SetParentRT(*col);

	die = new ObImage(L"Cookie/Die.png");
	die->pivot = OFFSET_T;
	die->maxFrame.x = 6;
	die->scale = Vector2(1932.0f / die->maxFrame.x, 322.0f);
	die->uv = Vector4(0.0f, 0.0f, 1.0f / die->maxFrame.x, 1.0f);
	die->isVisible = false;
	die->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
	die->SetParentRT(*col);

	key = 0.0f;
	moveDir = Vector2(0.0f, 0.0f);

	state = PlState::RUN;
	timeLeft = 0.0f;
	timeRight = 0.0f;
	speed = speedOrigin = 300.0f;
	isHit = false;
	timeHit = 0.0f;
	isHitAnim = false;
	timeHitAnim = 0.0f;
	isBoost = false;
}

void Airplane::Release()
{
	Character::Release();
	SafeDelete(idle);
}

void Airplane::Update()
{
	if (state == PlState::DIE)
	{
		isHit = false;
		speed = 0.0f;
		if (col->GetWorldPos().x < -app.GetHalfHeight() + 48.0f * 2.5f)
		{
			col->SetWorldPosY(-app.GetHalfHeight() + 48.0f * 2.5f);
		}
	}
	else if (state == PlState::RUN)
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
		else if (isBoost)
		{
			idle->isVisible = false;
			boost->isVisible = true;
		}
		else
		{
			idle->isVisible = true;
			boost->isVisible = false;
			hit->isVisible = false;
		}

		if (INPUT->KeyPress(VK_LEFT))
		{
			key -= DELTA * 3.0f;
			moveDir.x = -1.0f;
		}
		else if (INPUT->KeyPress(VK_RIGHT))
		{
			key += DELTA * 3.0f;
			moveDir.x = 1.0f;
		}
		else
		{
			moveDir.x = 0.0f;
			if (key < -DELTA * 1.5f)
			{
				key += DELTA * 1.5f;
			}
			else if (key > DELTA * 1.5f)
			{
				key -= DELTA * 1.5f;
			}
			else
			{
				key = 0.0f;
			}
		}

		key = Utility::Saturate(key, -3.0f, 3.0f);


		if (INPUT->KeyPress(VK_UP))
		{
			moveDir.y = 1.0f;
		}
		else if (INPUT->KeyPress(VK_DOWN))
		{
			moveDir.y = -1.0f;
		}
		else 
		{
			moveDir.y = 0.0f;
		}

		idle->maxFrame.x = int(key + 3);

		moveDir.Normalize();
		col->MoveWorldPos(moveDir * speed * DELTA);


		//run -> boost
		if (INPUT->KeyPress(VK_SPACE))
		{
			Boost();
		}
		else if (INPUT->KeyUp(VK_SPACE))
		{
			CancelBoost();
		}
	}

	if (isHit)
	{
		Color c = Color(0.5f, 0.5f, 0.5f, RANDOM->Float());
		idle->color =
			hit->color =
			boost->color =
			c;

		col->SetWorldPosX(col->GetWorldPos().x + RANDOM->Float(-1.0f, 1.0f));
		col->SetWorldPosY(col->GetWorldPos().y + RANDOM->Float(-1.0f, 1.0f));

		if (col->GetWorldPos().y < -app.GetHalfHeight() + 48.0f * 2.5f)
		{
			Spawn();
		}

		if (TIMER->GetTick(timeHit, 1.5f))
		{
			Color c = Color(0.5f, 0.5f, 0.5f, 1.0f);
			idle->color =
				hit->color =
				boost->color =
				c;

			timeHit = 0.0f;
			isHit = false;
		}
	}

	col->Update();
	idle->Update();
	boost->Update();
	hit->Update();
	die->Update();
}

void Airplane::LateUpdate()
{
}

void Airplane::Render()
{
	idle->Render();
	boost->Render();
	hit->Render();
	die->Render();
	col->Render();
}


void Airplane::Spawn()
{
	col->SetWorldPosX(0.0f);
	col->SetWorldPosY(-app.GetHalfHeight() + 200.0f);
}

void Airplane::Hit(const float damage)
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
			boost->isVisible = false;
			die->isVisible = false;

			hit->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
		}
	}
}

void Airplane::Boost()
{
	if (false == isBoost)
	{
		speedOrigin = speed;
		speed *= 2.0f;
		isBoost = true;
	}
}

void Airplane::CancelBoost()
{
	speed = speedOrigin;
	idle->isVisible = true;
	boost->isVisible = false;
	isBoost = false;
	idle->uv.x = 3.0f / 7.0f;
	idle->uv.z = 4.0f / 7.0f;
}

void Airplane::Die()
{
	if (state != PlState::DIE)
	{
		state = PlState::DIE;
		col->scale.x = 0.0f;
		col->scale.y = 0.0f;

		idle->isVisible = false;
		hit->isVisible = false;
		boost->isVisible = false;
		die->isVisible = true;
	}
}
