#pragma once
#include "Systems/IExecute.h"

class TextureSamplerDemo : public IExecute
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
	Shader* shader;

	VertexTexture vertices[6];
	ID3D11Buffer* vertexBuffer;

	UINT indices[6] = { 0, 1, 2, 2, 1, 3 };
	ID3D11Buffer* indexBuffer;

	Matrix world;
	Texture* texture = NULL;
};