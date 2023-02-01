#pragma once
#include "Systems/IExecute.h"

class GetVerticalRaycast : public IExecute
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
	Terrain* terrain;

	Vector3 position = Vector3(0, 0, 0);

	Shader* triShader;
	ID3D11Buffer* vertexBuffer;
};