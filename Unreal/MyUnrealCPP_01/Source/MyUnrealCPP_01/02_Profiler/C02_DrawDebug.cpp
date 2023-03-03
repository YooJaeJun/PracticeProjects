#include "02_Profiler/C02_DrawDebug.h"
#include "Global.h"
#include "Components/PointLightComponent.h"

AC02_DrawDebug::AC02_DrawDebug()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<UPointLightComponent>(this, &PointLight, "PointLight");

	InitLocation[0] = FVector(0, 0, 0);
	InitLocation[1] = FVector(0, 1000, 0);
	InitLocation[2] = FVector(0, 500, 0);
	InitLocation[3] = FVector(0, 1500, 0);
	InitLocation[4] = FVector(500, 1000, 0);

	Box = FBox(FVector(-50, -100, -50), FVector(50, 100, 50));
}

void AC02_DrawDebug::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC02_DrawDebug::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int32 i = 0; i < 5; i++)
		Location[i] = InitLocation[i] + GetActorLocation();

	DrawDebugSolidBox(GetWorld(), Location[0] + Box.GetCenter(), Box.GetExtent(), FColor::Red);
	DrawDebugPoint(GetWorld(), Location[1], 100, FColor::Green);
	DrawDebugSphere(GetWorld(), Location[2], 100, 10, FColor::Blue);
	DrawDebugCircle(GetWorld(), Location[3], 100, 10, FColor::Magenta);
	DrawDebugLine(GetWorld(), Location[2], Location[3], FColor::Yellow, false, -1, 0, 10);

	FVector location = Location[2];
	location.X += 10;
	location.Y += 10;
	// location.Z += FMath::Sin(GetWorld()->GetTimeSeconds() * 5.0f) * 400.0f;
	location.Z += EaseOutBounce(FMath::Sin(GetWorld()->GetTimeSeconds() * 2.5f)) * 200.0f;

	DrawDebugCapsule(GetWorld(), location, 200, 50, FQuat::Identity, FColor::White);
	DrawDebugDirectionalArrow(GetWorld(), Location[3], location, 400, FColor::Black, false, -1, 0, 20);


	const bool b = FMath::Sign(FMath::Cos(GetWorld()->GetTimeSeconds() * 5.0f)) >= 0;
	PointLight->SetVisibility(b);

}

float AC02_DrawDebug::EaseOutBounce(float x)
{
	const float n1 = 7.5625f;
	const float d1 = 2.75f;

	if (x < 1.0f / d1)
	{
		return n1 * x * x;
	}
	else if (x < 2.0f / d1)
	{
		return n1 * (x -= 1.5f / d1) * x + 0.75f;
	}
	else if (x < 2.5f / d1)
	{
		return n1 * (x -= 2.25f / d1) * x + 0.9375f;
	}
	else
	{
		return n1 * (x -= 2.625f / d1) * x + 0.984375f;
	}
}