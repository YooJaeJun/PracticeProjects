#include "01_Spawn/C01_Property.h"

AC01_Property::AC01_Property()
	: B(20)
{
	PrimaryActorTick.bCanEverTick = true;

	C = 30;
}

void AC01_Property::BeginPlay()
{
	Super::BeginPlay();

	FString str;
	str.Append(GetActorLabel()); 

	str.Append(" / A : ");
	str.Append(FString::FromInt(A) + " or ");
	str.Append(str.FromInt(A));

	str.Append(" / B : ");
	str.Append(FString::FromInt(B));

	str.Append(" / C : ");
	str.Append(FString::FromInt(C));

	GLog->Log(str);
}

void AC01_Property::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	D += DeltaTime;
}

