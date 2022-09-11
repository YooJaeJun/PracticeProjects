#include "stdafx.h"

Player::Player()
{
	Init();
}

void Player::Init()
{
	Character::Init();
	hp = 5;
	scaleXCoef = 0.4;
	scaleYCoef = 0.5;

	col = new ObRect();
	col->scale = Vector2(1288.0f / 4.0f * scaleXCoef, 322.0f * scaleYCoef);
	col->pivot = OFFSET_B;
	col->isFilled = false;
	col->SetWorldPosX(-500.0f);
	Spawn();

	run = new ObImage(L"Cookie/Run.png");
	run->pivot = OFFSET_B;
	run->maxFrame.x = 4;
	run->scale = Vector2(1288.0f / run->maxFrame.x, 322.0f);
	run->uv = Vector4(0.0f, 0.0f, 1.0f / run->maxFrame.x, 1.0f);
	run->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	run->SetParentRT(*col);

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

	state = State::RUN;
	gravity = 0.0f;
	speed = speedOrigin = 400.0f;
	isDoubleJump = false;
	timerHit = 0.0f;
	isBoost = false;
	timerBoost = 0.0f;
	isLand = false;
	timerLand = 0.0f;
}

void Player::Release()
{
	Character::Release();
	SafeDelete(run);
	SafeDelete(slide);
	SafeDelete(jump);
}

void Player::Update()
{
	ImGui::SliderInt("Hp", &hp, 0, 5);
	if (hp <= 0)
	{
		hp = 0;
		ImGui::Text("You died, but the test must go on.");
	}

	if (state == State::RUN)
	{
		// 착지 애니메이션
		if (isLand)
		{
			if (TIMER->GetTick(timerLand, 0.2f))
			{
				col->scale.x = run->scale.x * scaleXCoef;
				col->scale.y = run->scale.y * scaleYCoef;
				land->isVisible = false;
				run->isVisible = true;
				timerLand = 0.0f;
				isLand = false;
			}
		}
		else if (isBoost)
		{
			run->isVisible = false;
			boost->isVisible = true;
		}
		else
		{
			run->isVisible = true;
			boost->isVisible = false;
		}

		//run -> slide
		if (INPUT->KeyPress(VK_DOWN))
		{
			state = State::SLIDE;

			col->scale.x = slide->scale.x * scaleXCoef;
			col->scale.y = slide->scale.y * 0.25f;
			run->isVisible = false;
			slide->isVisible = true;
			land->isVisible = false;
			boost->isVisible = false;
			slide->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		}
		//run -> jump
		if (INPUT->KeyDown(VK_SPACE))
		{
			state = State::JUMP;

			gravity = -700.0f;
			col->scale.x = jump->scale.x * scaleXCoef;
			col->scale.y = jump->scale.y * 0.4f;
			run->isVisible = false;
			jump->isVisible = true;
			land->isVisible = false;
			boost->isVisible = false;
			jump->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
		}
	}
	else if (state == State::SLIDE)
	{
		//slide -> run
		if (INPUT->KeyUp(VK_DOWN))
		{
			state = State::RUN;
			col->scale.x = run->scale.x * scaleXCoef;
			col->scale.y = run->scale.y * scaleYCoef;
			run->isVisible = true;
			slide->isVisible = false;
		}
		//slide -> jump
		if (INPUT->KeyDown(VK_SPACE))
		{
			state = State::JUMP;

			gravity = -700.0f;
			col->scale.x = jump->scale.x * scaleXCoef;
			col->scale.y = jump->scale.y * 0.4f;
			slide->isVisible = false;
			jump->isVisible = true;
			jump->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
		}
	}
	else if (state == State::JUMP)
	{
		if (INPUT->KeyDown(VK_SPACE) && !isDoubleJump)
		{
			gravity = -700.0f;
			col->scale.x = doubleJump->scale.x * scaleXCoef;
			col->scale.y = doubleJump->scale.y * scaleYCoef;
			isDoubleJump = true;
			jump->isVisible = false;
			doubleJump->isVisible = true;
			doubleJump->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
		}
	}

	if (isHit)
	{
		Color c = Color(0.5f, 0.5f, 0.5f, RANDOM->Float());
		run->color =
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
			gravity = 0.0f;	// 중력 안 받게
		}

		if (TIMER->GetTick(timerHit, 2.0f))
		{
			Color c = Color(0.5f, 0.5f, 0.5f, 1.0f);
			run->color =
				slide->color =
				jump->color =
				doubleJump->color =
				land->color =
				hit->color =
				boost->color =
				c;
			timerHit = 0.0f;
			isHit = false;
		}
	}

	if (isBoost)
	{
		if (col->GetWorldPos().y < -app.GetHalfHeight() + 48.0f * 2.5f)
		{
			Spawn();
			gravity = 0.0f;	// 중력 안 받게
		}
		if (TIMER->GetTick(timerBoost, 5.0f))
		{
			speed = speedOrigin;
			timerBoost = 0.0f;
			isBoost = false;
		}
	}

	if (col->GetWorldPos().y + col->scale.y < -app.GetHalfHeight())
	{
		Hit(2);
		Spawn();
	}


	CAM->position += RIGHT * speed * DELTA;

	col->MoveWorldPos(RIGHT * speed * DELTA + DOWN * gravity * DELTA);
	gravity += 2500.0f * DELTA;

	col->Update();
	run->Update();
	slide->Update();
	jump->Update();
	doubleJump->Update();
	land->Update();
	hit->Update();
	boost->Update();
}

void Player::LateUpdate()
{
}

void Player::Render()
{
	col->Render();
	run->Render();
	slide->Render();
	jump->Render();
	doubleJump->Render();
	land->Render();
	hit->Render();
	boost->Render();
}

void Player::Spawn()
{
	col->SetWorldPosY(-app.GetHalfHeight() + 48.0f * 2.5f);
}

void Player::LandOn()
{
	col->SetWorldPosY(-app.GetHalfHeight() + 48.0f * 2.5f);
	gravity = 0.0f;

	//jump -> run (착지 애니메이션)
	if (state == State::JUMP)
	{
		state = State::RUN;
		col->scale.x = land->scale.x * scaleXCoef;
		col->scale.y = land->scale.y * scaleYCoef;
		isDoubleJump = false;
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
		hp -= damage;
		if (damage > 0)
		{
			isHit = true;
			isDoubleJump = false;
		}
	}
}

void Player::Boost()
{
	timerBoost = 0.0f;

	if (false == isBoost)
	{
		speedOrigin = speed;
		speed *= 3.0f;
		isBoost = true;
	}
}