#include "stdafx.h"
#include "AnimationDemo.h"
#include "Converter.h"

void AnimationDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(20, 0, 0);
	Context::Get()->GetCamera()->Position(1, 36, -85);


	shader = new Shader(L"45_Animation.fx");

	Kachujin();

}

void AnimationDemo::Update()
{
	if (kachujin != NULL) kachujin->Update();
}

void AnimationDemo::Render()
{
	ImGui::SliderFloat3("Direction2", direction, -1, +1);
	shader->AsVector("Direction")->SetFloatVector(direction);

	static int pass = 0;
	ImGui::InputInt("Pass2", &pass);
	pass %= 2;



	if (kachujin != NULL)
	{
		kachujin->Pass(pass);
		kachujin->Render();
	}
}

void AnimationDemo::Kachujin()
{
	kachujin = new ModelAnimator(shader);
	kachujin->ReadMesh(L"Kachujin/Mesh");
	kachujin->ReadMaterial(L"Kachujin/Mesh");
	kachujin->ReadClip(L"Kachujin/Sword And Shield Idle");
	kachujin->ReadClip(L"Kachujin/Sword And Shield Run");
	kachujin->ReadClip(L"Kachujin/Sword And Shield Slash");
	kachujin->ReadClip(L"Kachujin/Salsa Dancing");
	kachujin->GetTransform()->Position(0, 0, -30);
	kachujin->GetTransform()->Scale(0.025f, 0.025f, 0.025f);
}