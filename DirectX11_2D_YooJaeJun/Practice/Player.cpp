#include "stdafx.h"

namespace Dir8
{
	Player::Player()
	{
		scalar = 200.0f;
		scalarCoef = 100.0f;

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
		case CharacterState::IDLE:
			Idle();
			break;
		case CharacterState::WALK:
			Walk();
			break;
		case CharacterState::ROLL:
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
		LookTarget();
		walk->frame.y = frameY[targetDirstate];

		//idle -> walk
		if (moveDir != Vector2(0.0f, 0.0f))
		{
			state = CharacterState::WALK;
			walk->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		}
	}

	void Player::Walk()
	{
		Input();
		LookTarget();
		SetMoveDir();
		walk->frame.y = frameY[targetDirstate];

		col->MoveWorldPos(moveDir * scalar * DELTA);

		//idle -> walk
		if (moveDir == Vector2(0.0f, 0.0f))
		{
			state = CharacterState::IDLE;
			walk->ChangeAnim(ANIMSTATE::STOP, 0.1f);
			walk->frame.x = 0;
		}

		if (INPUT->KeyDown(VK_SPACE))
		{
			//walk -> roll
			state = CharacterState::ROLL;
			roll->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
			walk->isVisible = false;
			roll->isVisible = true;
			roll->frame.x = 0;
			roll->frame.y = frameY[moveDirState];
			scalar = 800.0f;
			scalarCoef = 100.0f;
		}
	}

	void Player::Roll()
	{
		scalarCoef += 4000.0f * DELTA;
		scalar -= scalarCoef * DELTA;

		col->MoveWorldPos(moveDir * scalar * DELTA);

		if (TIMER->GetTick(timeRoll, 0.5f))
		{
			state = CharacterState::IDLE;
			walk->ChangeAnim(ANIMSTATE::STOP, 0.1f);
			walk->isVisible = true;
			walk->frame.x = 0;
			roll->ChangeAnim(ANIMSTATE::STOP, 0.1f);
			roll->isVisible = false;
			roll->frame.x = 0;
			scalar = 200.0f;
		}
	}

	void Player::SetMoveDir()
	{
		float radian = Utility::DirToRadian(moveDir);

		if (radian < DIV8PI && radian > -DIV8PI)
		{
			moveDirState = DIR_R;
		}
		else if (radian > DIV8PI && radian < DIV8PI + DIV4PI)
		{
			moveDirState = DIR_RT;
		}
		else if (radian > DIV8PI + DIV4PI && radian < DIV8PI + DIV4PI * 2.0f)
		{
			moveDirState = DIR_T;
		}
		else if (radian > DIV8PI + DIV4PI * 2.0f && radian < DIV4PI * 3.0f + DIV8PI)
		{
			moveDirState = DIR_LT;
		}
		else if (radian > -(DIV8PI + DIV4PI * 3.0f) && radian < -(DIV4PI * 2.0f + DIV8PI))
		{
			moveDirState = DIR_LB;
		}
		else if (radian > -(DIV8PI + DIV4PI * 2.0f) && radian < -(DIV4PI + DIV8PI))
		{
			moveDirState = DIR_B;
		}
		else if (radian > -(DIV8PI + DIV4PI) && radian < -DIV8PI)
		{
			moveDirState = DIR_RB;
		}
		else
		{
			moveDirState = DIR_L;
		}
	}
}