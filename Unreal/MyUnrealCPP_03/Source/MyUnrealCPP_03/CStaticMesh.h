#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CStaticMesh.generated.h"

UCLASS()
class MYUNREALCPP_03_API ACStaticMesh : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "Material")
		class UMaterialInstanceConstant* Material;

private:
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Mesh;

public:	
	ACStaticMesh();

protected:
	virtual void BeginPlay() override;
};
