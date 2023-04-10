#pragma once
#include "Systems/IExecute.h"

class Viewer : public IExecute
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
	void Mesh();

private:
	Shader* shader;
	CubeSky* sky;

	ParticleSystem* particleSystem;

	Material* floor;
	Material* stone;

	MeshRender* sphere;
	MeshRender* grid;
};