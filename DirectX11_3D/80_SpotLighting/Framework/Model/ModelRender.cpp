#include "Framework.h"
#include "ModelRender.h"

ModelRender::ModelRender(Shader * shader)
	: shader(shader)
{
	model = new Model();

	for (UINT i = 0; i < MAX_MODEL_INSTANCE; i++)
		D3DXMatrixIdentity(&worlds[i]);

	instanceBuffer = new VertexBuffer(worlds, MAX_MODEL_INSTANCE, sizeof(Matrix), 1, true);
}

ModelRender::~ModelRender()
{
	SafeDelete(model);
	
	for (Transform* transform : transforms)
		SafeDelete(transform);

	SafeDelete(instanceBuffer);

	SafeRelease(texture);
	SafeRelease(srv);
}

void ModelRender::Update()
{
	if (texture == NULL)
	{
		for (ModelMesh* mesh : model->Meshes())
			mesh->SetShader(shader);

		CreateTexture();
	}

	for (ModelMesh* mesh : model->Meshes())
		mesh->Update();
}

void ModelRender::Render()
{
	instanceBuffer->Render();

	for (ModelMesh* mesh : model->Meshes())
		mesh->Render(transforms.size());
}

void ModelRender::ReadMesh(wstring file)
{
	model->ReadMesh(file);
}

void ModelRender::ReadMaterial(wstring file)
{
	model->ReadMaterial(file);
}

void ModelRender::Pass(UINT pass)
{
	for (ModelMesh* mesh : model->Meshes())
		mesh->Pass(pass);
}

void ModelRender::CreateTexture()
{
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
	desc.Width = MAX_MODEL_TRANSFORMS * 4;
	desc.Height = MAX_MODEL_INSTANCE;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;

	Matrix bones[MAX_MODEL_TRANSFORMS];
	for (UINT i = 0; i < MAX_MODEL_INSTANCE; i++)
	{
		for (UINT b = 0; b < model->BoneCount(); b++)
		{
			ModelBone* bone = model->BoneByIndex(b);

			Matrix parent;
			int parentIndex = bone->ParentIndex();

			if (parentIndex < 0)
				D3DXMatrixIdentity(&parent);
			else
				parent = bones[parentIndex];

			Matrix matrix = bone->Transform();
			bones[b] = parent;
			boneTransforms[i][b] = matrix * bones[b];
		}//for(b)
	}//for(i)

	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem = boneTransforms;
	subResource.SysMemPitch = MAX_MODEL_TRANSFORMS * sizeof(Matrix);
	subResource.SysMemSlicePitch = MAX_MODEL_TRANSFORMS * sizeof(Matrix) * MAX_MODEL_INSTANCE;

	Check(D3D::GetDevice()->CreateTexture2D(&desc, &subResource, &texture));


	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Format = desc.Format;

	Check(D3D::GetDevice()->CreateShaderResourceView(texture, &srvDesc, &srv));


	for (ModelMesh* mesh : model->Meshes())
		mesh->TransformsSRV(srv);
}

Transform * ModelRender::AddTransform()
{
	Transform* transform = new Transform();
	transforms.push_back(transform);

	return transform;
}

void ModelRender::UpdateTransforms()
{
	for (UINT i = 0; i < transforms.size(); i++)
		memcpy(worlds[i], transforms[i]->World(), sizeof(Matrix));

	D3D11_MAPPED_SUBRESOURCE subResource;
	D3D::GetDC()->Map(instanceBuffer->Buffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		memcpy(subResource.pData, worlds, sizeof(Matrix) * MAX_MESH_INSTANCE);
	}
	D3D::GetDC()->Unmap(instanceBuffer->Buffer(), 0);
}

void ModelRender::UpdateTransform(UINT instanceId, UINT boneIndex, Transform& transform)
{
	Matrix destMatrix = transform.World();

	ModelBone* bone = model->BoneByIndex(boneIndex);
	boneTransforms[instanceId][boneIndex] = destMatrix * boneTransforms[instanceId][boneIndex];

	int tempBoneIndex = boneIndex;
	for (ModelBone* child : bone->Childs())
	{
		Matrix parent = boneTransforms[instanceId][boneIndex];

		Matrix invParent;
		D3DXMatrixInverse(&invParent, NULL, &parent);
		tempBoneIndex++;

		Matrix temp = boneTransforms[instanceId][tempBoneIndex] * invParent;
		boneTransforms[instanceId][tempBoneIndex] = temp * destMatrix * parent;
	}

	D3D11_MAPPED_SUBRESOURCE subResource;
	D3D::GetDC()->Map(texture, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		memcpy(subResource.pData, boneTransforms, MAX_MODEL_INSTANCE * MAX_MODEL_TRANSFORMS * sizeof(Matrix));
	}
	D3D::GetDC()->Unmap(texture, 0);
}