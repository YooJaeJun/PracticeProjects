#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C05_FallingBox.generated.h"

UCLASS()
class MYUNREALCPP_01_API AC05_FallingBox : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Meshes[3];

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

public:	
	AC05_FallingBox();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnPhysics(int32 InIndex, FLinearColor InColor);

private:
	class UMaterialInstanceDynamic* Materials[3];
	FVector WorldLocation[3];
};
