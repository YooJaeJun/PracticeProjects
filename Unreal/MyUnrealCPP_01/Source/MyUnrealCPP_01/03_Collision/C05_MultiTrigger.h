#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C05_MultiTrigger.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiLightOverlap, int32, FLinearColor);

UCLASS()
class MYUNREALCPP_01_API AC05_MultiTrigger : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere)
		class UTextRenderComponent* Text;
	
public:	
	AC05_MultiTrigger();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	FMultiLightOverlap OnMultiLightOverlap;
};
