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

	UPROPERTY(EditAnywhere)
		float bEnableCameraLag;

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
		float AimingSpeed = 200;

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

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		float AutoFireInterval;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		float RecoilRate;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		float SpreadSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		float MaxSpreadAlignment;

	UPROPERTY(EditDefaultsOnly, Category = "Fire")
		TSubclassOf<class ACBullet> BulletClass;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<class UCUserWidget_CrossHair> CrossHairClass;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Magazine")
		uint8 MaxMagazineCount;

	UPROPERTY(EditDefaultsOnly, Category = "Magazine")
		class UAnimMontage* ReloadMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Magazine")
		float ReloadMontage_PlayRate;

	UPROPERTY(EditDefaultsOnly, Category = "Magazine")
		FName MagazineBoneName;

	UPROPERTY(EditDefaultsOnly, Category = "Magazine")
		TSubclassOf<class ACMagazine> MagazineClass;

	UPROPERTY(EditDefaultsOnly, Category = "Magazine")
		FName MagazineSocketName;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Arms")
		FTransform ArmsMeshTransform;

	UPROPERTY(EditDefaultsOnly, Category = "Arms")
		FTransform ArmsLeftHandTransform;

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
	FORCEINLINE bool IsAutoFire() { return bAutoFire; }
	FORCEINLINE FVector GetLeftHandLocation() { return LeftHandLocation; }
	FORCEINLINE FTransform GetArmsLeftHandTransform() { return ArmsLeftHandTransform; }


	FORCEINLINE uint8 GetCurrMagazineCount() { return CurrMagazineCount; }
	FORCEINLINE uint8 GetMaxMagazineCount() { return MaxMagazineCount; }

public:	
	ACWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	bool CanEquip();
	void Equip();
	virtual void Begin_Equip();
	virtual void End_Equip();

	bool CanUnequip();
	void Unequip();

public:
	bool CanAim();
	virtual void Begin_Aim();
	virtual void End_Aim();

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

public:
	void ToggleAutoFire();

public:
	bool CanReload();
	void Reload();

	void Eject_Magazine();
	void Spawn_Magazine();
	void Load_Magazine();
	void End_Reload();

private:
	bool bEquipping;
	bool bInAim;
	bool bFiring;
	bool bReload;
	bool bAutoFire = true;

protected:
	class ACPlayer* Owner;

private:
	FTimerHandle AutoFireHandle;

protected:
	class UCUserWidget_CrossHair* CrossHair;

private:
    float CurrSpreadRadius;
    float LastAddSpreadTime;

private:
	uint8 CurrMagazineCount;

	class ACMagazine* Magazine;
};
