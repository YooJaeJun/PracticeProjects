#include "stdafx.h"

namespace Dir8
{
	Player::Player()
	{
		scalar = 200.0f;

		col = new ObRect();
		col->isFilled = false;
		col->scale = Vector2(16.0f, 16.0f) * 6.0f;
		col->SetWorldPos(Vector2(-350.0f, -300.0f));

		walk = new ObImage(L"Walk.png");
		walk->SetParentRT(*col);
		walk->scale = Vector2(16.0f, 16.0f) * 6.0f;
		walk->maxFrame = Int2(6, 8);

		roll = new ObImage(L"Roll.png");
		roll->SetParentRT(*col);
		roll->scale = Vector2(16.0f, 16.0f) * 6.0f;
		roll->maxFrame = Int2(6, 8);
		roll->isVisible = false;

		frameY[DIR_R] = 0;
		frameY[DIR_T] = 1;
		frameY[DIR_L] = 2;
		frameY[DIR_B] = 3;
		frameY[DIR_RB] = 4;
		frameY[DIR_LB] = 5;
		frameY[DIR_LT] = 6;
		frameY[DIR_RT] = 7;
	}

	Player::~Player()
	{
	}

	void Player::Release()
	{
		SafeDelete(col);
		SafeDelete(walk);
	}

	void Player::Update()
	{
		targetDir = INPUT->GetWorldMousePos() - col->GetWorldPos();

		//FSM
		switch (state)
		{
		case PlayerState::IDLE:
			Idle();
			break;
		case PlayerState::WALK:
			Walk();
			break;
		case PlayerState::ROLL:
			Roll();
			break;
		}

		col->Update();
		walk->Update();
		roll->Update();
	}

	void Player::Render()
	{
		col->Render();
		walk->Render();
		roll->Render();
	}

	void Player::Input()
	{
		moveDir = Vector2(0.0f, 0.0f);

		if (INPUT->KeyPress('A'))
		{
			moveDir.x = -1.0f;
		}
		else if (INPUT->KeyPress('D'))
		{
			moveDir.x = 1.0f;
		}

		if (INPUT->KeyPress('S'))
		{
			moveDir.y = -1.0f;
		}
		else if (INPUT->KeyPress('W'))
		{
			moveDir.y = 1.0f;
		}

		moveDir.Normalize();
	}

	void Player::Idle()
	{
		Input();
		LookTarget(INPUT->GetWorldMousePos(), walk);
		walk->frame.y = frameY[dirState];

		//idle -> walk
		if (moveDir != Vector2(0.0f, 0.0f))
		{
			state = PlayerState::WALK;
			walk->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		}
	}

	void Player::Walk()
	{
		Input();
		LookTarget(INPUT->GetWorldMousePos(), walk);
		walk->frame.y = frameY[dirState];

		col->MoveWorldPos(moveDir * scalar * DELTA);

		//idle -> walk
		if (moveDir == Vector2(0.0f, 0.0f))
		{
			state = PlayerState::IDLE;
			walk->ChangeAnim(ANIMSTATE::STOP, 0.1f);
			walk->frame.x = 0;
		}

		if (INPUT->KeyDown(VK_SPACE))
		{
			//walk -> roll
			state = PlayerState::ROLL;
			roll->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
			walk->isVisible = false;
			roll->isVisible = true;
			roll->frame.x = 0;
			roll->frame.y = frameY[dirState];
		}
	}

	void Player::Roll()
	{
		LookTarget(moveDir + col->GetWorldPos(), roll);

		timeRoll += DELTA;

		col->MoveWorldPos(moveDir * scalar * cos(timeRoll / 0.6f * DIV2PI) * DELTA);

		if (TIMER->GetTick(timeRoll, 0.6f))
		{
			state = PlayerState::IDLE;
			walk->ChangeAnim(ANIMSTATE::STOP, 0.1f);
			walk->isVisible = true;
			walk->frame.x = 0;
			roll->ChangeAnim(ANIMSTATE::STOP, 0.1f);
			roll->isVisible = false;
			roll->frame.x = 0;
		}
	}
}