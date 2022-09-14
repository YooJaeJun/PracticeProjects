#include "stdafx.h"

Player::Player()
{
	Init();
}

void Player::Init()
{
	Character::Init();
	scaleCoef.x = 0.3f;
	scaleCoef.y = 0.45f;

	col = new ObRect();
	col->scale = Vector2(1288.0f / 4.0f * scaleCoef.x, 322.0f * scaleCoef.y);
	col->pivot = OFFSET_B;
	col->isFilled = false;
	Spawn();

	idle = new ObImage(L"Cookie/Run.png");
	idle->pivot = OFFSET_B;
	idle->maxFrame.x = 4;
	idle->scale = Vector2(1288.0f / idle->maxFrame.x, 322.0f);
	idle->uv = Vector4(0.0f, 0.0f, 1.0f / idle->maxFrame.x, 1.0f);
	idle->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	idle->SetParentRT(*col);

	slide = new ObImage(L"Cookie/Slide.png");
	slide->pivot = OFFSET_B;
	slide->maxFrame.x = 2;
	slide->scale = Vector2(644.0f / slide->maxFrame.x, 322.0f);
	slide->uv = Vector4(0.0f, 0.0f, 1.0f / slide->maxFrame.x, 1.0f);
	slide->isVisible = false;
	slide->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	slide->SetParentRT(*col);

	jump = new ObImage(L"Cookie/Jump.png");
	jump->pivot = OFFSET_B;
	jump->maxFrame.x = 2;
	jump->scale = Vector2(644.0f / jump->maxFrame.x, 322.0f);
	jump->uv = Vector4(0.0f, 0.0f, 1.0f / jump->maxFrame.x, 1.0f);
	jump->isVisible = false;
	jump->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
	jump->SetParentRT(*col);

	doubleJump = new ObImage(L"Cookie/DoubleJump.png");
	doubleJump->pivot = OFFSET_B;
	doubleJump->maxFrame.x = 6;
	doubleJump->scale = Vector2(1932.0f / doubleJump->maxFrame.x, 322.0f);
	doubleJump->uv = Vector4(0.0f, 0.0f, 1.0f / doubleJump->maxFrame.x, 1.0f);
	doubleJump->isVisible = false;
	doubleJump->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
	doubleJump->SetParentRT(*col);

	land = new ObImage(L"Cookie/Land.png");
	land->pivot = OFFSET_B;
	land->maxFrame.x = 1;
	land->scale = Vector2(322.0f / land->maxFrame.x, 322.0f);
	land->uv = Vector4(0.0f, 0.0f, 1.0f / land->maxFrame.x, 1.0f);
	land->isVisible = false;
	land->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
	land->SetParentRT(*col);

	hit = new ObImage(L"Cookie/Hit.png");
	hit->pivot = OFFSET_B;
	hit->maxFrame.x = 5;
	hit->scale = Vector2(1610.0f / hit->maxFrame.x, 322.0f);
	hit->uv = Vector4(0.0f, 0.0f, 1.0f / hit->maxFrame.x, 1.0f);
	hit->isVisible = false;
	hit->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
	hit->SetParentRT(*col);

	boost = new ObImage(L"Cookie/Boost.png");
	boost->pivot = OFFSET_B;
	boost->maxFrame.x = 4;
	boost->scale = Vector2(1288.0f / boost->maxFrame.x, 322.0f);
	boost->uv = Vector4(0.0f, 0.0f, 1.0f / boost->maxFrame.x, 1.0f);
	boost->isVisible = false;
	boost->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	boost->SetParentRT(*col);

	die = new ObImage(L"Cookie/Die.png");
	die->pivot = OFFSET_B;
	die->maxFrame.x = 6;
	die->scale = Vector2(1932.0f / die->maxFrame.x, 322.0f);
	die->uv = Vector4(0.0f, 0.0f, 1.0f / die->maxFrame.x, 1.0f);
	die->isVisible = false;
	die->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
	die->SetParentRT(*col);

	state = PlState::RUN;
	gravity = 0.0f;
	speed = speedOrigin = 400.0f;
	isHit = false;
	timeHit = 0.0f;
	isHitAnim = false;
	timeHitAnim = 0.0f;
	isBoost = false;
	timeBoost = 0.0f;
	isLand = false;
	timeLand = 0.0f;
}

