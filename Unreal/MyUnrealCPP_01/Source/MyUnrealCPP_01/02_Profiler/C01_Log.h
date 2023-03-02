#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C01_Log.generated.h"

UCLASS()
class MYUNREALCPP_01_API AC01_Log : public AActor
{
	GENERATED_BODY()
	
public:	
	AC01_Log();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
