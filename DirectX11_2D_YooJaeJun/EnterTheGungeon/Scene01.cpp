#include "stdafx.h"

Scene01::Scene01()
{
}

Scene01::~Scene01()
{
}

void Scene01::Init()
{
}

void Scene01::Release()
{
}

void Scene01::Update()
{
    if (INPUT->KeyDown('R'))
    {
        mapGen->Release();
        mapGen->Init();
    }

	mapGen->Update();
}

void Scene01::LateUpdate()
{
	mapGen->LateUpdate();
}

void Scene01::Render()
{
	mapGen->Render();
}

void Scene01::ResizeScreen()
{
	mapGen->ResizeScreen();
}