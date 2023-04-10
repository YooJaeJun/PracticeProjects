#pragma once

#define MAX_POINT_LIGHTS 256
struct PointLight
{
	Color Ambient;
	Color Diffuse;
	Color Specular;
	Color Emissive;

	Vector3 Position;
	float Range;

	float Intensity;
	Vector3 Padding;
};

class Lighting
{
public:
	static Lighting* Get();
	static void Create();
	static void Delete();

private:
	Lighting();
	~Lighting();

public:
	UINT PointLightCount() { return pointLightCount; }
	UINT PointLights(OUT PointLight* lights);
	void AddPointLight(PointLight& light);
	PointLight& GetPointLight(UINT index);

private:
	static Lighting* instance;

private:
	UINT pointLightCount = 0;
	PointLight pointLights[MAX_POINT_LIGHTS];
};