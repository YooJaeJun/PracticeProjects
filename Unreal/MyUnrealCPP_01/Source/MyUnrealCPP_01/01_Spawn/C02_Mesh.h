#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_Mesh.generated.h"

class UStaticMeshComponent;
class UMaterialInstanceDynamic;

UCLASS()
class MYUNREALCPP_01_API AC02_Mesh : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Mesh;

public:	
	AC02_Mesh();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void SetRandomColor();

private:
	UMaterialInstanceDynamic* Material;
};
