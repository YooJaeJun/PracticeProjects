#include "stdafx.h"
#include "MeshDemo.h"

void MeshDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(0, 0, 0);
	Context::Get()->GetCamera()->Position(0, 0, -10);

	shader = new Shader(L"25_Mesh.fx");
	sDirection = shader->AsVector("Direction");

	quad = new MeshQuad(shader);
	quad->Scale(2, 2, 2);
	quad->DiffuseMap(L"Box.png");
}

void MeshDemo::Destroy()
{
	SafeDelete(shader);
	SafeDelete(quad);
}

void MeshDemo::Update()
{
	Vector3 scale;
	quad->Scale(&scale);

	ImGui::SliderFloat2("Scale", scale, -3, 3);
	quad->Scale(scale);

	quad->Update();
}

void MeshDemo::Render()
{
	sDirection->SetFloatVector(direction);

	quad->Render();
}