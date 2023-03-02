#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C03_Spawner.generated.h"

UCLASS()
class MYUNREALCPP_01_API AC03_Spawner : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Settings")
		TSubclassOf<class AC02_Mesh> SpawnClasses[3];
	
public:	
	AC03_Spawner();

protected:
	virtual void BeginPlay() override;
};
