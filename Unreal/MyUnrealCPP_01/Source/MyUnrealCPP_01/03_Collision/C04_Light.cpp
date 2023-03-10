#include "03_Collision/C04_Light.h"
#include "Global.h"
#include "C04_Trigger.h"
#include "Components/PointLightComponent.h"
#include "Components/TextRenderComponent.h"

AC04_Light::AC04_Light()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UPointLightComponent>(this, &PointLight, "PointLight", Root);
	CHelpers::CreateComponent<UPointLightComponent>(this, &PointLight2, "PointLight2", Root);

	CreateTextRender();

	PointLight->SetRelativeLocation(FVector(0, -50, 0));
	PointLight->LightColor = FColor::Red;
	PointLight->Intensity = 1e+4f;	// 1 * 10 ^ 4
	PointLight->AttenuationRadius = 200;

	PointLight2->SetRelativeLocation(FVector(0, +50, 0));
	PointLight2->LightColor = FColor::Red;
	PointLight2->Intensity = 1e+4f;	// 1 * 10 ^ 4
	PointLight2->AttenuationRadius = 200;
}

void AC04_Light::BeginPlay()
{
	Super::BeginPlay();

	OffLight();

	AC04_Trigger* trigger = CHelpers::findActor<AC04_Trigger>(GetWorld());
	CheckNull(trigger);

	trigger->OnBoxLightBeginOverlap.BindUFunction(this, "OnLight");
	trigger->OnBoxLightEndOverlap.BindUFunction(this, "OffLight");
}

void AC04_Light::OnLight()
{
	PointLight->SetVisibility(true);
}

void AC04_Light::OffLight()
{
	PointLight->SetVisibility(false);
	PointLight2->SetVisibility(false);
}
