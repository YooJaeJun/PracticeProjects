#include "stdafx.h"
#include "GetRaycastDemo.h"

void GetRaycastDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(12, 0, 0);
	Context::Get()->GetCamera()->Position(35, 10, -55);
	((Freedom *)Context::Get()->GetCamera())->Speed(20);

	shader = new Shader(L"19_Terrain.fx");
	
	terrain = new Terrain(shader, L"Terrain/Gray256.png");
	terrain->Pass(1);
}

void GetRaycastDemo::Destroy()
{
	SafeDelete(shader);
	SafeDelete(terrain);
}

void GetRaycastDemo::Update()
{
	Vector3 position = terrain->GetRaycastPosition();

	string str = "";
	str += to_string(position.x) + ", ";
	str += to_string(position.y) + ", ";
	str += to_string(position.z) + ", ";

	Gui::Get()->RenderText(Vector2(10, 60), Color(1, 0, 0, 1), str);

	terrain->Update();
}

void GetRaycastDemo::Render()
{
	terrain->Render();
}
