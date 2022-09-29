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
		pl->Update();
		boss->Update();
	}

	void Scene01::LateUpdate()
	{
		boss->targetDir = pl->col->GetWorldPos() - boss->col->GetWorldPos();
		boss->targetDir.Normalize();

		if (boss->rangeAtk->Intersect(pl->col))
		{
			boss->Atk();
		}
		else if (boss->rangeTrace->Intersect(pl->col))
		{
			boss->Trace();
		}
		else if (boss->rangeLook->Intersect(pl->col))
		{
			boss->LookTarget();
		}
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