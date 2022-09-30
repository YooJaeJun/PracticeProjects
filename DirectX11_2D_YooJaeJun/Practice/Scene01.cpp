#include "stdafx.h"

namespace Dir8
{
	Scene01::Scene01()
	{
		pl = new Player();
		boss = new Boss();
	}

	Scene01::~Scene01()
	{
	}

	void Scene01::Init()
	{
	}

	void Scene01::Release()
	{
		pl->Release();
		boss->Release();
	}

	void Scene01::Update()
	{
		boss->targetPos = pl->col->GetWorldPos();

		pl->Update();
		boss->Update();
	}

	void Scene01::LateUpdate()
	{
	}

	void Scene01::Render()
	{
		pl->Render();
		boss->Render();
	}

	void Scene01::ResizeScreen()
	{
	}
}