void Player::Release()
{
	Character::Release();
	SafeDelete(idle);
	SafeDelete(slide);
	SafeDelete(jump);
}

void Player::Update()
{
	cout << "Player State " << (int)state << '\n';

	speed += 10.0f * DELTA;

	if (state == PlState::DIE)
	{
		isHit = false;
		speed = 0.0f;
		if (col->GetWorldPos().x < -app.GetHalfHeight() + 48.0f * 2.5f)
		{
			col->SetWorldPosY(-app.GetHalfHeight() + 48.0f * 2.5f);
			gravity = 0.0f;
		}
	}
	else if (state == PlState::RUN)
	{
		if (isHitAnim)
		{
			idle->isVisible = false;
			hit->isVisible = true;
			land->isVisible = false;

			if (TIMER->GetTick(timeHitAnim, 0.4f))	// ��Ʈ �ִϿ�
			{
				hit->isVisible = false;
				idle->isVisible = true;

				isHitAnim = false;
			}
		}
		else if (isLand)
		{
			if (TIMER->GetTick(timeLand, 0.2f))
			{
				col->scale.x = idle->scale.x * scaleCoef.x;
				col->scale.y = idle->scale.y * scaleCoef.y;
				land->isVisible = false;
				idle->isVisible = true;
				timeLand = 0.0f;
				isLand = false;
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

		//run -> slide
		if (INPUT->KeyPress(VK_DOWN))
		{
			Slide();
		}
		//run -> jump
		if (INPUT->KeyDown(VK_SPACE))
		{
			Jump();
		}
	}
	else if (state == PlState::SLIDE)
	{
		//slide -> run
		if (INPUT->KeyUp(VK_DOWN))
		{
			CancelSlide();
		}
		//slide -> jump
		if (INPUT->KeyDown(VK_SPACE))
		{
			Jump();
		}
	}
	else if (state == PlState::JUMP)
	{
		if (INPUT->KeyDown(VK_SPACE))
		{
			DoubleJump();
		}
	}
	else if (state == PlState::DOUBLEJUMP)
	{
	}

	if (isHit)
	{
		Color c = Color(0.5f, 0.5f, 0.5f, RANDOM->Float());
		idle->color =
			slide->color =
			jump->color =
			doubleJump->color =
			land->color =
			hit->color =
			boost->color =
			c;

		col->SetWorldPosX(col->GetWorldPos().x + RANDOM->Float(-1.0f, 1.0f));
		col->SetWorldPosY(col->GetWorldPos().y + RANDOM->Float(-1.0f, 1.0f));

		if (col->GetWorldPos().y < -app.GetHalfHeight() + 48.0f * 2.5f)
		{
			Spawn();
			gravity = 0.0f;	// �߷� �� �ް�
		}

		if (TIMER->GetTick(timeHit, 1.5f))
		{
			Color c = Color(0.5f, 0.5f, 0.5f, 1.0f);
			idle->color =
				slide->color =
				jump->color =
				doubleJump->color =
				land->color =
				hit->color =
				boost->color =
				c;

			timeHit = 0.0f;
			isHit = false;
		}
	}

	if (isBoost)
	{
		if (col->GetWorldPos().y < -app.GetHalfHeight() + 48.0f * 2.5f)
		{
			Spawn();
			gravity = 0.0f;	// �߷� �� �ް�
		}
		if (TIMER->GetTick(timeBoost, 4.0f))
		{
			speed = speedOrigin;
			timeBoost = 0.0f;
			isBoost = false;
			isHit = true;
		}
	}

	CAM->position += RIGHT * speed * DELTA;

	col->MoveWorldPos(RIGHT * speed * DELTA + DOWN * gravity * DELTA);
	gravity += 2500.0f * DELTA;

	col->Update();
	idle->Update();
	slide->Update();
	jump->Update();
	doubleJump->Update();
	land->Update();
	hit->Update();
	boost->Update();
	die->Update();
}

void Player::LateUpdate()
{
}

void Player::Render()
{
	col->Render();
	idle->Render();
	slide->Render();
	jump->Render();
	doubleJump->Render();
	land->Render();
	hit->Render();
	boost->Render();
	die->Render();
}


void Player::Jump()
{
	state = PlState::JUMP;
	gravity = -800.0f;
	col->scale.x = jump->scale.x * scaleCoef.x;
	col->scale.y = jump->scale.y * 0.4f;

	idle->isVisible = false;
	slide->isVisible = false;
	jump->isVisible = true;
	land->isVisible = false;
	boost->isVisible = false;
	hit->isVisible = false;
	isHitAnim = false;

	jump->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
}

void Player::DoubleJump()
{
	state = PlState::DOUBLEJUMP;
	gravity = -800.0f;
	col->scale.x = doubleJump->scale.x * scaleCoef.x;
	col->scale.y = doubleJump->scale.y * scaleCoef.y;

	jump->isVisible = false;
	doubleJump->isVisible = true;
	hit->isVisible = false;
	isHitAnim = false;

	doubleJump->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
}

void Player::Slide()
{
	state = PlState::SLIDE;
	col->scale.x = slide->scale.x * scaleCoef.x;
	col->scale.y = slide->scale.y * 0.25f;

	idle->isVisible = false;
	slide->isVisible = true;
	land->isVisible = false;
	boost->isVisible = false;
	hit->isVisible = false;
	isHitAnim = false;

	slide->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
}

void Player::CancelSlide()
{
	state = PlState::RUN;
	col->scale.x = idle->scale.x * scaleCoef.x;
	col->scale.y = idle->scale.y * scaleCoef.y;

	idle->isVisible = true;
	slide->isVisible = false;
	hit->isVisible = false;
	isHitAnim = false;
}

void Player::Spawn()
{
	col->SetWorldPosX(CAM->position.x - app.GetHalfWidth() + col->scale.x * 2.0f);
	col->SetWorldPosY(-app.GetHalfHeight() + 48.0f * 2.5f + 1.0f);
}

void Player::LandOn()
{
	col->SetWorldPosY(-app.GetHalfHeight() + 48.0f * 2.5f);
	gravity = 0.0f;

	//jump -> run (���� �ִϸ��̼�)
	if (state == PlState::JUMP || state == PlState::DOUBLEJUMP)
	{
		state = PlState::RUN;
		col->scale.x = land->scale.x * scaleCoef.x;
		col->scale.y = land->scale.y * scaleCoef.y;

		jump->isVisible = false;
		doubleJump->isVisible = false;
		land->isVisible = true;
		isLand = true;
	}

	col->Update();
}

void Player::Hit(const float damage)
{
	if (false == isHit)
	{
		// hp -= damage;	// ������ ��������
		if (damage > 0)
		{
			gravity = 500.0f;
			isHit = true;
			isHitAnim = true;

			idle->isVisible = false;
			slide->isVisible = false;
			jump->isVisible = false;
			doubleJump->isVisible = false;
			land->isVisible = false;
			hit->isVisible = true;
			boost->isVisible = false;
			die->isVisible = false;

			hit->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
		}
	}
}

void Player::Boost()
{
	timeBoost = 0.0f;

	if (false == isBoost)
	{
		speedOrigin = speed;
		speed *= 3.0f;
		isBoost = true;
	}
}

void Player::Die()
{
	if (state != PlState::DIE)
	{
		state = PlState::DIE;
		col->scale.x = 0.0f;
		col->scale.y = 0.0f;

		idle->isVisible = false;
		slide->isVisible = false;
		jump->isVisible = false;
		doubleJump->isVisible = false;
		land->isVisible = false;
		hit->isVisible = false;
		boost->isVisible = false;
		die->isVisible = true;
	}
}
