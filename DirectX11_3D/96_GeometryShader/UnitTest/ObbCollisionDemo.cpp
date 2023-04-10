#include "stdafx.h"
#include "ObbCollisionDemo.h"

void ObbCollisionDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(20, 0, 0);
	Context::Get()->GetCamera()->Position(1, 36, -85);


	shader = new Shader(L"55_Render.fx");

	sky = new CubeSky(L"Environment/GrassCube1024.dds");

	floor = new Material(shader);
	floor->DiffuseMap("White.png");
	
	grid = new MeshRender(shader, new MeshGrid(5, 5));
	grid->AddTransform();
	
	
	transform[0] = new Transform();
	transform[0]->Position(0.0f, 0.5f, 0.0f);
	transform[0]->Scale(2, 1, 1);
	collider[0] = new Collider(transform[0]);

	transform[1] = new Transform();
	transform[1]->Position(2.0f, 0.5f, 0.0f);	
	collider[1] = new Collider(transform[1]);
}

void ObbCollisionDemo::Update()
{
	sky->Update();
	grid->Update();

	Vector3 position2;
	transform[1]->Position(&position2);

	if (Keyboard::Get()->Press(VK_RIGHT))
		position2.x += 3.0f * Time::Delta();
	else if (Keyboard::Get()->Press(VK_LEFT))
		position2.x -= 3.0f * Time::Delta();

	if (Keyboard::Get()->Press(VK_UP))
		position2.z += 3.0f * Time::Delta();
	else if (Keyboard::Get()->Press(VK_DOWN))
		position2.z -= 3.0f * Time::Delta();

	transform[1]->Position(position2);


	Vector3 rotation = Vector3(0, 0, 0);
	Vector3 rotation2 = Vector3(0, 0, 0);

	transform[0]->RotationDegree(&rotation);
	transform[1]->RotationDegree(&rotation2);

	ImGui::SliderFloat3("Rotation", (float *)rotation, -179, 179);
	ImGui::SliderFloat3("Rotation2", (float *)rotation2, -179, 179);

	transform[0]->RotationDegree(rotation);
	transform[1]->RotationDegree(rotation2);


	collider[0]->Update();
	collider[1]->Update();
}

void ObbCollisionDemo::Render()
{
	sky->Render();

	floor->Render();
	grid->Render();


	bool bCheck = collider[0]->Intersection(collider[1]);

	Color color;
	color = bCheck ? Color(1, 0, 0, 1) : Color(0, 1, 0, 1);

	collider[0]->Render(color);
	collider[1]->Render(color);
}