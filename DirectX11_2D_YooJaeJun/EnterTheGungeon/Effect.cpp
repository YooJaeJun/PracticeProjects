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
		state = State::idle;
		idle->SetWorldPos(wpos);
		idle->ChangeAnim(AnimState::once, 0.1f);
		idle->isVisible = true;
	}

	void Effect::Idle()
	{
		if (TIMER->GetTick(timeDie, intervalDie))
		{
			state = State::die;
			idle->isVisible = false;
		}
	}

	void Effect::Die()
	{
	}
}