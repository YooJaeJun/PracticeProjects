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

	// LineTrace
	{
		start.Z += 40;
		end.Z += 40;

		TArray<AActor*> ignores;
		ignores.Add(Cylinders[0]);
		ignores.Add(Cylinders[1]);

		FHitResult hitResult;

		UKismetSystemLibrary::LineTraceSingleByProfile(GetWorld(), start, end, "Pawn", false, 
			ignores, EDrawDebugTrace::ForOneFrame, hitResult, true);

		if (hitResult.bBlockingHit)
		{
			if (OnLineTraceResult.IsBound())
				OnLineTraceResult.Broadcast(hitResult.GetActor(), FLinearColor::MakeRandomColor());
		}
	}
}

void AC02_LineTrace::StartLaunch(AActor* InActor, FLinearColor InColor)
{
	ACharacter* character = Cast<ACharacter>(InActor);
	CheckNull(character);

	character->LaunchCharacter(FVector(0, 0, 50), true, false);
}

