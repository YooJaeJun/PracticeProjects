#include "01_Spawn/C01_Property.h"

AC01_Property::AC01_Property()
	: b(20)
{
	PrimaryActorTick.bCanEverTick = true;

	c = 30;
}

void AC01_Property::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC01_Property::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

