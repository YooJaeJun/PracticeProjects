#include "stdafx.h"
#include "Editor.h"
#include "Utilities/Xml.h"

void Editor::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(20, 0, 0);
	Context::Get()->GetCamera()->Position(1, 36, -85);
	((Freedom *)Context::Get()->GetCamera())->Speed(50, 2);


	shader = new Shader(L"82_NormalMapping.fxo");
	sky = new CubeSky(L"Environment/GrassCube1024.dds");

	Mesh();


	UpdateParticleList();
	UpdateTextureList();
}

void Editor::Destroy()
{
	
}

void Editor::Update()
{
	OnGUI();


	sky->Update();

	sphere->Update();
	grid->Update();

	
	Vector3 position;
	sphere->GetTransform(0)->Position(&position);

	if (Keyboard::Get()->Press('L'))
		position.x += 20 * Time::Delta();
	else if (Keyboard::Get()->Press('J'))
		position.x -= 20 * Time::Delta();

	if (Keyboard::Get()->Press('I'))
		position.z += 20 * Time::Delta();
	else if (Keyboard::Get()->Press('K'))
		position.z -= 20 * Time::Delta();

	if (Keyboard::Get()->Press('O'))
		position.y += 20 * Time::Delta();
	else if (Keyboard::Get()->Press('U'))
		position.y -= 20 * Time::Delta();

	sphere->GetTransform(0)->Position(position);
	sphere->UpdateTransforms();

	if (particleSystem != NULL)
	{
		particleSystem->Add(position);
		particleSystem->Update();
	}
}

void Editor::Render()
{
	sky->Render();

	stone->Render();
	sphere->Render();

	floor->Render();
	grid->Render();

	if (particleSystem != NULL)
		particleSystem->Render();
}

void Editor::Mesh()
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


	Transform* transform = NULL;

	grid = new MeshRender(shader, new MeshGrid(5, 5));
	transform = grid->AddTransform();
	transform->Position(0, 0, 0);
	transform->Scale(12, 1, 12);
	grid->UpdateTransforms();

	sphere = new MeshRender(shader, new MeshSphere(0.5f, 20, 20));
	transform = sphere->AddTransform();
	transform->Position(0, 5, 0);
	transform->Scale(5, 5, 5);
	sphere->UpdateTransforms();
}

void Editor::UpdateParticleList()
{
	particleList.clear();
	Path::GetFiles(&particleList, L"../../_Textures/Particles/", L"*.xml", false);

	for (wstring& file : particleList)
		file = Path::GetFileNameWithoutExtension(file);
}

void Editor::UpdateTextureList()
{
	textureList.clear();

	vector<wstring> files;
	Path::GetFiles(&files, L"../../_Textures/Particles/", L"*.*", false);

	for (wstring file : files)
	{
		wstring ext = Path::GetExtension(file);
		transform(ext.begin(), ext.end(), ext.begin(), toupper);

		file = Path::GetFileName(file);
		if (ext == L"PNG" || ext == L"TGA" || ext == L"JPG")
			textureList.push_back(file);
	}
}

void Editor::OnGUI()
{
	float width = D3D::Width();
	float height = D3D::Height();

	bool bOpen = true;
	bOpen = ImGui::Begin("Particle", &bOpen);
	ImGui::SetWindowPos(ImVec2(width - windowWidth, 0));
	ImGui::SetWindowSize(ImVec2(windowWidth, height));
	{
		OnGUI_List();
		OnGUI_Settings();
	}
	ImGui::End();
}

void Editor::OnGUI_List()
{
	if (ImGui::CollapsingHeader("Particle List", ImGuiTreeNodeFlags_DefaultOpen))
	{
		for (UINT i = 0; i < particleList.size(); i++)
		{
			if (ImGui::Button(String::ToString(particleList[i]).c_str(), ImVec2(200, 0)))
			{
				SafeDelete(particleSystem);

				file = particleList[i];
				particleSystem = new ParticleSystem(particleList[i]);

				bLoop = particleSystem->GetData().bLoop;
				maxParticle = particleSystem->GetData().MaxParticles;
			}
		}//for(i)
	}//ImGui::CollapsingHeader
}

