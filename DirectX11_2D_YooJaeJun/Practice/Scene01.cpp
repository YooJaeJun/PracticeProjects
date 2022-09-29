#include "stdafx.h"

Scene01::Scene01()
{
	pl = new Player();
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
	pl->Update();
}

void Scene01::LateUpdate()
{
}

void Scene01::Render()
{
	pl->Render();
}

void Scene01::ResizeScreen()
{
}
