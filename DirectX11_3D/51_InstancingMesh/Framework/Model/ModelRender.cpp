#include "Framework.h"
#include "ModelRender.h"

ModelRender::ModelRender(Shader * shader)
	: shader(shader)
{
	model = new Model();
	transform = new Transform(shader);
}

ModelRender::~ModelRender()
{
	SafeDelete(model);
	SafeDelete(transform);
}

void ModelRender::Update()
{
	if (bRead == true)
	{
		bRead = false;

		for (ModelMesh* mesh : model->Meshes())
			mesh->SetShader(shader);

		UpdateTransform();
	}

	for (ModelMesh* mesh : model->Meshes())
		mesh->Update();
}

void ModelRender::Render()
{
	for (ModelMesh* mesh : model->Meshes())
	{
		mesh->SetTransform(transform);
		mesh->Render();
	}
}

void ModelRender::ReadMesh(wstring file)
{
	model->ReadMesh(file);
}

void ModelRender::ReadMaterial(wstring file)
{
	model->ReadMaterial(file);

	bRead = true;
}

void ModelRender::Pass(UINT pass)
{
	for (ModelMesh* mesh : model->Meshes())
		mesh->Pass(pass);
}

void ModelRender::UpdateTransform(ModelBone * bone, Matrix & matrix)
{
	if (bone != NULL)
		UpdateBones(bone, matrix);

	for (UINT i = 0; i < model->BoneCount(); i++)
	{
		ModelBone* bone = model->BoneByIndex(i);
		transforms[i] = bone->Transform();
	}

	for (ModelMesh* mesh : model->Meshes())
		mesh->Transforms(transforms);
}

void ModelRender::UpdateBones(ModelBone * bone, Matrix & matrix)
{
	Matrix temp = bone->Transform();
	bone->Transform(temp * matrix);

	for (ModelBone* child : bone->Childs())
		UpdateBones(child, matrix);
}

