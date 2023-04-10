#include "stdafx.h"
#include "AnimationDemo.h"
#include "Converter.h"

void AnimationDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(17, 0, 0);
	Context::Get()->GetCamera()->Position(0, 6, -41);


	shader = new Shader(L"53_InstancingAnimation.fx");

	Kachujin();

}

void AnimationDemo::Update()
{
	static UINT instance = 20;
	static UINT clip = 0;
	static float speed = 1.0f;
	static float tweenTime = 1.0f;

	static bool blendMode = false;
	static float alpha = 0.0f;

	ImGui::Checkbox("BlendMode", &blendMode);
	if (blendMode == false)
	{
		ImGui::InputInt("Instance", (int *)&instance);
		ImGui::InputInt("Clip", (int *)&clip);
		clip %= 4;

		ImGui::InputFloat("Speed", &speed, 0.01f);
		ImGui::InputFloat("TweenTime", &tweenTime, 0.01f);

		if (ImGui::Button("Apply"))
			kachujin->PlayTweenMode(instance, clip, speed, tweenTime);
	}
	else
	{
		ImGui::InputInt("Instance", (int *)&instance);
		ImGui::SliderFloat("Alpha", &alpha, 0.0f, 2.0f);

		kachujin->SetBlendAlpha(instance, alpha);

		if (ImGui::Button("Apply"))
			kachujin->PlayBlendMode(instance, 0, 1, 2);
	}

	if (kachujin != NULL)
		kachujin->Update();
}

void AnimationDemo::Render()
{
	if (kachujin != NULL) kachujin->Render();
}

void AnimationDemo::Kachujin()
{
	kachujin = new ModelAnimator(shader);
	kachujin->ReadMesh(L"Kachujin/Mesh");
	kachujin->ReadMaterial(L"Kachujin/Mesh");
	kachujin->ReadClip(L"Kachujin/Sword And Shield Idle");
	kachujin->ReadClip(L"Kachujin/Sword And Shield Walk");
	kachujin->ReadClip(L"Kachujin/Sword And Shield Run");
	kachujin->ReadClip(L"Kachujin/Sword And Shield Slash");
	kachujin->ReadClip(L"Kachujin/Salsa Dancing");
	
	for (float x = -50; x <= 50; x += 2.5f)
	{
		Transform* transform = kachujin->AddTransform();
		transform->Position(x, 0, -5);
		transform->Scale(0.01f, 0.01f, 0.01f);
	}
	kachujin->UpdateTransforms();
	kachujin->Pass(2);
}