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

	Transform* GetTransform() { return transform; }
	Model* GetModel() { return model; }

	void Pass(UINT pass);

	void UpdateTransform(ModelBone* bone = NULL, Matrix& matrix = Matrix());

private:
	void UpdateBones(ModelBone* bone, Matrix& matrix);

private:
	bool bRead = false;

	Shader* shader;
	Model* model;
	Transform* transform;

	Matrix transforms[MAX_MODEL_TRANSFORMS];
};