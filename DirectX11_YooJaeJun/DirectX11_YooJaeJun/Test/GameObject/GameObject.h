#pragma once

class GameObject
{
public:
	Vector2 position;
	Vector2 scale;
	float	rotation;

	GameObject();
	~GameObject();

	virtual void Render(HDC hdc);	// 재정의가 예정

};

