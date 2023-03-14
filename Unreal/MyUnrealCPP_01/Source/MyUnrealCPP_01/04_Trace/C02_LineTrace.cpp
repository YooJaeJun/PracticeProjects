#include "04_Trace/C02_LineTrace.h"
#include "Global.h"
#include "C02_Cylinder.h"
#include "GameFramework/Character.h"

AC02_LineTrace::AC02_LineTrace()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AC02_LineTrace::BeginPlay()
{
	Super::BeginPlay();

	CHelpers::FindActors<AC02_Cylinder>(GetWorld(), Cylinders);

	OnLineTraceResult.AddDynamic(this, &AC02_LineTrace::StartLaunch);
}

void AC02_LineTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector start = Cylinders[0]->GetActorLocation();
	FVector end = Cylinders[1]->GetActorLocation();

	// DrawDebugLine
	{
		start.Z -= 20;
		end.Z -= 20;

		DrawDebugLine(GetWorld(), start, end, FColor::Blue);
	}
}

void AC02_LineTrace::StartLaunch(AActor* InActor, FLinearColor InColor)
{
}

