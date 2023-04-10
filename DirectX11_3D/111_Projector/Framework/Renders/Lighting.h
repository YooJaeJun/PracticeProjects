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

#define MAX_SPOT_LIGHTS 256
struct SpotLight
{
	Color Ambient;
	Color Diffuse;
	Color Specular;
	Color Emissive;

	Vector3 Position;
	float Range;

	Vector3 Direction;
	float Angle;

	float Intensity;
	float Padding[3];
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

public:
	UINT SpotLightCount() { return spotLightCount; }
	UINT SpotLights(OUT SpotLight* lights);
	void AddSpotLight(SpotLight& light);
	SpotLight& GetSpotLight(UINT index);

private:
	static Lighting* instance;

private:
	UINT pointLightCount = 0;
	PointLight pointLights[MAX_POINT_LIGHTS];

private:
	UINT spotLightCount = 0;
	SpotLight spotLights[MAX_SPOT_LIGHTS];
};