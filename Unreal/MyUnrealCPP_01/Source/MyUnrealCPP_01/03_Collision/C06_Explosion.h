#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C06_Explosion.generated.h"

UCLASS()
class MYUNREALCPP_01_API AC06_Explosion : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Particles")
		class UParticleSystem* Particles[3];

private:
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

public:	
	AC06_Explosion();

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
		void OnExplosion(int32 InIndex);
};
