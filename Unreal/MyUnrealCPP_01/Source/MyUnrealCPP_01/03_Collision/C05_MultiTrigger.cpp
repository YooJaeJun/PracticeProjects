#include "03_Collision/C05_MultiTrigger.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AC05_MultiTrigger::AC05_MultiTrigger()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Root);

	CreateTextRender();

	Box->bHiddenInGame = false;
	Box->SetRelativeScale3D(FVector(3));
}

void AC05_MultiTrigger::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &AC05_MultiTrigger::OnComponentBeginOverlap);
}

void AC05_MultiTrigger::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckFalse(OnMultiLightOverlap.IsBound());

	int32 index = UKismetMathLibrary::RandomIntegerInRange(0, 2);
	FLinearColor color = FLinearColor::MakeRandomColor();

	OnMultiLightOverlap.Broadcast(index, color);
}
