#include "stdafx.h"
#include "WeatherDemo.h"

void WeatherDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(20, 0, 0);
	Context::Get()->GetCamera()->Position(1, 36, -85);
	((Freedom *)Context::Get()->GetCamera())->Speed(50, 2);


	shader = new Shader(L"82_NormalMapping.fxo");

	sky = new CubeSky(L"Environment/GrassCube1024.dds");
	
	rain = new Rain(Vector3(300, 100, 500), (UINT)1e+4f, L"Environment/Rain.png");
	snow = new Snow(Vector3(300, 100, 500), (UINT)1e+5f, L"Environment/Snow.png");
	
	Billboards();

	Mesh();
	Airplane();
	
	Kachujin();
	KachujinCollider();
	KachujinWeapon();

	PointLighting();
	SpotLighting();
}

void WeatherDemo::Update()
{
	sky->Update();

	cube->Update();
	grid->Update();
	cylinder->Update();
	sphere->Update();

	airplane->Update();
	kachujin->Update();

	Matrix worlds[MAX_MODEL_TRANSFORMS];
	for (UINT i = 0; i < kachujin->GetTransformCount(); i++)
	{
		kachujin->GetAttachTransform(i, worlds);
		weapon->GetTransform(i)->World(weaponInitTransform->World() * worlds[40]);
	}

	weapon->UpdateTransforms();
	weapon->Update();

	billboard->Update();



	UINT WeatherSelected = (UINT)weatherType;

	ImGui::Separator();
	ImGui::InputInt("Weather Type", (int *)&WeatherSelected);
	WeatherSelected %= (UINT)WeatherType::Count;
	weatherType = (WeatherType)WeatherSelected;

	switch (weatherType)
	{
		case WeatherType::Rain: rain->Update(); break;
		case WeatherType::Snow: snow->Update(); break;
	}
}

void WeatherDemo::Render()
{
	sky->Render();

	
	Pass(0, 1, 2);

	wall->Render();
	sphere->Render();

	brick->Render();
	cylinder->Render();

	stone->Render();
	cube->Render();

	floor->Render();
	grid->Render();

	airplane->Render();
	
	kachujin->Render();
	weapon->Render();

	billboard->Render();
	
	switch (weatherType)
	{
	case WeatherType::Rain: rain->Render(); break;
	case WeatherType::Snow: snow->Render(); break;
	}
}

void WeatherDemo::Billboards()
{
	billboard = new Billboard(shader);

	for (UINT i = 0; i < 1200; i++)
	{
		Vector2 scale = Math::RandomVec2(1, 3);
		Vector2 position = Math::RandomVec2(-60, 60);

		billboard->Add(Vector3(position.x, scale.y * 0.5f, position.y), scale, 0);
	}
}

void WeatherDemo::Mesh()
{
	//Create Material
	{
		floor = new Material(shader);
		floor->DiffuseMap("Floor.png");
		floor->Specular(1, 1, 1, 20);
		floor->SpecularMap("Floor_Specular.png");
		floor->NormalMap("Floor_Normal.png");
		
		stone = new Material(shader);
		stone->DiffuseMap("Stones.png");
		stone->Specular(1, 1, 1, 20);
		stone->SpecularMap("Stones_Specular.png");
		stone->Emissive(0.15f, 0.15f, 0.15f, 0.3f);
		stone->NormalMap("Stones_Normal.png");

		
		brick = new Material(shader);
		brick->DiffuseMap("Bricks.png");
		brick->Specular(1, 0.3f, 0.3f, 20);
		brick->SpecularMap("Bricks_Specular.png");
		brick->Emissive(0.15f, 0.15f, 0.15f, 0.3f);
		brick->NormalMap("Bricks_Normal.png");

		wall = new Material(shader);
		wall->DiffuseMap("Wall.png");
		wall->Specular(1, 1, 1, 20);
		wall->SpecularMap("Wall_Specular.png");
		wall->Emissive(0.15f, 0.15f, 0.15f, 0.3f);
		wall->NormalMap("Wall_Normal.png");
	}

	//Create Mesh
	{
		Transform* transform = NULL;

		cube = new MeshRender(shader, new MeshCube());
		transform = cube->AddTransform();
		transform->Position(0, 5, 0);
		transform->Scale(20, 10, 20);

		grid = new MeshRender(shader, new MeshGrid(5, 5));
		transform = grid->AddTransform();
		transform->Position(0, 0, 0);
		transform->Scale(12, 1, 12);

		cylinder = new MeshRender(shader, new MeshCylinder(0.5f, 3.0f, 20, 20));
		sphere = new MeshRender(shader, new MeshSphere(0.5f, 20, 20));
		for (UINT i = 0; i < 5; i++)
		{
			transform = cylinder->AddTransform();
			transform->Position(-30, 6, -15.0f + (float)i * 15.0f);
			transform->Scale(5, 5, 5);

			transform = cylinder->AddTransform();
			transform->Position(30, 6, -15.0f + (float)i * 15.0f);
			transform->Scale(5, 5, 5);


			transform = sphere->AddTransform();
			transform->Position(-30, 15.5f, -15.0f + (float)i * 15.0f);
			transform->Scale(5, 5, 5);

			transform = sphere->AddTransform();
			transform->Position(30, 15.5f, -15.0f + (float)i * 15.0f);
			transform->Scale(5, 5, 5);
		}
	}

	sphere->UpdateTransforms();
	cylinder->UpdateTransforms();
	cube->UpdateTransforms();
	grid->UpdateTransforms();

	meshes.push_back(sphere);
	meshes.push_back(cylinder);
	meshes.push_back(cube);
	meshes.push_back(grid);
}

