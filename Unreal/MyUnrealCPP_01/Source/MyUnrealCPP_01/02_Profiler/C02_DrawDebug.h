#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_DrawDebug.generated.h"

UCLASS()
class MYUNREALCPP_01_API AC02_DrawDebug : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Settings")
		FVector InitLocation[5];

	UPROPERTY(EditAnywhere, Category = "Settings")
		FBox Box;

private:
	UPROPERTY(VisibleAnywhere)
		class UPointLightComponent* PointLight;

public:	
	AC02_DrawDebug();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	float EaseOutBounce(float x);

private:
	FVector Location[5];
};
