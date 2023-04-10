#pragma once
#include "Systems/IExecute.h"

class DynamicCubeMapDemo : public IExecute
{
public:
	virtual void Initialize() override;
	virtual void Ready() override {}
	virtual void Destroy() override {}
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void ResizeScreen() override {}

private:
	void Billboards();
	void Mesh();
	void Airplane();
	void Kachujin();
	void KachujinCollider();
	void KachujinWeapon();
	void PointLighting();
	void SpotLighting();

	void Pass(UINT mesh, UINT model, UINT anim);

private:
	Shader* shader;

	DynamicCubeMap* cubeMap;

	Billboard* billboard;

	CubeSky* sky;

	Material* floor;
	Material* stone;
	Material* brick;
	Material* wall;

	MeshRender* cube;
	MeshRender* cylinder;
	MeshRender* sphere;
	MeshRender* sphere2;
	MeshRender* grid;

	ModelRender* airplane = NULL;


	ModelAnimator* kachujin = NULL;
	Transform* colliderInitTransforms;
	ColliderObject** colliders;

	ModelRender* weapon = NULL;
	Transform* weaponInitTransform;

	vector<MeshRender *> meshes;
	vector<ModelRender *> models;
	vector<ModelAnimator *> animators;
};