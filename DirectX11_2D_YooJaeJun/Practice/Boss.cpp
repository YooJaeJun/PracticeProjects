#include "stdafx.h"

namespace Dir8
{
	Boss::Boss()
	{
		scalar = 200.0f;

		col = new ObRect();
		col->isFilled = false;
		col->scale = Vector2(128.0f, 1016.0f / 8.0f) * 1.5f;

		walk = new ObImage(L"boss.bmp");
		walk->SetParentRT(*col);
		walk->scale = Vector2(128.0f, 1016.0f / 8.0f) * 1.5f;
		walk->maxFrame = Int2(1, 8);

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
		range[0]->scale = Vector2((float)BossState::ATTACK, (float)BossState::ATTACK) * 2.0f;
		range[1]->scale = Vector2((float)BossState::MOVE, (float)BossState::MOVE) * 2.0f;
		range[2]->scale = Vector2((float)BossState::LOOK, (float)BossState::LOOK) * 2.0f;
	}

	Boss::~Boss()
	{
	}

	void Boss::Release()
	{
		SafeDelete(col);
		SafeDelete(walk);

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
		walk->Update();
		for (auto& elem : range)
		{
			elem->Update();
		}
	}

	void Boss::Render()
	{
		col->Render();
		walk->Render();
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
		LookTarget(targetPos, walk);
		walk->frame.y = frameY[dirState];

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
		Look();

		Vector2 dir = targetPos - col->GetWorldPos();
		dir.Normalize();
		col->MoveWorldPos(dir * scalar * DELTA);

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

		walk->scale.x += plus * scalar * DELTA;
		walk->scale.y -= plus * scalar * DELTA;

		if (walk->scale.x < 50.0f || walk->scale.y < 50.0f)
		{
			switching = !switching;
		}

		if (distance > (float)BossState::ATTACK)
		{
			state = BossState::MOVE;
			walk->scale = Vector2(128.0f, 127.0f) * 1.5f;
		}
	}
}