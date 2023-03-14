#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C05_SpotLight.generated.h"

UCLASS()
class MYUNREALCPP_01_API AC05_SpotLight : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class USpotLightComponent* Lights[3];

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
public:	
	AC05_SpotLight();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnLight(int32 InIndex, FLinearColor InColor);
};
