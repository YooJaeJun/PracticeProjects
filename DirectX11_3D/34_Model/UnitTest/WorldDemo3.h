#pragma once
#include "Systems/IExecute.h"

class WorldDemo3 : public IExecute
{
public:
	virtual void Initialize() override;
	virtual void Ready() override {}
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void PreRender() override {}
	virtual void Render() override;
	virtual void PostRender() override {}
	virtual void ResizeScreen() override {}

private:
	void CreateVertex();
	void CreateVertex2();

private:
	Shader* shader;

	Vertex vertices[6];
	ID3D11Buffer* vertexBuffer;

	Vertex vertices2[6];
	ID3D11Buffer* vertexBuffer2;

	Vector3 position = Vector3(0, 0, 0);
	Vector3 scale = Vector3(1, 1, 1);
	Matrix world;

	Vector3 position2 = Vector3(0, 0, 0);
	Vector3 scale2 = Vector3(1, 1, 1);
	Matrix world2;
};