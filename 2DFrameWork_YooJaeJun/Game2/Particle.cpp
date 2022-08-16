#include "stdafx.h"

Particle::Particle()
{
	Init(0);
}

void Particle::Init(const int idx)
{
	Unit::Init();

	hitbox = make_shared<ObStarPointed>();
	hitbox->SetWorldPos(Vector2(2000.0f, 2000.0f));
	hitbox->rotation = 36.0f * idx * ToRadian;
	hitbox->scale = Vector2(15.0f, 15.0f);
	hitbox->isVisible = false;
	hitbox->isFilled = true;
	hitbox->color = Color(RANDOM->Float(0.5f, 0.9f), RANDOM->Float(0.4f, 0.8f), RANDOM->Float(0.4f, 0.6f));

	state == (int)estate::die;

	spawnTime = 0.0f;
	randVec = Vector2(0.0f, 0.0f);
}

void Particle::Update()
{
	Unit::Update();

	if (state == (int)estate::hit)
	{
		spawnTime += 100.0f * DELTA;
		velocity = hitbox->GetRight() + DOWN * gravity + randVec;
		hitbox->MoveWorldPos(velocity);

		if (spawnTime > 80.0f)
		{
			state = (int)estate::die;
			spawnTime = 0.0f;
			hitbox->isVisible = false;
			hitbox->SetWorldPos(Vector2(2000.0f, 2000.0f));
		}
	}
	hitbox->Update();
}

void Particle::Render()
{
	Unit::Render();
	hitbox->Render();
}

void Particle::Spawn(const Vector2& pos)
{
	state = (int)estate::hit;
	hitbox->isVisible = true;
	hitbox->SetWorldPos(pos);
	hitbox->rotation = RANDOM->Float(0.0f, 359.0f) * ToRadian;
	randVec = Vector2(RANDOM->Float(-200.0f, 200.0f), RANDOM->Float(300.0f, 1200.0f)) * DELTA;
	gravity = 600 * DELTA;
}