#include "03_Collision/C06_EventTrigger.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AC06_EventTrigger::AC06_EventTrigger()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Root);

	CreateTextRender();

	Box->SetRelativeScale3D(FVector(3));
	Box->bHiddenInGame = false;
}

void AC06_EventTrigger::BeginPlay()
{
	Super::BeginPlay();

	Box->OnComponentBeginOverlap.AddDynamic(this, &AC06_EventTrigger::OnComponentBeginOverlap);
}

void AC06_EventTrigger::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckFalse(OnExplosionEvent.IsBound());

	int32 index = UKismetMathLibrary::RandomIntegerInRange(0, 2);

	OnExplosionEvent.Broadcast(index);
}

