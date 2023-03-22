#include "stdafx.h"
#include "NormalVectorDemo.h"

void NormalVectorDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(12, 0, 0);
	Context::Get()->GetCamera()->Position(35, 10, -55);

	shader = new Shader(L"19_Terrain.fx");
	
	//terrain = new Terrain(shader, L"Terrain/Grayscale.png");
	terrain = new Terrain(shader, L"Terrain/Gray256.png");
	terrain->Pass(0);
}

void NormalVectorDemo::Destroy()
{
	SafeDelete(shader);

	SafeDelete(terrain);
}

void NormalVectorDemo::Update()
{
	terrain->Update();
}

void NormalVectorDemo::Render()
{
	terrain->Render();

	//DebugLine::Get()->RenderLine(0, 0, 0, 0, 100, 0, 1, 0, 0);
	//DebugLine::Get()->RenderLine(1, 0, 0, 5, 10, 0, 0, 1, 0);
}
