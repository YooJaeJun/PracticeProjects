#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Weapons/CWeaponComponent.h"
#include "CAnimInstance.generated.h"

UCLASS()
class MYUNREALCPP_02_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		float Pitch;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
		float Direction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapons")
		EWeaponType WeaponType = EWeaponType::Max;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapons")
		bool bInAim;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapons")
		bool bUseIK;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapons")
		FVector LeftHandLocation;


public:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION()
		void OnWeaponTypeChanged(EWeaponType InPrevType, EWeaponType InNewType);

private:
	class ACPlayer* OwnerCharacter;
	class UCWeaponComponent* Weapon;

private:
	FRotator PrevRotation;
};
