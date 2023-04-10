#pragma once
#include "Systems/IExecute.h"

class CubeSkyDemo : public IExecute
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
	void CreateMesh();

	void Pass(UINT mesh, UINT model, UINT anim);

private:
	Shader* shader;

	CubeSky* sky;

	Material* floor;
	Material* stone;
	Material* brick;
	Material* wall;

	MeshRender* cube;
	MeshRender* cylinder;
	MeshRender* sphere;
	MeshRender* grid;

	vector<MeshRender *> meshes;
	vector<ModelRender *> models;
	vector<ModelAnimator *> animators;
};