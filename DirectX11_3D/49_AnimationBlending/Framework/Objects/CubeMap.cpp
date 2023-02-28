#include "Framework.h"
#include "CubeMap.h"

CubeMap::CubeMap(Shader * shader)
	: shader(shader)
{
	//mesh = new MeshCube(shader);
	mesh = new MeshSphere(shader, 0.5f);

	sSrv = shader->AsSRV("CubeMap");
}

CubeMap::~CubeMap()
{
	SafeDelete(mesh);

	SafeRelease(srv);
}

void CubeMap::Texture(wstring file)
{
	SafeRelease(srv);

	file = L"../../_Textures/" + file;
	Check(D3DX11CreateShaderResourceViewFromFile
	(
		D3D::GetDevice(), file.c_str(), NULL, NULL, &srv, NULL
	));
}

void CubeMap::Update()
{
	mesh->Update();
}

void CubeMap::Render()
{
	sSrv->SetResource(srv);

	mesh->Render();
}