#include "04_Trace/C03_MultiTrace.h"
#include "Global.h"
#include "Components/TextRenderComponent.h"

AC03_MultiTrace::AC03_MultiTrace()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");

	CreateTextRender();
}

void AC03_MultiTrace::BeginPlay()
{
	Super::BeginPlay();
}

void AC03_MultiTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector start = GetActorLocation();
	FVector start1 = FVector(start.X + 50, start.Y, start.Z);
	FVector start2 = FVector(start.X - 50, start.Y, start.Z);

	FVector end1 = start1 + GetActorForwardVector() * 600;
	FVector end2 = start2 + GetActorForwardVector() * 600;

	TArray<AActor*> ignores;
	TArray<FHitResult> hitResults1;
	TArray<FHitResult> hitResults2;

	// Channel
	UKismetSystemLibrary::LineTraceMulti(GetWorld(), start1, end1, ETraceTypeQuery::TraceTypeQuery1, 
		false, ignores, EDrawDebugTrace::ForOneFrame, hitResults1, true);

	// Objects
	TArray<TEnumAsByte<EObjectTypeQuery>> types;
	types.Add(EObjectTypeQuery::ObjectTypeQuery1);

	UKismetSystemLibrary::LineTraceMultiForObjects(GetWorld(), start2, end2, types,
		false, ignores, EDrawDebugTrace::ForOneFrame, hitResults2, true);

	TotalTime += DeltaTime;
	if (TotalTime >= 2.0f)
	{
		TotalTime = 0.0f;

		CLog::Log(FString::Printf(L"-- Channel : %d", hitResults1.Num()));
		for (const FHitResult& hitResult : hitResults1)
		{
			FString str = FString::Printf(L"Block : %d, %s", hitResult.bBlockingHit, *hitResult.GetActor()->GetName());
			CLog::Log(str);
		}

		//CLog::Log(FString::Printf(L"-- Channel : %d", hitResults1.Num()));
		//for (const FHitResult& hitResult : hitResults1)
		//	CLog::Log(hitResult.GetActor()->GetName());

		CLog::Log(FString::Printf(L"-- Objects : %d", hitResults2.Num()));
		for (const FHitResult& hitResult : hitResults2)
			CLog::Log(hitResult.GetActor()->GetName());
	}
}

