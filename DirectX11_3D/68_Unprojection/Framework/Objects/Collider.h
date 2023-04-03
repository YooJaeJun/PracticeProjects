#pragma once

struct ColliderObject
{
	class Transform* Init = NULL;
	class Transform* Transform = NULL;
	class Collider* Collider = NULL;
};

class Collider
{
public:
	Collider(Transform* transform, Transform* init = NULL);
	~Collider();

	void Update();
	void Render(Color color = Color(0, 1, 0, 1));

	Transform* GetTransform() { return transform; }

private:
	Transform* init = NULL;
	Transform* transform;

	Vector3 lines[8];
};