#pragma once
#define MAX_MODEL_TRANSFORMS 250

class ModelBone;
class ModelMesh;

class Model
{
public:
	typedef VertexTextureNormalTangentBlend ModelVertex;

public:
	Model();
	~Model();

	UINT BoneCount() { return bones.size(); }
	vector<ModelBone *>& Bones() { return bones; }
	ModelBone* BoneByIndex(UINT index) { return bones[index]; }
	ModelBone* BoneByName(wstring name);

	UINT MeshCount() { return meshes.size(); }
	vector<ModelMesh*>& Meshes() { return meshes; }
	ModelMesh* MeshByIndex(UINT index) { return meshes[index]; }
	ModelMesh* MeshByName(wstring name);

public:
	void ReadMesh(wstring file);

private:
	void BindBone();
	void BindMesh();

private:
	ModelBone* root;
	vector<ModelBone *> bones;
	vector<ModelMesh *> meshes;
};