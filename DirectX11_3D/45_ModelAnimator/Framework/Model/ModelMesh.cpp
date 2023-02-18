#include "Framework.h"
#include "ModelMesh.h"

ModelBone::ModelBone()
{

}

ModelBone::~ModelBone()
{

}

///////////////////////////////////////////////////////////////////////////////

ModelMesh::ModelMesh()
{
	boneBuffer = new ConstantBuffer(&boneDesc, sizeof(BoneDesc));
}

ModelMesh::~ModelMesh()
{
	SafeDelete(transform);
	SafeDelete(perFrame);

	SafeDelete(material);

	SafeDeleteArray(vertices);
	SafeDeleteArray(indices);

	SafeDelete(vertexBuffer);
	SafeDelete(indexBuffer);

	SafeDelete(boneBuffer);
}

void ModelMesh::Binding(Model * model)
{
	vertexBuffer = new VertexBuffer(vertices, vertexCount, sizeof(Model::ModelVertex));
	indexBuffer = new IndexBuffer(indices, indexCount);

	
	Material* srcMaterial = model->MaterialByName(materialName);

	material = new Material();
	material->CopyFrom(srcMaterial);
}

void ModelMesh::SetShader(Shader * shader)
{
	this->shader = shader;

	SafeDelete(transform);
	transform = new Transform(shader);

	SafeDelete(perFrame);
	perFrame = new PerFrame(shader);

	sBoneBuffer = shader->AsConstantBuffer("CB_Bone");

	material->SetShader(shader);
	
	sTransformsSRV = shader->AsSRV("TransformsMap");
}

void ModelMesh::Update()
{
	boneDesc.Index = boneIndex;

	perFrame->Update();
	transform->Update();
}

void ModelMesh::Render()
{
	boneBuffer->Render();
	sBoneBuffer->SetConstantBuffer(boneBuffer->Buffer());

	perFrame->Render();
	transform->Render();
	material->Render();

	vertexBuffer->Render();
	indexBuffer->Render();

	if (transformsSRV != NULL)
		sTransformsSRV->SetResource(transformsSRV);

	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shader->DrawIndexed(0, pass, indexCount);
}

void ModelMesh::Transforms(Matrix * transforms)
{
	memcpy(boneDesc.Transforms, transforms, sizeof(Matrix) * MAX_MODEL_TRANSFORMS);
}

void ModelMesh::SetTransform(Transform * transform)
{
	this->transform->Set(transform);
}


