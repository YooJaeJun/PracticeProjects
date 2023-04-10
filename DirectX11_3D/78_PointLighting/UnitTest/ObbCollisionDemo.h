#pragma once
#include "Systems/IExecute.h"

class ObbCollisionDemo : public IExecute
{
public:
	virtual void Initialize() override;
	virtual void Ready() override {}
	virtual void Destroy() override {}
	virtual void Update() override;
	virtual void PreRender() override {}
	virtual void Render() override;
	virtual void PostRender() override {}
	virtual void ResizeScreen() override {}

private:
	Shader* shader;

	CubeSky* sky;

	Material* floor;
	MeshRender* grid;

	Transform* transform[2];
	Collider* collider[2];
};