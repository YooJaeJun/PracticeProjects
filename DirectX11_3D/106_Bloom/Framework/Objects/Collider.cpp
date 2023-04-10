#include "Framework.h"
#include "Collider.h"

Collider::Collider(Transform * transform, Transform * init)
	: transform(transform), init(init)
{
	lines[0] = Vector3(-0.5f, -0.5f, -0.5f); //Min
	lines[1] = Vector3(-0.5f, +0.5f, -0.5f);
	lines[2] = Vector3(+0.5f, -0.5f, -0.5f);
	lines[3] = Vector3(+0.5f, +0.5f, -0.5f);
	lines[4] = Vector3(-0.5f, -0.5f, +0.5f);
	lines[5] = Vector3(-0.5f, +0.5f, +0.5f);
	lines[6] = Vector3(+0.5f, -0.5f, +0.5f);
	lines[7] = Vector3(+0.5f, +0.5f, +0.5f); //Max
}

Collider::~Collider()
{

}

void Collider::Update()
{
	Transform temp;
	temp.World(transform->World());

	if (init != NULL)
		temp.World(init->World() * transform->World());

	
	temp.Position(&bounding.Position);

	D3DXVec3Normalize(&bounding.AxisX, &temp.Right());
	D3DXVec3Normalize(&bounding.AxisY, &temp.Up());
	D3DXVec3Normalize(&bounding.AxisZ, &temp.Forward());

	Vector3 scale;
	temp.Scale(&scale);
	bounding.HalfSize = scale * 0.5f;
}

void Collider::Render(Color color)
{
	Transform temp;
	temp.World(transform->World());

	if (init != NULL)
		temp.World(init->World() * transform->World());

	Matrix world = temp.World();


	Vector3 dest[8];
	for (UINT i = 0; i < 8; i++)
		D3DXVec3TransformCoord(&dest[i], &lines[i], &world);

	//Front
	DebugLine::Get()->RenderLine(dest[0], dest[1], color);
	DebugLine::Get()->RenderLine(dest[1], dest[3], color);
	DebugLine::Get()->RenderLine(dest[3], dest[2], color);
	DebugLine::Get()->RenderLine(dest[2], dest[0], color);

	//Backward
	DebugLine::Get()->RenderLine(dest[4], dest[5], color);
	DebugLine::Get()->RenderLine(dest[5], dest[7], color);
	DebugLine::Get()->RenderLine(dest[7], dest[6], color);
	DebugLine::Get()->RenderLine(dest[6], dest[4], color);

	//Side
	DebugLine::Get()->RenderLine(dest[0], dest[4], color);
	DebugLine::Get()->RenderLine(dest[1], dest[5], color);
	DebugLine::Get()->RenderLine(dest[2], dest[6], color);
	DebugLine::Get()->RenderLine(dest[3], dest[7], color);
}

bool Collider::Intersection(Ray & ray, float * outDistance)
{
	*outDistance = 0.0f;

	Vector3 dest[8];

	Transform temp;
	temp.World(transform->World());

	if (init != NULL)
		temp.World(init->World() * transform->World());

	Matrix world = temp.World();

	Vector3 minPosition, maxPosition;
	D3DXVec3TransformCoord(&minPosition, &lines[0], &world);
	D3DXVec3TransformCoord(&maxPosition, &lines[7], &world);

	if (fabsf(ray.Direction.x) == 0.0f) ray.Direction.x = 1e-6f;
	if (fabsf(ray.Direction.y) == 0.0f) ray.Direction.y = 1e-6f;
	if (fabsf(ray.Direction.z) == 0.0f) ray.Direction.z = 1e-6f;


	float minValue = 0.0f, maxValue = FLT_MAX;

	//Check X
	if (fabsf(ray.Direction.x) >= 1e-6f)
	{
		float value = 1.0f / ray.Direction.x;
		float minX = (minPosition.x - ray.Position.x) * value;
		float maxX = (maxPosition.x - ray.Position.x) * value;

		if (minX > maxX)
		{
			float temp = minX;
			minX = maxX;
			maxX = temp;
		}

		minValue = max(minX, minValue);
		maxValue = min(maxX, maxValue);

		if (minValue > maxValue)
			return false;
	}
	else if (ray.Position.x < minPosition.x || ray.Position.x > maxPosition.x)
		return false;

	//Check Y
	if (fabsf(ray.Direction.y) >= 1e-6f)
	{
		float value = 1.0f / ray.Direction.y;
		float minY = (minPosition.y - ray.Position.y) * value;
		float maxY = (maxPosition.y - ray.Position.y) * value;

		if (minY > maxY)
		{
			float temp = minY;
			minY = maxY;
			maxY = temp;
		}

		minValue = max(minY, minValue);
		maxValue = min(maxY, maxValue);

		if (minValue > maxValue)
			return false;
	}
	else if (ray.Position.y < minPosition.y || ray.Position.y > maxPosition.y)
		return false;


	//Check Z
	if (fabsf(ray.Direction.z) >= 1e-6f)
	{
		float value = 1.0f / ray.Direction.z;
		float minZ = (minPosition.z - ray.Position.z) * value;
		float maxZ = (maxPosition.z - ray.Position.z) * value;

		if (minZ > maxZ)
		{
			float temp = minZ;
			minZ = maxZ;
			maxZ = temp;
		}

		minValue = max(minZ, minValue);
		maxValue = min(maxZ, maxValue);

		if (minValue > maxValue)
			return false;
	}
	else if (ray.Position.z < minPosition.z || ray.Position.z > maxPosition.z)
		return false;

	*outDistance = minValue;
	return true;
}

