#pragma once

struct Ray
{
	Ray() : Position(0, 0, 0), Direction(0, 0, 0)
	{

	}

	Ray(Vector3& position, Vector3& direction)
		:Position(position), Direction(direction)
	{

	}

	Vector3 Position;
	Vector3 Direction;
};

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

	bool Intersection(Ray& ray, float* outDistance);

private:
	Transform* init = NULL;
	Transform* transform;

	Vector3 lines[8];
};