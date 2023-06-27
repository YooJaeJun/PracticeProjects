#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapons/CWeaponStructures.h"
#include "NiagaraDataInterfaceExport.h"
#include "CAura.generated.h"

UCLASS()
class MYUNREALCPP_04_API ACAura
	: public AActor
	, public INiagaraParticleCallbackHandler
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		FHitData HitData;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		float DamageInterval = 0.1f;

private:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		class UNiagaraComponent* Niagara;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* Box;

public:	
	ACAura();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void OnSystemFinished(UNiagaraComponent* PSystem);

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	void ReceiveParticleData_Implementation(const TArray<FBasicParticleData>& Data, UNiagaraSystem* NiagaraSystem);


private:
	TArray<class ACharacter*> Hitted;
	FTimerHandle TimerHandle;
};
