#include "stdafx.h"

Sonic::Sonic()
{
	Init();
}

void Sonic::Init()
{
	Character::Init();
	hp = 5;

	col = new ObRect();
	col->scale = Vector2(192.0f / 4.0f, 60.0f) * 2.0f;
	col->pivot = OFFSET_B;
	col->isFilled = false;
	col->SetWorldPosX(-500.0f);
	col->SetWorldPosY(-app.GetHalfHeight() + 48.0f * 2.5f);

	run = new ObImage(L"run.bmp");
	run->pivot = OFFSET_B;
	run->scale = Vector2(192.0f / 4.0f, 60.0f) * 2.0f;
	run->uv = Vector4(0.0f, 0.0f, 1.0f / 4.0f, 1.0f);
	run->maxFrame.x = 4;
	run->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	run->SetParentRT(*col);

	spin = new ObImage(L"spin.bmp");
	spin->pivot = OFFSET_B;
	spin->scale = Vector2(240.0f / 5.0f, 48.0f) * 2.0f;
	spin->uv = Vector4(0.0f, 0.0f, 1.0f / 5.0f, 1.0f);
	spin->isVisible = false;
	spin->maxFrame.x = 5;
	spin->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
	spin->SetParentRT(*col);

	state = State::RUN;
	gravity = 0.0f;
	doubleJump = false;

	timerHit = 0.0f;
}

void Sonic::Release()
{
	Character::Release();
	SafeDelete(run);
	SafeDelete(spin);
}

void Sonic::Update()
{
	ImGui::SliderInt("Hp", &hp, 1, 5);
	if (hp <= 0)
	{
		hp = 0;
		ImGui::Text("You died, but the test must go on.");
	}

	if (col->GetWorldPos().y + col->scale.y < -app.GetHalfHeight())
	{
		hp -= 2;
		hit = true;
		col->SetWorldPosY(-app.GetHalfHeight() + 48.0f * 2.5f);
		col->Update();
	}

	if (hit)
	{
		run->color = Color(0.5f, 0.5f, 0.5f, RANDOM->Float());
		spin->color = Color(0.5f, 0.5f, 0.5f, RANDOM->Float());
		col->SetWorldPosX(col->GetWorldPos().x + RANDOM->Float(-1.0f, 1.0f));
		col->SetWorldPosY(col->GetWorldPos().y + RANDOM->Float(-1.0f, 1.0f));

		// 중력 안 받게
		if (col->GetWorldPos().y < -app.GetHalfHeight() + 48.0f * 2.5f)
		{
			col->SetWorldPosY(-app.GetHalfHeight() + 48.0f * 2.5f);
			gravity = 0.0f;
		}

		if (TIMER->GetTick(timerHit, 2.5f))
		{
			run->color = Color(0.5f, 0.5f, 0.5f, 1.0f);
			spin->color = Color(0.5f, 0.5f, 0.5f, 1.0f);
			timerHit = 0.0f;
			hit = false;
		}
	}

	col->MoveWorldPos(RIGHT * 200.0f * DELTA);
	CAM->position += RIGHT * 200.0f * DELTA;

	if (state == State::RUN)
	{
		//run -> spin
		if (INPUT->KeyDown(VK_DOWN))
		{
			state = State::SPIN;
			col->scale = spin->scale;
			run->isVisible = false;
			spin->isVisible = true;
			spin->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
		}

		//run -> jump
		if (INPUT->KeyDown(VK_SPACE))
		{
			state = State::JUMP;

			gravity = -700.0f;
			col->scale = spin->scale;
			run->isVisible = false;
			spin->isVisible = true;
			doubleJump = false;
			spin->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
		}
	}
	else if (state == State::SPIN)
	{
		//spin -> run
		if (INPUT->KeyUp(VK_DOWN))
		{
			state = State::RUN;
			col->scale = run->scale;
			run->isVisible = true;
			spin->isVisible = false;
		}
	}
	else if (state == State::JUMP)
	{
		if (INPUT->KeyDown(VK_SPACE) && !doubleJump)
		{
			doubleJump = true;
			gravity = -700.0f;
		}
	}

	col->MoveWorldPos(DOWN * gravity * DELTA);
	gravity += 700.0f * DELTA;

	col->Update();
	run->Update();
	spin->Update();
}

void Sonic::LateUpdate()
{
}

void Sonic::Render()
{
	col->Render();
	run->Render();
	spin->Render();
}

void Sonic::LandOn()
{
	col->SetWorldPosY(-app.GetHalfHeight() + 48.0f * 2.5f);
	gravity = 0.0f;

	//jump -> run
	if (state == State::JUMP)
	{
		state = State::RUN;
		col->scale = run->scale;
		run->isVisible = true;
		spin->isVisible = false;
	}

	col->Update();
	run->Update();
	spin->Update();
}

void Sonic::Hit()
{
	if (false == hit)
	{
		hp--;
		hit = true;
	}
}
