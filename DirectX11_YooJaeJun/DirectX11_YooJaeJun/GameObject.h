#pragma once
class GameObject
{
public:
	Vector2		position;
	Vector2		scale;
	float		rotation;
	Matrix		S, R, T, W;


public:

	GameObject();
	~GameObject();

	virtual void Update();
	virtual void Render();
};

