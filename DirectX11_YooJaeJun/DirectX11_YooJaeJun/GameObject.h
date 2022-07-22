#pragma once
class ObLine;	// 전방선언

class GameObject
{
private:
	static ObLine* axis;	// 4 or 8 바이트는 데이터 영역에, 구조체 크기 만큼 바이트는 힙 영역에

public:
	Vector2		position;
	Vector2		scale;
	float		rotation;
	Matrix		S, R, T, W;
	bool		isAxis;

public:

	GameObject();
	~GameObject();

	virtual void Update();
	virtual void Render();
	static void CreateStaticMember();
	static void DeleteStaticMember();
};

