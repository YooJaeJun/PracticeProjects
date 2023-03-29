#pragma once
#include "Systems/IExecute.h"

class TextureLoadDemo : public IExecute
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
	void LoadTexture(wstring file);

private:
	Shader* shader;

	VertexTexture vertices[6];
	ID3D11Buffer* vertexBuffer;

	UINT indices[6] = { 0, 1, 2, 2, 1, 3 };
	ID3D11Buffer* indexBuffer;

	Matrix world;
	//ID3D11ShaderResourceView* srv;
	Texture* texture = NULL;
};