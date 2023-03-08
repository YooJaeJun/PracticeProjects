#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C01_ActorOverlap.generated.h"

UCLASS()
class MYUNREALCPP_01_API AC01_ActorOverlap : public AActor
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
	AC01_ActorOverlap();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void EndOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
