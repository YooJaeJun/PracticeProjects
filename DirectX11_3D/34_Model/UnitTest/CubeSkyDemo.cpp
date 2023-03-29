#include "stdafx.h"
#include "CubeSkyDemo.h"

void CubeSkyDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(20, 0, 0);
	Context::Get()->GetCamera()->Position(1, 36, -85);


	shader = new Shader(L"25_Mesh.fx");
	sDirection = shader->AsVector("Direction");

	sky = new CubeSky(L"Environment/GrassCube1024.dds");
	
	CreateMesh();

	cubeMapShader = new Shader(L"29_CubeMap.fx");
	cubeMap = new CubeMap(cubeMapShader);
	//cubeMap->Texture(L"Environment/SunsetCube1024.dds");
	cubeMap->Texture(L"Environment/Earth.dds");
	cubeMap->GetTransform()->Position(0, 20, 0);
	cubeMap->GetTransform()->Scale(10, 10, 10);
}

void CubeSkyDemo::Destroy()
{
	SafeDelete(shader);
	SafeDelete(sky);
	
	SafeDelete(cube);
	SafeDelete(grid);

	for (int i = 0; i < 10; i++)
	{
		SafeDelete(cylinder[i]);
		SafeDelete(sphere[i]);
	}

	SafeDelete(cubeMapShader);
	SafeDelete(cubeMap);
}

void CubeSkyDemo::Update()
{
	sky->Update();

	cube->Update();
	grid->Update();

	for (int i = 0; i < 10; i++)
	{
		cylinder[i]->Update();
		sphere[i]->Update();
	}

	cubeMap->Update();
}

void CubeSkyDemo::Render()
{
	ImGui::SliderFloat3("Direction", direction, -1, +1);
	sDirection->SetFloatVector(direction);

	sky->Render();

	cube->Render();
	grid->Render();

	for (int i = 0; i < 10; i++)
	{
		cylinder[i]->Render();
		sphere[i]->Render();
	}

	cubeMap->Render();
}

void CubeSkyDemo::CreateMesh()
{
	cube = new MeshCube(shader);
	cube->GetTransform()->Position(0, 5, 0);
	cube->GetTransform()->Scale(20, 10, 20);
	cube->DiffuseMap(L"Stones.png");

	grid = new MeshGrid(shader, 6, 6);
	grid->GetTransform()->Scale(12, 1, 12);
	grid->DiffuseMap(L"Floor.png");


	for (UINT i = 0; i < 5; i++)
	{
		cylinder[i * 2] = new MeshCylinder(shader, 0.5f, 3.0f, 20, 20);
		cylinder[i * 2]->GetTransform()->Position(-30, 6, (float)i * 15.0f - 15.0f);
		cylinder[i * 2]->GetTransform()->Scale(5, 5, 5);
		cylinder[i * 2]->DiffuseMap(L"Bricks.png");

		cylinder[i * 2 + 1] = new MeshCylinder(shader, 0.5f, 3.0f, 20, 20);
		cylinder[i * 2 + 1]->GetTransform()->Position(30, 6, (float)i * 15.0f - 15.0f);
		cylinder[i * 2 + 1]->GetTransform()->Scale(5, 5, 5);
		cylinder[i * 2 + 1]->DiffuseMap(L"Bricks.png");


		sphere[i * 2] = new MeshSphere(shader, 0.5f, 20, 20);
		sphere[i * 2]->GetTransform()->Position(-30, 15.5f, (float)i * 15.0f - 15.0f);
		sphere[i * 2]->GetTransform()->Scale(5, 5, 5);
		sphere[i * 2]->DiffuseMap(L"Wall.png");

		sphere[i * 2 + 1] = new MeshSphere(shader, 0.5f, 20, 20);
		sphere[i * 2 + 1]->GetTransform()->Position(30, 15.5f, (float)i * 15.0f - 15.0f);
		sphere[i * 2 + 1]->GetTransform()->Scale(5, 5, 5);
		sphere[i * 2 + 1]->DiffuseMap(L"Wall.png");
	}
}
