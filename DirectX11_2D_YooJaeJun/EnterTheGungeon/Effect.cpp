#include "stdafx.h"

namespace Gungeon
{
	Effect::Effect()
	{
		state = State::die;
		timeDie = 0.0f;
		intervalDie = 0.5f;
	}

	void Effect::Release()
	{
		Character::Release();
		SafeDelete(idle);
	}

	void Effect::Update()
	{
		Character::Update();

		switch (state)
		{
		case Gungeon::State::idle:
			Idle();
			break;
		case Gungeon::State::die:
			Die();
			break;
		default:
			break;
		}

		idle->Update();
	}

	void Effect::LateUpdate()
	{
	}

	void Effect::Render()
	{
		Character::Render();
		idle->Render();	// RENDER->push(idle);
	}

	void Effect::Spawn(const Vector2 wpos)
	{
		idle->SetWorldPos(wpos);
		state = State::idle;
		idle->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
		idle->isVisible = true;
	}

	void Effect::Idle()
	{
		if (TIMER->GetTick(timeDie, intervalDie))
		{
			state = State::die;
			idle->ChangeAnim(ANIMSTATE::STOP, 0.1f);
			idle->isVisible = false;
		}
	}

	void Effect::Die()
	{
	}
}