void Editor::OnGUI_Settings()
{
	if (particleSystem == NULL) return;

	ImGui::Spacing();

	if (ImGui::CollapsingHeader("Particle Settings", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Separator();

		ImGui::SliderInt("MaxParticles", (int *)&maxParticle, 1, 1000);
		ImGui::Checkbox("Loop", &bLoop);

		if (ImGui::Button("Apply"))
		{
			particleSystem->GetData().bLoop = bLoop;
			particleSystem->GetData().MaxParticles = maxParticle;
			particleSystem->Reset();
		}


		ImGui::Separator();

		const char* types[] = { "Opaque", "Additive", "AlphaBlend" };
		ImGui::Combo("BlendType", (int *)&particleSystem->GetData().Type, types, 3);

		ImGui::SliderFloat("ReadyTime", &particleSystem->GetData().ReadyTime, 0.1f, 10.0f);
		ImGui::SliderFloat("ReadyRandomTime", &particleSystem->GetData().ReadyRandomTime, 0.0f, 100.0f);

		ImGui::SliderFloat("StartVelocity", &particleSystem->GetData().StartVelocity, 0.0f, 10.0f);
		ImGui::SliderFloat("EndVelocity", &particleSystem->GetData().EndVelocity, -100.0f, 100.0f);

		ImGui::SliderFloat("MinHorizontalVelocity", &particleSystem->GetData().MinHorizontalVelocity, -100.0f, 100.0f);
		ImGui::SliderFloat("MaxHorizontalVelocity", &particleSystem->GetData().MaxHorizontalVelocity, -100.0f, 100.0f);

		ImGui::SliderFloat("MinVerticalVelocity", &particleSystem->GetData().MinVerticalVelocity, -100.0f, 100.0f);
		ImGui::SliderFloat("MaxVerticalVelocity", &particleSystem->GetData().MaxVerticalVelocity, -100.0f, 100.0f);

		ImGui::SliderFloat3("Gravity", particleSystem->GetData().Gravity, -100, 100);

		ImGui::SliderFloat("Color Amount", &particleSystem->GetData().ColorAmount, 0.1f, 5.0f);

		ImGui::ColorEdit4("MinColor", particleSystem->GetData().MinColor);
		ImGui::ColorEdit4("MaxColor", particleSystem->GetData().MaxColor);

		ImGui::SliderFloat("MinRotateSpeed", &particleSystem->GetData().MinRotateSpeed, -10, 10);
		ImGui::SliderFloat("MaxRotateSpeed", &particleSystem->GetData().MaxRotateSpeed, -10, 10);

		ImGui::SliderFloat("MinStartSize", &particleSystem->GetData().MinStartSize, 0, 500);
		ImGui::SliderFloat("MaxStartSize", &particleSystem->GetData().MaxStartSize, 0, 500);

		ImGui::SliderFloat("MinEndSize", &particleSystem->GetData().MinEndSize, 0, 500);
		ImGui::SliderFloat("MaxEndSize", &particleSystem->GetData().MaxEndSize, 0, 500);

		ImGui::Spacing();
		OnGUI_Write();


		ImGui::Spacing();
		ImGui::Separator();
		if (ImGui::CollapsingHeader("TextureList", ImGuiTreeNodeFlags_DefaultOpen))
		{
			for (wstring textureFile : textureList)
			{
				if (ImGui::Button(String::ToString(textureFile).c_str(), ImVec2(200, 0)))
				{
					particleSystem->GetData().TextureFile = textureFile;
					particleSystem->SetTexture(L"Particles/" + textureFile);
				}
			}//for(i)
		}
	}
}

void Editor::OnGUI_Write()
{
	ImGui::Separator();

	if (ImGui::Button("WriteParticle"))
	{
		D3DDesc desc = D3D::GetDesc();

		Path::SaveFileDialog
		(
			file, L"Particle file\0*.xml", L"../../_Textures/Particles",
			bind(&Editor::WriteFile, this, placeholders::_1),
			desc.Handle
		);
	}
}

void Editor::WriteFile(wstring file)
{
	Xml::XMLDocument* document = new Xml::XMLDocument();

	Xml::XMLDeclaration* decl = document->NewDeclaration();
	document->LinkEndChild(decl);

	Xml::XMLElement* root = document->NewElement("Particle");
	root->SetAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
	root->SetAttribute("xmlns:xsd", "http://www.w3.org/2001/XMLSchema");
	document->LinkEndChild(root);


	Xml::XMLElement* node = NULL;

	node = document->NewElement("BlendState");
	node->SetText((int)particleSystem->GetData().Type);
	root->LinkEndChild(node);


	string textureFile = String::ToString(particleSystem->GetData().TextureFile);
	String::Replace(&textureFile, "Particles/", "");

	node = document->NewElement("Loop");
	node->SetText(particleSystem->GetData().bLoop);
	root->LinkEndChild(node);

	node = document->NewElement("TextureFile");
	node->SetText(textureFile.c_str());
	root->LinkEndChild(node);


	node = document->NewElement("MaxParticles");
	node->SetText(particleSystem->GetData().MaxParticles);
	root->LinkEndChild(node);


	node = document->NewElement("ReadyTime");
	node->SetText(particleSystem->GetData().ReadyTime);
	root->LinkEndChild(node);

	node = document->NewElement("ReadyRandomTime");
	node->SetText(particleSystem->GetData().ReadyRandomTime);
	root->LinkEndChild(node);

	node = document->NewElement("StartVelocity");
	node->SetText(particleSystem->GetData().StartVelocity);
	root->LinkEndChild(node);

	node = document->NewElement("EndVelocity");
	node->SetText(particleSystem->GetData().EndVelocity);
	root->LinkEndChild(node);


	node = document->NewElement("MinHorizontalVelocity");
	node->SetText(particleSystem->GetData().MinHorizontalVelocity);
	root->LinkEndChild(node);

	node = document->NewElement("MaxHorizontalVelocity");
	node->SetText(particleSystem->GetData().MaxHorizontalVelocity);
	root->LinkEndChild(node);

	node = document->NewElement("MinVerticalVelocity");
	node->SetText(particleSystem->GetData().MinVerticalVelocity);
	root->LinkEndChild(node);

	node = document->NewElement("MaxVerticalVelocity");
	node->SetText(particleSystem->GetData().MaxVerticalVelocity);
	root->LinkEndChild(node);


	node = document->NewElement("Gravity");
	node->SetAttribute("X", particleSystem->GetData().Gravity.x);
	node->SetAttribute("Y", particleSystem->GetData().Gravity.y);
	node->SetAttribute("Z", particleSystem->GetData().Gravity.z);
	root->LinkEndChild(node);

	node = document->NewElement("ColorAmount");
	node->SetText(particleSystem->GetData().ColorAmount);
	root->LinkEndChild(node);

	node = document->NewElement("MinColor");
	node->SetAttribute("R", particleSystem->GetData().MinColor.r);
	node->SetAttribute("G", particleSystem->GetData().MinColor.g);
	node->SetAttribute("B", particleSystem->GetData().MinColor.b);
	node->SetAttribute("A", particleSystem->GetData().MinColor.a);
	root->LinkEndChild(node);

	node = document->NewElement("MaxColor");
	node->SetAttribute("R", particleSystem->GetData().MaxColor.r);
	node->SetAttribute("G", particleSystem->GetData().MaxColor.g);
	node->SetAttribute("B", particleSystem->GetData().MaxColor.b);
	node->SetAttribute("A", particleSystem->GetData().MaxColor.a);
	root->LinkEndChild(node);


	node = document->NewElement("MinRotateSpeed");
	node->SetText(particleSystem->GetData().MinRotateSpeed);
	root->LinkEndChild(node);

	node = document->NewElement("MaxRotateSpeed");
	node->SetText(particleSystem->GetData().MaxRotateSpeed);
	root->LinkEndChild(node);

	node = document->NewElement("MinStartSize");
	node->SetText((int)particleSystem->GetData().MinStartSize);
	root->LinkEndChild(node);

	node = document->NewElement("MaxStartSize");
	node->SetText((int)particleSystem->GetData().MaxStartSize);
	root->LinkEndChild(node);

	node = document->NewElement("MinEndSize");
	node->SetText((int)particleSystem->GetData().MinEndSize);
	root->LinkEndChild(node);

	node = document->NewElement("MaxEndSize");
	node->SetText((int)particleSystem->GetData().MaxEndSize);
	root->LinkEndChild(node);

	wstring folder = Path::GetDirectoryName(file);
	wstring fileName = Path::GetFileNameWithoutExtension(file);

	document->SaveFile(String::ToString(folder + fileName + L".xml").c_str());
	SafeDelete(document);

	UpdateParticleList();
}
