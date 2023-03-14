#include "03_Collision/C04_Trigger.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AC04_Trigger::AC04_Trigger()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Root);

	CreateTextRender();

	Box->bHiddenInGame = false;
	Box->SetRelativeScale3D(FVector(3));
}

void AC04_Trigger::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &AC04_Trigger::OnComponentBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &AC04_Trigger::OnComponentEndOverlap);
}

void AC04_Trigger::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OnBoxLightBeginOverlap.IsBound())
		OnBoxLightBeginOverlap.Execute();

	if (OnBoxLightColorOverlap.IsBound())
	{
		FString str = OnBoxLightColorOverlap.Execute(FLinearColor::MakeRandomColor());

		CLog::Print(str);
	}
}

void AC04_Trigger::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OnBoxLightEndOverlap.IsBound())
		OnBoxLightEndOverlap.Execute();
}