void WeatherDemo::Airplane()
{
	airplane = new ModelRender(shader);
	airplane->ReadMesh(L"B787/Airplane");
	airplane->ReadMaterial(L"B787/Airplane");

	Transform* transform = airplane->AddTransform();
	transform->Position(2.0f, 9.91f, 2.0f);
	transform->Scale(0.004f, 0.004f, 0.004f);
	airplane->UpdateTransforms();

	models.push_back(airplane);
}

void WeatherDemo::Kachujin()
{
	kachujin = new ModelAnimator(shader);
	kachujin->ReadMesh(L"Kachujin/Mesh");
	kachujin->ReadMaterial(L"Kachujin/Mesh");
	kachujin->ReadClip(L"Kachujin/Sword And Shield Idle");
	kachujin->ReadClip(L"Kachujin/Sword And Shield Walk");
	kachujin->ReadClip(L"Kachujin/Sword And Shield Run");
	kachujin->ReadClip(L"Kachujin/Sword And Shield Slash");
	kachujin->ReadClip(L"Kachujin/Salsa Dancing");


	Transform* transform = NULL;

	transform = kachujin->AddTransform();
	transform->Position(0, 0, -30);
	transform->Scale(0.075f, 0.075f, 0.075f);
	kachujin->PlayTweenMode(0, 0, 1.0f);

	transform = kachujin->AddTransform();
	transform->Position(-15, 0, -30);
	transform->Scale(0.075f, 0.075f, 0.075f);
	kachujin->PlayTweenMode(1, 1, 1.0f);

	transform = kachujin->AddTransform();
	transform->Position(-30, 0, -30);
	transform->Scale(0.075f, 0.075f, 0.075f);
	kachujin->PlayTweenMode(2, 2, 0.75f);

	transform = kachujin->AddTransform();
	transform->Position(15, 0, -30);
	transform->Scale(0.075f, 0.075f, 0.075f);
	kachujin->PlayBlendMode(3, 0, 1, 2);
	kachujin->SetBlendAlpha(3, 1.5f);

	transform = kachujin->AddTransform();
	transform->Position(30, 0, -32.5f);
	transform->Scale(0.075f, 0.075f, 0.075f);
	kachujin->PlayTweenMode(4, 4, 0.75f);

	kachujin->UpdateTransforms();

	animators.push_back(kachujin);
}

void WeatherDemo::KachujinCollider()
{
	UINT count = kachujin->GetTransformCount();
	colliders = new  ColliderObject*[count];

	colliderInitTransforms = new Transform();
	colliderInitTransforms->Position(-2.9f, 1.45f, -50.0f);
	colliderInitTransforms->Scale(5, 5, 75);

	for (UINT i = 0; i < count; i++)
	{
		colliders[i] = new ColliderObject();

		//colliders[i]->Init = new Transform();
		//colliders[i]->Init->Position(0, 0, 0);
		//colliders[i]->Init->Scale(10, 30, 10);

		colliders[i]->Transform = new Transform();
		//colliders[i]->Collider = new Collider(colliders[i]->Transform, colliders[i]->Init);
		colliders[i]->Collider = new Collider(colliders[i]->Transform, colliderInitTransforms);
	}
}

