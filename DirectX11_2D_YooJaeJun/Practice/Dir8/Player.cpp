#include "stdafx.h"

namespace Dir8
{
	Player::Player()
	{
		scalar = 200.0f;
		lastPos = Vector2(0.0f, 0.0f);

		col = new ObRect();
		col->isFilled = false;
		col->scale = Vector2(16.0f, 16.0f) * 6.0f;
		col->SetWorldPos(Vector2(-350.0f, -300.0f));
		col->color = Color(1.0f, 1.0f, 1.0f, 1.0f);

		colTile = new ObRect;
		colTile->scale = Vector2(col->scale.x / 3.0f, col->scale.y / 4.0f);
		colTile->SetParentRT(*col);
		colTile->SetLocalPosY(col->GetWorldPos().y - 35.0f);
		colTile->isFilled = false;
		colTile->isVisible = true;
		colTile->color = Color(1.0f, 1.0f, 1.0f, 1.0f);

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
		colTile->Update();
		walk->Update();
		roll->Update();
	}

	void Player::Render()
	{
		walk->Render();
		roll->Render();
		col->Render();
		colTile->Render();
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
		else
		{
			moveDir.x = 0.0f;
		}

		if (INPUT->KeyPress('S'))
		{
			moveDir.y = -1.0f;
		}
		else if (INPUT->KeyPress('W'))
		{
			moveDir.y = 1.0f;
		}
		else
		{
			moveDir.y = 0.0f;
		}

		moveDir.Normalize();
	}

	void Player::Idle()
	{
		Input();
		LookTarget(INPUT->GetWorldMousePos(), walk);

		//idle -> walk
		if (moveDir != Vector2(0.0f, 0.0f))
		{
			state = PlayerState::WALK;
			walk->ChangeAnim(AnimState::loop, 0.1f);
		}
	}

	void Player::Walk()
	{
		Input();
		LookTarget(INPUT->GetWorldMousePos(), walk);

		col->MoveWorldPos(moveDir * scalar * DELTA);

		//idle -> walk
		if (moveDir == Vector2(0.0f, 0.0f))
		{
			state = PlayerState::IDLE;
			walk->ChangeAnim(AnimState::stop, 0.1f);
			walk->frame.x = 0;
		}

		if (INPUT->KeyDown(VK_SPACE))
		{
			//walk -> roll
			state = PlayerState::ROLL;
			roll->ChangeAnim(AnimState::once, 0.1f);
			roll->isVisible = true;
			walk->isVisible = false;
			timeRoll = 0.0f;
		}
	}

	void Player::Roll()
	{
		LookTarget(moveDir + col->GetWorldPos(), roll);

		timeRoll += DELTA;

		col->MoveWorldPos(moveDir * (scalar + 300.0f) * cos(timeRoll / 0.6f * DIV2PI) * DELTA);

		if (timeRoll > 0.6f)
		{
			state = PlayerState::IDLE;
			walk->ChangeAnim(AnimState::stop, 0.1f);
			roll->isVisible = false;
			walk->isVisible = true;
			walk->frame.x = 0;
		}
	}
	bool Player::IntersectTile(ObTileMap* tilemap)
	{
		auto GetTileState = [&](Vector2 wpos) ->bool
		{
			Int2 on;
			if (tilemap->WorldPosToTileIdx(wpos, on))
			{
				return tilemap->GetTileState(on) == TileState::wall;
			}
			return false;
		};

		Vector2 pos;
		bool flag = false;

		pos = colTile->lt();
		flag |= GetTileState(pos);
		pos = colTile->lb();
		flag |= GetTileState(pos);
		pos = colTile->rt();
		flag |= GetTileState(pos);
		pos = colTile->rb();
		flag |= GetTileState(pos);

		return flag;
	}

	void Player::StepBack()
	{
		col->SetWorldPos(lastPos);
		col->Update();
		colTile->Update();
	}
}