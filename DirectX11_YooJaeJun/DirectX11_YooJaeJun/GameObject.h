#pragma once
class ObLine;	// ���漱��

class GameObject
{
private:
	static ObLine* axis;	// 4 or 8 ����Ʈ�� ������ ������, ����ü ũ�� ��ŭ ����Ʈ�� �� ������

public:
	static void CreateStaticMember();
	static void DeleteStaticMember();

	// member

private:
	Vector2		position;
	Matrix		S, R, T, R2, RT;
	Matrix*		p;

protected:
	Matrix		W;

public:
	Vector2		scale;
	float		rotation;	// ������
	float		rotation2;	// ������
	bool		isAxis;

	// member function
public:
	GameObject();
	virtual ~GameObject() {}

	virtual void Update();
	virtual void Render();


	// getter setter
public:
	Vector2 GetLocalPos() { return position; }

	Vector2 GetWorldPos()
	{
		if (!p) return position;
		return Vector2(RT._41, RT._42);	// ���忡�� �󸶳� �־������� ���� ��. (800, 600)
	}

	// �̵���ų �� +=
	void MoveLocalPos(Vector2 Velocity) { position += Velocity; }
	void MoveWorldPos(Vector2 Velocity)
	{
		if (!p) position += Velocity;
		else
		{
			Vector2 locVelocity = Vector2::TransformNormal(Velocity, (*p).Invert());
			position += locVelocity;
		}
	}

	void SetLocalPos(Vector2 localPos) { position = localPos; }
	void SetWorldPos(Vector2 worldPos)
	{
		if (!p) position = worldPos;
		else
		{
			Vector2 localPos = Vector2::TransformNormal(worldPos, (*p).Invert());
			position += localPos;
		}
	}

	// �ڽ� ��
	Vector2 GetRight() const { return Vector2(RT._11, RT._12); }	// x��
	Vector2 GetDown() const { return Vector2(RT._21, RT._22); }		// y��

	void SetParentRT(GameObject& src) { p = &src.RT; }
};

