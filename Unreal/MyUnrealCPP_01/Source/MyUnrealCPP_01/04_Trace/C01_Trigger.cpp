#include "04_Trace/C01_Trigger.h"
#include "Global.h"
#include "C01_SphereTrace.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

AC01_Trigger::AC01_Trigger()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Root);

	CreateTextRender();

	Box->SetRelativeScale3D(FVector(3));
	Box->bHiddenInGame = false;
}

void AC01_Trigger::BeginPlay()
{
	Super::BeginPlay();

	AC01_SphereTrace* trace =  CHelpers::FindActor<AC01_SphereTrace>(GetWorld());
	CheckNull(trace);

	OnActorBeginOverlap.AddDynamic(trace, &AC01_SphereTrace::BeginOverlap);
}
