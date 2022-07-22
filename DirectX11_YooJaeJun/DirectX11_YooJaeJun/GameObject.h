#pragma once
class ObLine;	// ���漱��

class GameObject
{
private:
	static ObLine* axis;	// 4 or 8 ����Ʈ�� ������ ������, ����ü ũ�� ��ŭ ����Ʈ�� �� ������

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

