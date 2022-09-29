#include "stdafx.h"

Player::Player()
{
	col = new ObRect();
	col->isFilled = false;
	col->scale = Vector2(16.0f, 16.0f) * 6.0f;

	walk = new ObImage(L"Walk.png");
	walk->SetParentRT(*col);
	walk->scale = Vector2(16.0f, 16.0f) * 6.0f;
	walk->maxFrame = Int2(6, 8);

	frameY[DIR_R] = 0;
	frameY[DIR_T] = 1;
	frameY[DIR_L] = 2;
	frameY[DIR_B] = 3;
	frameY[DIR_RB] = 4;
	frameY[DIR_LB] = 5;
	frameY[DIR_LT] = 6;
	frameY[DIR_RT] = 7;

	plState = PlState::IDLE;
}

Player::~Player()
{
}

void Player::Update()
{
	//FSM
	switch (plState)
	{
	case PlState::IDLE:
		Idle();
		break;
	case PlState::WALK:
		Walk();
		break;
	}

	col->Update();
	walk->Update();
}

void Player::Render()
{
	col->Render();
	walk->Render();
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

void Player::LookTarget()
{
	Vector2 dir = INPUT->GetWorldMousePos() - col->GetWorldPos();
	float radian = Utility::DirToRadian(dir);

	if (radian < DIV8PI && radian > -DIV8PI)
	{
		dirstate = DIR_R;
	}
	else if (radian > DIV8PI && radian < DIV8PI + DIV4PI)
	{
		dirstate = DIR_RT;
	}
	else if (radian > DIV8PI + DIV4PI && radian < DIV8PI + DIV4PI * 2.0f)
	{
		dirstate = DIR_T;
	}
	else if (radian > DIV8PI + DIV4PI * 2.0f && radian < DIV4PI * 3.0f + DIV8PI)
	{
		dirstate = DIR_LT;
	}
	else if (radian > -(DIV8PI + DIV4PI * 3.0f) && radian < -(DIV4PI * 2.0f + DIV8PI))
	{
		dirstate = DIR_LB;
	}
	else if (radian > -(DIV8PI + DIV4PI * 2.0f) && radian < -(DIV4PI + DIV8PI))
	{
		dirstate = DIR_B;
	}
	else if (radian > -(DIV8PI + DIV4PI) && radian < -DIV8PI)
	{
		dirstate = DIR_RB;
	}
	else
	{
		dirstate = DIR_L;
	}

	walk->frame.y = frameY[dirstate];
}

void Player::Idle()
{
	Input();
	LookTarget();

	//idle -> walk
	if (moveDir != Vector2(0.0f, 0.0f))
	{
		plState = PlState::WALK;
		walk->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	}
}

void Player::Walk()
{
	Input();
	LookTarget();

	col->MoveWorldPos(moveDir * 200.0f * DELTA);

	//idle -> walk
	if (moveDir == Vector2(0.0f, 0.0f))
	{
		plState = PlState::IDLE;
		walk->ChangeAnim(ANIMSTATE::STOP, 0.1f);
		walk->frame.x = 0;
	}
}
