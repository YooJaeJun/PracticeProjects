#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C01_Trigger.generated.h"

UCLASS()
class MYUNREALCPP_01_API AC01_Trigger : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

public:	
	AC01_Trigger();

protected:
	virtual void BeginPlay() override;
};
