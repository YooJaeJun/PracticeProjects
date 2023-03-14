#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C07_Override.generated.h"

UCLASS()
class MYUNREALCPP_01_API AC07_Override : public AActor
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
	AC07_Override();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UFUNCTION(BlueprintNativeEvent)
		void ChangeColorWhite();

	void ChangeColorWhite_Implementation();

	UFUNCTION(BlueprintImplementableEvent)
		void ChangeColorRed();
};
