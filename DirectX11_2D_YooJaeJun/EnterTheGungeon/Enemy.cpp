#include "stdafx.h"

Enemy::Enemy()
{
	curHp = maxHp = 3;
	scalar = 120.0f;
	timeFire = 0.0f;
	timeHit = 0.0f;
	isHit = false;
	isHitAnim = false;
	timeHitAnim = 0.0f;
	timeSetMoveDir = 0.0f;
	timeSetTargetDir = 0.0f;

	float bulletCoef = 3.0f;
	for (auto& elem : bullet)
	{
		elem = new EnemyBullet;
		elem->col->scale.x = 8.0f * bulletCoef;
		elem->col->scale.y = 8.0f * bulletCoef;
		elem->idle = new ObImage(L"EnterTheGungeon/Enemy_0/Bullet_0.png");
		elem->idle->scale.x = 8.0f * bulletCoef;
		elem->idle->scale.y = 8.0f * bulletCoef;
		elem->idle->SetParentRT(*elem->col);
	}
}

void Enemy::Release()
{
	Unit::Release();
	for (auto& elem : bullet) elem->Release();
}

void Enemy::Update()
{
	Unit::Update();

	switch (state)
	{
	case State::idle:
		Idle();
		break;
	case State::die:
		Die();
		break;
	default:
		break;
	}
}

void Enemy::LateUpdate()
{
}

void Enemy::Render()
{
	for (auto& elem : bullet) elem->Render();
	Unit::Render();
}

void Enemy::Idle()
{
	Unit::Idle();

	targetDir = moveDir = targetPos - Pos();

	moveDir.Normalize();
	SetMoveDir();

	weapon->col->rotation = Utility::DirToRadian(targetPos - weapon->Pos());
	targetDir.Normalize();
	targetRotation = Utility::DirToRadian(targetDir);
	SetTargetDir();

	if (targetDir.x >= 0.0f)
	{
		if (targetDirBefore.x < 0.0f)
		{
			swap(weapon->idle->uv.y, weapon->idle->uv.w);
			weapon->col->SetLocalPosX(18.0f);
			weapon->col->pivot = Vector2(0.4f, 0.25f);
			weapon->idle->pivot = Vector2(0.4f, 0.25f);
		}
	}
	else
	{
		if (targetDirBefore.x >= 0.0f)
		{
			swap(weapon->idle->uv.y, weapon->idle->uv.w);
			weapon->col->SetLocalPosX(-18.0f);
			weapon->col->pivot = Vector2(0.4f, -0.25f);
			weapon->idle->pivot = Vector2(0.4f, -0.25f);
		}
	}

	// col->MoveWorldPos(moveDir * scalar * DELTA);

	if (moveDir.x == 0.0f && moveDir.y == 0.0f)
	{
		idle[curTargetDirState]->isVisible = true;
		for (auto& elem : walk) elem->isVisible = false;
	}
	else
	{
		for (auto& elem : idle) elem->isVisible = false;
		walk[curTargetDirState]->isVisible = true;
	}

	if (TIMER->GetTick(timeFire, 1.0f))
	{
		for (auto& elem : bullet)
		{
			if (elem->isFired) continue;

			elem->Spawn(weapon->firePos->GetWorldPos(), moveDir);
			break;
		}
	}

	if (isHit)
	{
		if (TIMER->GetTick(timeHit, 0.01f))
		{
			isHit = false;
		}
	}

	if (isHitAnim)
	{
		Color c = Color(RANDOM->Float(0.6f, 1.0f), 0.5f, 0.5f, RANDOM->Float(0.2f, 1.0f));
		for (auto& elem : idle) elem->color = c;
		for (auto& elem : walk) elem->color = c;
		hit->color = c;

		SetPosX(Pos().x + RANDOM->Float(-1.0f, 1.0f));
		SetPosY(Pos().y + RANDOM->Float(-1.0f, 1.0f));

		for (auto& elem : idle) elem->isVisible = false;
		hit->isVisible = true;

		if (TIMER->GetTick(timeHitAnim, 0.4f))
		{
			Color c = Color(0.5f, 0.5f, 0.5f, 1.0f);
			for (auto& elem : idle) elem->color = c;
			for (auto& elem : walk) elem->color = c;
			hit->color = c;
			die->color = c;

			hit->isVisible = false;

			isHitAnim = false;
		}
	}
	else
	{
		idle[curTargetDirState]->color.w = 1.0f;
		walk[curTargetDirState]->color.w = 1.0f;
		hit->isVisible = false;
	}

	for (auto& elem : bullet)
	{
		elem->Update();
	}
}

void Enemy::Hit(const int damage)
{
	Unit::Hit(damage);
	if (false == isHit)
	{
		hit->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
	}
}

void Enemy::Killed()
{
	Unit::Killed();

	for (auto& elem : bullet)
	{
		elem->col->colOnOff = false;
		elem->col->isVisible = false;
		elem->idle->colOnOff = false;
		elem->idle->isVisible = false;
	}
}

void Enemy::Die()
{
	Unit::Die();
}

void Enemy::FindPath(ObTileMap* map)
{
	if (TIMER->GetTick(timeFindPath, 2.0f))
	{
		Int2 sour, dest;
		bool isFind;

		isFind = map->WorldPosToTileIdx(Pos(), sour);
		isFind &= map->WorldPosToTileIdx(targetPos, dest);

		if (isFind)
		{
			if (map->PathFinding(sour, dest, way))
			{
				g = 0.0f;
				start = Pos();
				way.pop_back();
				end = way.back()->Pos;
			}
		}
	}

	if (false == way.empty())
	{
		// SetPos(Vector2::Lerp(start, end, g));
		moveDir = way.back()->Pos - Pos();
		col->MoveWorldPos(moveDir * DELTA);

		g += DELTA * 2.0f;

		if (g > 1.0f)
		{
			g = 0.0f;
			start = end;
			way.pop_back();
			if (false == way.empty())
			{
				end = way.back()->Pos;
			}
		}
	}
}
