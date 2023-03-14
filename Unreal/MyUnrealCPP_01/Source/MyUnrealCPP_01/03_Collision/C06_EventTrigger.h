#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C06_EventTrigger.generated.h"

UCLASS()
class MYUNREALCPP_01_API AC06_EventTrigger : public AActor
{
	GENERATED_BODY()

private:
	DECLARE_EVENT_OneParam(AC06_EventTrigger, FExplosionEvent, int32);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

public:	
	AC06_EventTrigger();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	FExplosionEvent OnExplosionEvent;
};
