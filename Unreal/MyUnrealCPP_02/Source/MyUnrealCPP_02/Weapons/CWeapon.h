#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapon.generated.h"

USTRUCT()
struct FWeaponAimData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float TargetArmLength;

	UPROPERTY(EditAnywhere)
		FVector SocketOffset;

	UPROPERTY(EditAnywhere)
		float FieldOfView;

public:
	void SetData(class ACharacter* InOwner);
	void SetDataByNoneCurve(class ACharacter* InOwner);
};

UCLASS(abstract)
class MYUNREALCPP_02_API ACWeapon : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Equip")
		FName HolsterSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Equip")
		class UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Equip")
		float EquipMontage_PlayRate;

	UPROPERTY(EditDefaultsOnly, Category = "Equip")
		FName RightHandSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Equip")
		FVector LeftHandLocation;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Aim")
		FWeaponAimData BaseData;

	UPROPERTY(EditDefaultsOnly, Category = "Aim")
		FWeaponAimData AimData;

	UPROPERTY(EditDefaultsOnly, Category = "Aim")
		class UCurveFloat* AimCurve;

	UPROPERTY(EditDefaultsOnly, Category = "Aim")
		float AimingSpeed = 200.0f;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Hit")
		float HitDistance = 3000;

	UPROPERTY(EditDefaultsOnly, Category = "Hit")
		class UMaterialInstanceConstant* HitDecal;

	UPROPERTY(EditDefaultsOnly, Category = "Hit")
		class UParticleSystem* HitParticle;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		class UParticleSystem* FlashParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		class UParticleSystem* EjectParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		class USoundWave* FireSound;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		float RecoilAngle;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		TSubclassOf<class UMatineeCameraShake> CameraShakeClass;

private:
	UPROPERTY(VisibleAnywhere)
		class USceneComponent* Root;

protected:
	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* Mesh;

private:
	UPROPERTY(VisibleAnywhere)
		class UTimelineComponent* Timeline;

public:
	FORCEINLINE bool IsInAim() { return bInAim; }
	FORCEINLINE FVector GetLeftHandLocation() { return LeftHandLocation; }

public:	
	ACWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	bool CanEquip();
	void Equip();
	void Begin_Equip();
	void End_Equip();

	bool CanUnequip();
	void Unequip();

public:
	bool CanAim();
	void Begin_Aim();
	void End_Aim();

private:
	UFUNCTION()
		void OnAiming(float Output);

public:
	bool CanFire();
	void Begin_Fire();
	void End_Fire();

private:
	UFUNCTION()
		void OnFiring();

private:
	bool bEquipping;
	bool bInAim;
	bool bFiring;
	bool bReload;
	bool bAutoFire = true;

private:
	class ACPlayer* Owner;
};
