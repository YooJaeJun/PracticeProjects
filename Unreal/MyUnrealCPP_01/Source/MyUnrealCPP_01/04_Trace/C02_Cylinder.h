#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_Cylinder.generated.h"

UCLASS()
class MYUNREALCPP_01_API AC02_Cylinder : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
	
public:	
	AC02_Cylinder();

protected:
	virtual void BeginPlay() override;

};
