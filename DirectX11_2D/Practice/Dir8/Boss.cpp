#include "stdafx.h"

namespace Dir8
{
	Boss::Boss()
	{
		scalar = 200.0f;
		state = BossState::IDLE;

		col = new ObRect();
		col->isFilled = false;
		col->scale = Vector2(128.0f, 1016.0f / 8.0f) * 1.5f;

		img = new ObImage(L"boss.bmp");
		img->SetParentRT(*col);
		img->scale = Vector2(128.0f, 1016.0f / 8.0f) * 1.5f;
		img->maxFrame = Int2(1, 8);

		frameY[DIR_R] = 0;
		frameY[DIR_L] = 1;
		frameY[DIR_RB] = 2;
		frameY[DIR_LT] = 3;
		frameY[DIR_T] = 4;
		frameY[DIR_B] = 5;
		frameY[DIR_LB] = 6;
		frameY[DIR_RT] = 7;

		for (auto& elem : range)
		{
			elem = new ObCircle();
			elem->isFilled = false;
			elem->SetParentRT(*col);
		}
		float scale = (float)BossState::LOOK;
		range[0]->scale = Vector2(scale, scale) * 2.0f;
		scale = (float)BossState::MOVE;
		range[1]->scale = Vector2(scale, scale) * 2.0f;
		scale = (float)BossState::ATTACK;
		range[2]->scale = Vector2(scale, scale) * 2.0f;
	}

	Boss::~Boss()
	{
	}

	void Boss::Release()
	{
		SafeDelete(col);
		SafeDelete(img);

		for (auto& elem : range)
		{
			SafeDelete(elem);
		}
	}

	void Boss::Update()
	{
		Vector2 dist = targetPos - GetPos();
		distance = dist.Length();

		//FSM
		switch (state)
		{
		case BossState::IDLE:
			Idle();
			break;
		case BossState::LOOK:
			Look();
			break;
		case BossState::MOVE:
			Move();
			break;
		case BossState::ATTACK:
			Attack();
			break;
		}

		col->Update();
		img->Update();
		for (auto& elem : range)
		{
			elem->Update();
		}
	}

	void Boss::Render()
	{
		col->Render();
		img->Render();
		for (auto& elem : range)
		{
			elem->Render();
		}
	}

	void Boss::Idle()
	{
		if (distance < (float)BossState::LOOK)
		{
			state = BossState::LOOK;
		}
	}

	void Boss::Look()
	{
		LookTarget(targetPos, img);

		if (distance < (float)BossState::MOVE)
		{
			state = BossState::MOVE;
		}

		if (distance > (float)BossState::LOOK)
		{
			state = BossState::IDLE;
		}
	}

	void Boss::Move()
	{
		LookTarget(targetPos, img);

		moveDir = targetPos - col->GetWorldPos();
		moveDir.Normalize();
		col->MoveWorldPos(moveDir * scalar * DELTA);

		if (distance < (float)BossState::ATTACK)
		{
			state = BossState::ATTACK;
		}

		if (distance > (float)BossState::MOVE)
		{
			state = BossState::LOOK;
		}
	}

	void Boss::Attack()
	{
		float plus;

		if (switching) plus = 1.0f;
		else plus = -1.0f;

		img->scale.x += plus * scalar * DELTA;
		img->scale.y -= plus * scalar * DELTA;

		if (img->scale.x < 50.0f || img->scale.y < 50.0f)
		{
			switching = !switching;
		}

		if (distance > (float)BossState::ATTACK)
		{
			state = BossState::MOVE;
			img->scale = Vector2(128.0f, 127.0f) * 1.5f;
		}
	}
}