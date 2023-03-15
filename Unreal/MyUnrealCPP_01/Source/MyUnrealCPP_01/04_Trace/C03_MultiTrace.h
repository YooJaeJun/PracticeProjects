#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C03_MultiTrace.generated.h"

UCLASS()
class MYUNREALCPP_01_API AC03_MultiTrace : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		class UTextRenderComponent* Text;

public:	
	AC03_MultiTrace();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	float TotalTime;
};