void WeatherDemo::KachujinWeapon()
{
	weapon = new ModelRender(shader);
	weapon->ReadMesh(L"Weapon/Sword");
	weapon->ReadMaterial(L"Weapon/Sword");

	UINT count = kachujin->GetTransformCount();
	for (UINT i = 0; i < count; i++)
		weapon->AddTransform();

	weapon->UpdateTransforms();
	models.push_back(weapon);

	
	weaponInitTransform = new Transform();
	weaponInitTransform->Position(-2.9f, 1.45f, -6.45f);
	weaponInitTransform->Scale(0.5f, 0.5f, 0.75f);
	weaponInitTransform->Rotation(0, 0, 1);
}

void WeatherDemo::PointLighting()
{
	PointLight light;
	light =
	{
		Color(0.0f, 0.0f, 0.0f, 1.0f), //Ambient
		Color(0.0f, 0.0f, 1.0f, 1.0f), //Diffuse
		Color(0.0f, 0.0f, 0.7f, 1.0f), //Specular
		Color(0.0f, 0.0f, 0.7f, 1.0f), //Emissive
		Vector3(-30, 10, -30), 5.0f, 0.9f
	};
	Lighting::Get()->AddPointLight(light);

	light =
	{
		Color(0.0f, 0.0f, 0.0f, 1.0f),
		Color(1.0f, 0.0f, 0.0f, 1.0f),
		Color(0.6f, 0.2f, 0.0f, 1.0f),
		Color(0.6f, 0.3f, 0.0f, 1.0f),
		Vector3(15, 10, -30), 10.0f, 0.3f
	};
	Lighting::Get()->AddPointLight(light);

	light =
	{
		Color(0.0f, 0.0f, 0.0f, 1.0f), //Ambient
		Color(0.0f, 1.0f, 0.0f, 1.0f), //Diffuse
		Color(0.0f, 0.7f, 0.0f, 1.0f), //Specular
		Color(0.0f, 0.7f, 0.0f, 1.0f), //Emissive
		Vector3(-5, 1, -17.5f), 5.0f, 0.9f
	};
	Lighting::Get()->AddPointLight(light);

	light =
	{
		Color(0.0f, 0.0f, 0.0f, 1.0f),
		Color(0.0f, 0.0f, 1.0f, 1.0f),
		Color(0.0f, 0.0f, 0.7f, 1.0f),
		Color(0.0f, 0.0f, 0.7f, 1.0f),
		Vector3(-10, 1, -17.5f), 5.0f, 0.9f
	};
	Lighting::Get()->AddPointLight(light);
}

void WeatherDemo::SpotLighting()
{
	SpotLight light;
	light =
	{
		Color(0.3f, 1.0f, 0.0f, 1.0f),
		Color(0.7f, 1.0f, 0.0f, 1.0f),
		Color(0.3f, 1.0f, 0.0f, 1.0f),
		Color(0.3f, 1.0f, 0.0f, 1.0f),
		Vector3(-15, 20, -30), 25.0f,
		Vector3(0, -1, 0), 30.0f, 0.4f
	};
	Lighting::Get()->AddSpotLight(light);

	light =
	{
		Color(1.0f, 0.2f, 0.9f, 1.0f),
		Color(1.0f, 0.2f, 0.9f, 1.0f),
		Color(1.0f, 0.2f, 0.9f, 1.0f),
		Color(1.0f, 0.2f, 0.9f, 1.0f),
		Vector3(0, 20, -30), 30.0f,
		Vector3(0, -1, 0), 40.0f, 0.55f
	};
	Lighting::Get()->AddSpotLight(light);
}

void WeatherDemo::Pass(UINT mesh, UINT model, UINT anim)
{
	for (MeshRender* temp : meshes)
		temp->Pass(mesh);

	for (ModelRender* temp : models)
		temp->Pass(model);

	for (ModelAnimator* temp : animators)
		temp->Pass(anim);
}