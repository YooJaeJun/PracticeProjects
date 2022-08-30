#include "stdafx.h"

void Character::Init(Vector2 pos)
{
    obj->SetWorldPos(pos);
    moveDir = Vector2(0.0f, 0.0f);
	lastPos = Vector2(pos);
    hitTime = 0.0f;
}

void Character::Update()
{
	obj->Update();
    Move();

    if (type == eType::ball)
    {
        float rgb = scalar / 400.0f;
        obj->color = Color(rgb, rgb, rgb);
    }
}

void Character::LateUpdate()
{
}

void Character::Render()
{
	obj->Render();
}

void Character::Release()
{
	delete obj;
}


void Character::Move()
{
    Vector2 velocity;
    float radius = obj->scale.x / 2;
    // 두 플레이어
    if (type == eType::p1)
    {
        if (INPUT->KeyPress(VK_UP))
        {
            if (obj->GetWorldPos().y + radius < 400.0f)
            {
                velocity += UP * scalar * DELTA;
            }
        }
        else if (INPUT->KeyPress(VK_DOWN))
        {
            if (obj->GetWorldPos().y - radius > 0.0f)
            {
                velocity += DOWN * scalar * DELTA;
            }
        }
        if (INPUT->KeyPress(VK_LEFT))
        {
            if (obj->GetWorldPos().x - radius > -200.0f)
            {
                velocity += LEFT * scalar * DELTA;
            }
        }
        else if (INPUT->KeyPress(VK_RIGHT))
        {
            if (obj->GetWorldPos().x + radius < 200.0f)
            {
                velocity += RIGHT * scalar * DELTA;
            }
        }
    }
    else if (type == eType::p2)
    {
        if (INPUT->KeyPress('W'))
        {
            if (obj->GetWorldPos().y + radius < 0.0f)
            {
                velocity += UP * scalar * DELTA;
            }
        }
        else if (INPUT->KeyPress('S'))
        {
            if (obj->GetWorldPos().y - radius > -400.0f)
            {
                velocity += DOWN * scalar * DELTA;
            }
        }
        if (INPUT->KeyPress('A'))
        {
            if (obj->GetWorldPos().x - radius > -200.0f)
            {
                velocity += LEFT * scalar * DELTA;
            }
        }
        else if (INPUT->KeyPress('D'))
        {
            if (obj->GetWorldPos().x + radius < 200.0f)
            {
                velocity += RIGHT * scalar * DELTA;
            }
        }
    }
    // 볼
    else if (type == eType::ball)
    {
        if (state == eState::hit)
        {
            scalar -= 50.0f * DELTA;
            if (scalar <= 0.0f)
            {
                scalar = 0.0f;
                state = eState::idle;
            }
        }
        velocity = moveDir * scalar * DELTA;
    }
    // 골대
    else if (type == eType::post)
    {
        if (state == eState::hit)
        {
            hitTime += 100.0f * DELTA;
            float rand = RANDOM->Float(0.7f, 1.0f);
            obj->color = Color(rand, rand, rand);
            if (hitTime > 30.0f)
            {
                hitTime = 0.0f;
                obj->color = Color(0.5f, 0.5f, 0.5f);
                state = eState::idle;
            }
        }
    }

    obj->MoveWorldPos(velocity);
}

void Character::Bounce(IntersectPos interPos, Character* other, eType type)
{
    state = eState::hit;
    // 플레이어와 충돌
    Vector2 direction;
    if (type == eType::p1 or type == eType::p2)
    {
        scalar += 5000.0f * DELTA;
        if (scalar > 600.0f) scalar = 600.0f;

        direction = obj->GetWorldPos() - other->obj->GetWorldPos();
        direction.Normalize();
        if (interPos == IntersectPos::leftRight)
        {
            SetDirX(direction.x);
            obj->SetWorldPos(lastPos);
        }
        else if (interPos == IntersectPos::topBottom)
        {
            SetDirY(direction.y);
            obj->SetWorldPos(lastPos);
        }
        else if (interPos == IntersectPos::edge)
        {
            SetDir(direction);
            obj->SetWorldPos(lastPos);
        }
        else
        {
            SetDir(direction);
        }
    }
    // 벽과 충돌
    else
    {
        direction = obj->GetWorldPos() - lastPos;
        direction.Normalize();

        if (interPos == IntersectPos::leftRight)
        {
            SetDirX(-direction.x);
            obj->SetWorldPos(lastPos);
        }
        else if (interPos == IntersectPos::topBottom)
        {
            SetDirY(-direction.y);
            obj->SetWorldPos(lastPos);
        }
        else if (interPos == IntersectPos::edge)
        {
            SetDir(-direction);
            obj->SetWorldPos(lastPos);
        }
    }
}

void Character::SetDir(const Vector2 otherDir)
{
    moveDir = otherDir;
}

void Character::SetDirX(const float otherDirX)
{
    moveDir.x = otherDirX;
}

void Character::SetDirY(const float otherDirY)
{
    moveDir.y = otherDirY;
}