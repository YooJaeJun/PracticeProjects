#include "stdafx.h"
#include "ModelDemo.h"
#include "Converter.h"

void ModelDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(20, 0, 0);
	Context::Get()->GetCamera()->Position(1, 36, -85);


	shader = new Shader(L"38_Model.fx");

	Airplane();
	Tower();
	Tank();


	sky = new CubeSky(L"Environment/GrassCube1024.dds");

	gridShader = new Shader(L"25_Mesh.fx");
	grid = new MeshGrid(gridShader, 6, 6);
	grid->GetTransform()->Scale(12, 1, 12);
	grid->DiffuseMap(L"Floor.png");

}

void ModelDemo::Update()
{
	sky->Update();
	grid->Update();

	if (airplane != NULL) airplane->Update();
	if (tower != NULL) tower->Update();
	if (tank != NULL)
	{
		ModelBone* bone = tank->GetModel()->BoneByIndex(10);

		Transform transform;
		float rotation = sinf(Time::Get()->Running() + 100) * Math::PI * Time::Delta();
		transform.Rotation(0, rotation, 0);

		tank->UpdateTransform(bone, transform.World());
		tank->Update();
	}
}

void ModelDemo::Render()
{
	ImGui::SliderFloat3("Direction", direction, -1, +1);
	shader->AsVector("Direction")->SetFloatVector(direction);
	gridShader->AsVector("Direction")->SetFloatVector(direction);

	static int pass = 0;
	ImGui::InputInt("Pass", &pass);
	pass %= 2;



	sky->Render();
	grid->Render();

	if (airplane != NULL)
	{
		airplane->Pass(pass);
		airplane->Render();
	}

	if (tower != NULL)
	{
		tower->Pass(pass);
		tower->Render();
	}

	if (tank != NULL)
	{
		tank->Pass(pass);
		tank->Render();
	}
}

void ModelDemo::Airplane()
{
	airplane = new ModelRender(shader);
	airplane->ReadMesh(L"B787/Airplane");
	airplane->ReadMaterial(L"B787/Airplane");
	airplane->GetTransform()->Scale(0.005f, 0.005f, 0.005f);
}

void ModelDemo::Tower()
{
	tower = new ModelRender(shader);
	tower->ReadMesh(L"Tower/Tower");
	tower->ReadMaterial(L"Tower/Tower");
	tower->GetTransform()->Position(-20, 0, 0);
	tower->GetTransform()->Scale(0.01f, 0.01f, 0.01f);
}

void ModelDemo::Tank()
{
	tank = new ModelRender(shader);
	tank->ReadMesh(L"Tank/Tank");
	tank->ReadMaterial(L"Tank/Tank");
	tank->GetTransform()->Position(20, 0, 0);
}