#include "stdafx.h"
#include "ModelDemo.h"
#include "Converter.h"

void ModelDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(20, 0, 0);
	Context::Get()->GetCamera()->Position(1, 36, -85);


	shader = new Shader(L"52_InstancingModel.fx");

	Airplane();
	Tower();
	Tank();

}

void ModelDemo::Update()
{
	if (airplane != NULL) airplane->Update();
	if (tower != NULL) tower->Update();
	if (tank != NULL) tank->Update();
}

void ModelDemo::Render()
{
	if (airplane != NULL)
		airplane->Render();

	if (tower != NULL)
		tower->Render();

	if (tank != NULL)
		tank->Render();
}

void ModelDemo::Airplane()
{
	airplane = new ModelRender(shader);
	airplane->ReadMesh(L"B787/Airplane");
	airplane->ReadMaterial(L"B787/Airplane");
	
	for (float x = -50; x <= 50; x += 2.5f)
	{
		Transform* transform = airplane->AddTransform();

		transform->Position(Vector3(x, 0.0f, 2.5f));
		transform->RotationDegree(0, Math::Random(-180.0f, 180.0f), 0);
		transform->Scale(0.00025f, 0.00025f, 0.00025f);
	}
	airplane->UpdateTransforms();
	airplane->Pass(1);
}

void ModelDemo::Tower()
{
	tower = new ModelRender(shader);
	tower->ReadMesh(L"Tower/Tower");
	tower->ReadMaterial(L"Tower/Tower");
	
	for (float x = -50; x <= 50; x += 2.5f)
	{
		Transform* transform = tower->AddTransform();

		transform->Position(Vector3(x, 0.0f, 7.5f));
		transform->RotationDegree(0, Math::Random(-180.0f, 180.0f), 0);
		transform->Scale(0.003f, 0.003f, 0.003f);
	}
	tower->UpdateTransforms();
	tower->Pass(1);
}

void ModelDemo::Tank()
{
	tank = new ModelRender(shader);
	tank->ReadMesh(L"Tank/Tank");
	tank->ReadMaterial(L"Tank/Tank");
	
	for (float x = -50; x <= 50; x += 2.5f)
	{
		Transform* transform = tank->AddTransform();

		transform->Position(Vector3(x, 0.0f, 5.0f));
		transform->RotationDegree(0, Math::Random(-180.0f, 180.0f), 0);
		transform->Scale(0.1f, 0.1f, 0.1f);
	}
	tank->UpdateTransforms();
	tank->Pass(1);
}