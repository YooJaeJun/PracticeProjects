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

		rangeAtk = new ObCircle();
		rangeAtk->scale = Vector2(300.0f, 300.0f);
		rangeAtk->isFilled = false;
		rangeAtk->SetParentRT(*col);

		rangeTrace = new ObCircle();
		rangeTrace->scale = Vector2(550.0f, 550.0f);
		rangeTrace->isFilled = false;
		rangeTrace->SetParentRT(*col);

		rangeLook = new ObCircle();
		rangeLook->scale = Vector2(800.0f, 800.0f);
		rangeLook->isFilled = false;
		rangeLook->SetParentRT(*col);
	}

	Boss::~Boss()
	{
	}

	void Boss::Release()
	{
		SafeDelete(col);
		SafeDelete(walk);
		SafeDelete(rangeAtk);
		SafeDelete(rangeTrace);
		SafeDelete(rangeLook);
	}

	void Boss::Update()
	{
		//FSM
		switch (state)
		{
		case CharacterState::IDLE:
			Idle();
			break;
		case CharacterState::WALK:
			Walk();
			break;
		}

		col->Update();
		walk->Update();
		rangeAtk->Update();
		rangeTrace->Update();
		rangeLook->Update();
	}

	void Boss::Render()
	{
		col->Render();
		walk->Render();
		rangeAtk->Render();
		rangeTrace->Render();
		rangeLook->Render();
	}

	void Boss::Idle()
	{
		//idle -> walk
		if (moveDir != Vector2(0.0f, 0.0f))
		{
			state = CharacterState::WALK;
			walk->ChangeAnim(ANIMSTATE::LOOP, 0.1f, false);
		}
	}

	void Boss::Walk()
	{
		col->MoveWorldPos(moveDir * 200.0f * DELTA);

		//idle -> walk
		if (moveDir == Vector2(0.0f, 0.0f))
		{
			state = CharacterState::IDLE;
			walk->ChangeAnim(ANIMSTATE::STOP, 0.1f, false);
		}
	}

	void Boss::Atk()
	{
		walk->scale.x = RANDOM->Float(col->scale.x - 10.0f, col->scale.x + 10.0f);
		walk->scale.y = RANDOM->Float(col->scale.y - 10.0f, col->scale.y + 10.0f);
	}

	void Boss::Trace()
	{
		Boss::LookTarget();
		col->MoveWorldPos(targetDir * scalar * DELTA);
	}

	void Boss::LookTarget()
	{
		Character::LookTarget();
		walk->frame.y = frameY[targetDirstate];
	}
}