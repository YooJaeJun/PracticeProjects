#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMagazine.generated.h"

UCLASS()
class MYUNREALCPP_02_API ACMagazine : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Mesh_Full;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Mesh_Empty;

public:	
	ACMagazine();

protected:
	virtual void BeginPlay() override;

public:
	void SetEject();

private:
	bool bEject;
};
