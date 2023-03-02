#include "01_Spawn/C03_Spawner.h"
#include "Global.h"
#include "C02_Mesh.h"

AC03_Spawner::AC03_Spawner()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AC03_Spawner::BeginPlay()
{
	Super::BeginPlay();

	for (int32 i = 0; i < 3; i++)
	{
		if (SpawnClasses[i] == nullptr)
			continue;

		FVector location = GetActorLocation();

		FTransform transform;
		transform.SetLocation(FVector(location.X, location.Y + i * 350, location.Z));

		GetWorld()->SpawnActor<AC02_Mesh>(SpawnClasses[i], transform);
	}
}

