#include "03_Collision/C05_SpotLight.h"
#include "Global.h"
#include "C05_MultiTrigger.h"
#include "Components/SpotLightComponent.h"
#include "Components/TextRenderComponent.h"

AC05_SpotLight::AC05_SpotLight()
{
    CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");

    for (int32 i = 0; i < 3; i++)
    {
        FString str;
        str.Append("Lights");
        str.Append(FString::FromInt(i + 1));

        CHelpers::CreateComponent<USpotLightComponent>(this, &Lights[i], FName(str), Root);

        Lights[i]->SetRelativeLocation(FVector(0, i * 150, 0));
        Lights[i]->SetRelativeRotation(FRotator(-90, 0, 0));
        Lights[i]->Intensity = 1e+5f;
        Lights[i]->OuterConeAngle = 25;
    }

    CreateTextRender();
}

void AC05_SpotLight::BeginPlay()
{
	Super::BeginPlay();

    AC05_MultiTrigger* trigger = CHelpers::FindActor<AC05_MultiTrigger>(GetWorld());
    CheckNull(trigger);

    trigger->OnMultiLightOverlap.AddUFunction(this, "OnLight");
}

void AC05_SpotLight::OnLight(int32 InIndex, FLinearColor InColor)
{
    for (int32 i = 0; i < 3; i++)
        Lights[i]->SetLightColor(FLinearColor::White);

    Lights[InIndex]->SetLightColor(InColor);
}

