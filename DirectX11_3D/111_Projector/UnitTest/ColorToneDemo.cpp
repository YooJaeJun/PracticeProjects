#include "stdafx.h"
#include "ColorToneDemo.h"

void ColorToneDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(20, 0, 0);
	Context::Get()->GetCamera()->Position(1, 36, -85);
	((Freedom *)Context::Get()->GetCamera())->Speed(50, 2);


	shader = new Shader(L"96_Billboard.fxo");


	float width = D3D::Width(), height = D3D::Height();
	width = height = 4096;

	renderTarget = new RenderTarget((UINT)width, (UINT)height);
	depthStencil = new DepthStencil((UINT)width, (UINT)height);
	viewport = new Viewport(width, height);

	
	render2D = new Render2D();
	render2D->GetTransform()->Scale(355, 200, 1);
	render2D->GetTransform()->Position(200, 120, 0);
	render2D->SRV(renderTarget->SRV());

	postEffect = new PostEffect(L"100_ColorTone.fxo");
	postEffect->SRV(renderTarget->SRV());


	sky = new CubeSky(L"Environment/GrassCube1024.dds");
	
	Billboards();

	Mesh();
	Airplane();
	
	Kachujin();
	KachujinCollider();
	KachujinWeapon();

	PointLighting();
	SpotLighting();
}

void ColorToneDemo::Update()
{
	static UINT Pass = postEffect->GetShader()->PassCount() - 1;
	ImGui::InputInt("ColorTone Pass", (int *)&Pass);
	Pass %= postEffect->GetShader()->PassCount();
	postEffect->Pass(Pass);


	Vector2 PixelSize = Vector2(1.0f / D3D::Width(), 1.0f / D3D::Height());
	postEffect->GetShader()->AsVector("PixelSize")->SetFloatVector(PixelSize);


	//Saturation
	{
		ImGui::Separator();

		static float Saturation = 0.0f;
		ImGui::InputFloat("Saturation", &Saturation, 0.1f);
		postEffect->GetShader()->AsScalar("Saturation")->SetFloat(Saturation);
	}

	//Sharpness
	{
		ImGui::Separator();

		static float Sharpness = 0.0f;
		ImGui::InputFloat("Sharpness", &Sharpness, 0.1f);
		postEffect->GetShader()->AsScalar("Sharpness")->SetFloat(Sharpness);
	}

	//Vignette
	{
		ImGui::Separator();

		static float Power = 1.0f;
		ImGui::InputFloat("Power", &Power, 0.1f);
		postEffect->GetShader()->AsScalar("Power")->SetFloat(Power);

		static float ScaleX = 1.0f;
		ImGui::InputFloat("ScaleX", &ScaleX, 0.1f);

		static float ScaleY = 1.0f;
		ImGui::InputFloat("ScaleY", &ScaleY, 0.1f);
		postEffect->GetShader()->AsVector("Scale")->SetFloatVector(Vector2(ScaleX, ScaleY));
	}

	//LensDistortion
	{
		ImGui::Separator();

		static float LensPower = 1.0f;
		ImGui::InputFloat("LensPower", &LensPower, 0.01f);
		postEffect->GetShader()->AsScalar("LensPower")->SetFloat(LensPower);

		static Vector3 Distortion = Vector3(-0.02f, -0.02f, -0.02f);
		ImGui::InputFloat("DistortionX", &Distortion.x, 0.001f);
		ImGui::InputFloat("DistortionY", &Distortion.y, 0.001f);
		ImGui::InputFloat("DistortionZ", &Distortion.z, 0.001f);
		postEffect->GetShader()->AsVector("Distortion")->SetFloatVector(Distortion);
	}

	//Interace
	{
		ImGui::Separator();

		static float Strength = 1.0f;
		ImGui::InputFloat("Strength", &Strength, 0.01f);
		postEffect->GetShader()->AsScalar("Strength")->SetFloat(Strength);

		static int InteraceValue = 2;
		ImGui::InputInt("InteraceValue", &InteraceValue);
		postEffect->GetShader()->AsScalar("interaceValue")->SetInt(InteraceValue);
	}

	//Down Scale
	{
		ImGui::Separator();

		static float ScaleX = D3D::Width();
		ImGui::InputFloat("DownScaleX", &ScaleX, 1.0f);

		static float ScaleY = D3D::Height();
		ImGui::InputFloat("DownScaleY", &ScaleY, 1.0f);
		postEffect->GetShader()->AsVector("ScaleSourceSize")->SetFloatVector(Vector2(ScaleX, ScaleY));
	}

	//Wiggle
	{
		ImGui::Separator();

		static float OffsetX = 10;
		ImGui::InputFloat("OffsetX", &OffsetX, 0.1f);

		static float OffsetY = 10;
		ImGui::InputFloat("OffsetY", &OffsetY, 0.1f);
		postEffect->GetShader()->AsVector("WiggleOffset")->SetFloatVector(Vector2(OffsetX, OffsetY));

		static float AmountX = 0.01f;
		ImGui::InputFloat("AmountX", &AmountX, 0.001f);

		static float AmountY = 0.01f;
		ImGui::InputFloat("AmountY", &AmountY, 0.001f);
		postEffect->GetShader()->AsVector("WiggleAmount")->SetFloatVector(Vector2(AmountX, AmountY));
	}


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

	render2D->Update();
	postEffect->Update();
}

void ColorToneDemo::PreRender()
{
	renderTarget->PreRender(depthStencil);
	viewport->RSSetViewport();


	//Render
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
	}
}

void ColorToneDemo::Render()
{
	
}

void ColorToneDemo::PostRender()
{
	postEffect->Render();


	render2D->Render();
}

void ColorToneDemo::Billboards()
{
	billboard = new Billboard(shader);
	//billboard->Pass(3);
	billboard->Pass(4);
	
	billboard->AddTexture(L"Terrain/grass_14.tga");
	billboard->AddTexture(L"Terrain/grass_07.tga");
	billboard->AddTexture(L"Terrain/grass_11.tga");

	for (UINT i = 0; i < 1200; i++)
	{
		Vector2 scale = Math::RandomVec2(1, 3);
		Vector2 position = Math::RandomVec2(-60, 60);

		billboard->Add(Vector3(position.x, scale.y * 0.5f, position.y), scale, 0);
	}

	for (UINT i = 0; i < 300; i++)
	{
		Vector2 scale = Math::RandomVec2(1, 3);
		Vector2 position = Math::RandomVec2(-60, 60);

		billboard->Add(Vector3(position.x, scale.y * 0.5f, position.y), scale, 1);
	}

	for (UINT i = 0; i < 700; i++)
	{
		Vector2 scale = Math::RandomVec2(1, 3);
		Vector2 position = Math::RandomVec2(-60, 60);

		billboard->Add(Vector3(position.x, scale.y * 0.5f, position.y), scale, 2);
	}
}

void ColorToneDemo::Mesh()
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

void ColorToneDemo::Airplane()
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

void ColorToneDemo::Kachujin()
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

void ColorToneDemo::KachujinCollider()
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

void ColorToneDemo::KachujinWeapon()
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

void ColorToneDemo::PointLighting()
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

void ColorToneDemo::SpotLighting()
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

void ColorToneDemo::Pass(UINT mesh, UINT model, UINT anim)
{
	for (MeshRender* temp : meshes)
		temp->Pass(mesh);

	for (ModelRender* temp : models)
		temp->Pass(model);

	for (ModelAnimator* temp : animators)
		temp->Pass(anim);
}