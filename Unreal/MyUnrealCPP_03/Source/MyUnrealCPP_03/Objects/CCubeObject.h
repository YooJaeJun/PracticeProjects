#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCubeObject.generated.h"

UCLASS()
class MYUNREALCPP_03_API ACCubeObject : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
		class UProceduralMeshComponent* Mesh;
	
public:	
	ACCubeObject();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void AddTriangles(int32 InStart);

private:
	TArray<FVector> Positions;
	TArray<int32> Indices;
	TArray<FVector> Normals;
	TArray<FColor> Colors;
	TArray<FVector2D> Uvs;
};