bool Collider::Intersection(Collider * other)
{
	return Collision(this->bounding, other->bounding);
}

bool Collider::SeperatingPlane(Vector3 & position, Vector3 & direction, Bounding & box1, Bounding & box2)
{
	float val = fabsf(D3DXVec3Dot(&position, &direction));

	float val2 = 0.0f;
	val2 += fabsf(D3DXVec3Dot(&(box1.AxisX * box1.HalfSize.x), &direction));
	val2 += fabsf(D3DXVec3Dot(&(box1.AxisY * box1.HalfSize.y), &direction));
	val2 += fabsf(D3DXVec3Dot(&(box1.AxisZ * box1.HalfSize.z), &direction));
	val2 += fabsf(D3DXVec3Dot(&(box2.AxisX * box2.HalfSize.x), &direction));
	val2 += fabsf(D3DXVec3Dot(&(box2.AxisY * box2.HalfSize.y), &direction));
	val2 += fabsf(D3DXVec3Dot(&(box2.AxisZ * box2.HalfSize.z), &direction));

	return val > val2;
}

bool Collider::Collision(Bounding & box1, Bounding & box2)
{
	Vector3 position = box2.Position - box1.Position;

	if (SeperatingPlane(position, box1.AxisX, box1, box2) == true) return false;
	if (SeperatingPlane(position, box1.AxisY, box1, box2) == true) return false;
	if (SeperatingPlane(position, box1.AxisZ, box1, box2) == true) return false;

	if (SeperatingPlane(position, box2.AxisX, box1, box2) == true) return false;
	if (SeperatingPlane(position, box2.AxisY, box1, box2) == true) return false;
	if (SeperatingPlane(position, box2.AxisZ, box1, box2) == true) return false;

	if (SeperatingPlane(position, Cross(box1.AxisX, box2.AxisX), box1, box2) == true) return false;
	if (SeperatingPlane(position, Cross(box1.AxisX, box2.AxisY), box1, box2) == true) return false;
	if (SeperatingPlane(position, Cross(box1.AxisX, box2.AxisZ), box1, box2) == true) return false;

	if (SeperatingPlane(position, Cross(box1.AxisY, box2.AxisX), box1, box2) == true) return false;
	if (SeperatingPlane(position, Cross(box1.AxisY, box2.AxisY), box1, box2) == true) return false;
	if (SeperatingPlane(position, Cross(box1.AxisY, box2.AxisZ), box1, box2) == true) return false;

	if (SeperatingPlane(position, Cross(box1.AxisZ, box2.AxisX), box1, box2) == true) return false;
	if (SeperatingPlane(position, Cross(box1.AxisZ, box2.AxisY), box1, box2) == true) return false;
	if (SeperatingPlane(position, Cross(box1.AxisZ, box2.AxisZ), box1, box2) == true) return false;

	return true;
}

Vector3 Collider::Cross(Vector3 & vec1, Vector3 & vec2)
{
	float x = vec1.y * vec2.z - vec1.z * vec2.y;
	float y = vec1.z * vec2.x - vec1.x * vec2.z;
	float z = vec1.x * vec2.y - vec1.y * vec2.x;

	return Vector3(x, y, z);
}
