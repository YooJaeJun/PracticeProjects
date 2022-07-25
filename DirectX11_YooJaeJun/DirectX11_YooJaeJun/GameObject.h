#pragma once
class ObLine;	// 전방선언

class GameObject
{
private:
	static ObLine* axis;	// 4 or 8 바이트는 데이터 영역에, 구조체 크기 만큼 바이트는 힙 영역에
	Matrix		S, R, T;

public:
	Vector2		position;
	Vector2		scale;
	float		rotation;
	bool		isAxis;
	Matrix		W, RT;
	Matrix*		p;

public:

	GameObject();
	~GameObject();

	virtual void Update();
	virtual void Render();
	static void CreateStaticMember();
	static void DeleteStaticMember();

	// getter setter
	Vector2 GetRight() const { return Vector2(RT._11, RT._12); }	// x축
	Vector2 GetDown() const { return Vector2(RT._21, RT._22); }		// y축

	Vector2 GetWorldPos() { return Vector2(RT._41, RT._42); }	// 이동
};

