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
	Vector2		scale;
	Matrix		S, R, T, R2, RT;
	Matrix*		p;

protected:
	Matrix		W;

public:
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
	void MoveLocalPos(Vector2 velocity) { position += velocity; }
	void MoveWorldPos(Vector2 velocity)
	{
		if (!p) position += velocity;
		else
		{
			//							   ����(w)�� 0 => �ٸ� �������� �̵�
			Vector2 locVelocity = Vector2::TransformNormal(velocity, (*p).Invert());	// �� �ӵ� * ����� SRT * RT * (1 / RT)
			position += locVelocity;
		}
	}

	void SetLocalPos(Vector2 localPos) { position = localPos; }
	void SetWorldPos(Vector2 worldPos)
	{
		if (!p) position = worldPos;
		else
		{
			//							����(w)�� 1
			Vector2 localPos = Vector2::Transform(worldPos, (*p).Invert());
			position += localPos;
		}
	}

	// �ڽ� ��
	Vector2 GetRight() const { return Vector2(RT._11, RT._12); }	// x��
	Vector2 GetDown() const { return Vector2(RT._21, RT._22); }		// y��

	void SetParentRT(GameObject& src) { p = &src.RT; }
	void SetParentRT(shared_ptr<GameObject> src) { p = &src->RT; }

	void SetScale(Vector2 other) { scale.x = other.x; scale.y = other.y; }
};

