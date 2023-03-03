#pragma once

class ModelRender
{
public:
	ModelRender(Shader* shader);
	~ModelRender();

	void Update();
	void Render();

public:
	void ReadMesh(wstring file);
	void ReadMaterial(wstring file);

	Model* GetModel() { return model; }

	
	Transform* AddTransform();
	Transform* GetTransform(UINT index) { return transforms[index]; }
	void UpdateTransforms();

	void Pass(UINT pass);

	void UpdateTransform(UINT instanceId, UINT boneIndex, Transform& transform);

private:
	void CreateTexture();

private:
	Shader* shader;
	Model* model;

	vector<Transform *> transforms;
	Matrix worlds[MAX_MODEL_INSTANCE];

	VertexBuffer* instanceBuffer;
	

	Matrix boneTransforms[MAX_MODEL_INSTANCE][MAX_MODEL_TRANSFORMS];

	ID3D11Texture2D* texture = NULL;
	ID3D11ShaderResourceView* srv;
};