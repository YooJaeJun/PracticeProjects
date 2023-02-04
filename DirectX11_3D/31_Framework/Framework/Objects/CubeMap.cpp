#include "Framework.h"
#include "CubeMap.h"

CubeMap::CubeMap(Shader* shader)
	: shader(shader)
{
	//cube = new MeshCube(shader);
	cube = new MeshSphere(shader, 0.5f);

	sSrv = shader->AsSRV("CubeMap");
}

CubeMap::~CubeMap()
{
	SafeDelete(cube);
	
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
	cube->Update();
}

void CubeMap::Render()
{
	sSrv->SetResource(srv);

	cube->Render();
}

void CubeMap::Position(float x, float y, float z)
{
	cube->Position(x, y, z);
}

void CubeMap::Position(Vector3& vec)
{
	cube->Position(vec);
}

void CubeMap::Position(Vector3* vec)
{
	cube->Position(vec);
}

void CubeMap::Rotation(float x, float y, float z)
{
	cube->Rotation(x, y, z);
}

void CubeMap::Rotation(Vector3& vec)
{
	cube->Rotation(vec);
}

void CubeMap::Rotation(Vector3* vec)
{
	cube->Rotation(vec);
}

void CubeMap::RotationDegree(float x, float y, float z)
{
	cube->RotationDegree(x, y, z);
}

void CubeMap::RotationDegree(Vector3& vec)
{
	cube->RotationDegree(vec);
}

void CubeMap::RotationDegree(Vector3* vec)
{
	cube->RotationDegree(vec);
}

void CubeMap::Scale(float x, float y, float z)
{
	cube->Scale(x, y, z);
}

void CubeMap::Scale(Vector3& vec)
{
	cube->Scale(vec);
}

void CubeMap::Scale(Vector3* vec)
{
	cube->Scale(vec);
}
