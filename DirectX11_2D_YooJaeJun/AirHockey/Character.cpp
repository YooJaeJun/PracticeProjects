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

    // 볼
    if (type == eType::ball)
    {
        float rgb = scalar / 400.0f;
        obj->color = Color(rgb, rgb, rgb);
    }
    // 볼
    else if (type == eType::ball)
    {
        if (state == eState::hit)
        {
            scalar -= 80.0f * DELTA;
            if (scalar <= 0.0f)
            {
                scalar = 0.0f;
                state = eState::idle;
            }
        }
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
                obj->color = originColor;
                state = eState::idle;
            }
        }
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
            velocity += UP * scalar * DELTA;
        }
        else if (INPUT->KeyPress(VK_DOWN))
        {
            velocity += DOWN * scalar * DELTA;
        }
        if (INPUT->KeyPress(VK_LEFT))
        {
            velocity += LEFT * scalar * DELTA;
        }
        else if (INPUT->KeyPress(VK_RIGHT))
        {
            velocity += RIGHT * scalar * DELTA;
        }
    }
    else if (type == eType::p2)
    {
        if (INPUT->KeyPress('W'))
        {
            velocity += UP * scalar * DELTA;
        }
        else if (INPUT->KeyPress('S'))
        {
            velocity += DOWN * scalar * DELTA;
        }
        if (INPUT->KeyPress('A'))
        {
            velocity += LEFT * scalar * DELTA;
        }
        else if (INPUT->KeyPress('D'))
        {
            velocity += RIGHT * scalar * DELTA;
        }
    }
    // 볼
    else if (type == eType::ball)
    {
        velocity = moveDir * scalar * DELTA;
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
        scalar += 4000.0f * DELTA;
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