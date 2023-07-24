#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Components/CWeaponComponent.h"
#include "Components/CFeetComponent.h"
#include "CAnimInstance.generated.h"

UCLASS()
class MYUNREALCPP_04_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
        float Speed;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
        float Pitch;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
        float Direction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
        bool bFalling;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
        bool bBow_Aiming;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InverseKinemetics")
        bool bFeet;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InverseKinemetics")
        FFeetData FeetData;

protected:
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
        EWeaponType WeaponType = EWeaponType::Max;

public:
    void NativeBeginPlay() override;
    void NativeUpdateAnimation(float DeltaSeconds) override;

private:
    UFUNCTION()
        void OnWeaponTypeChanged(EWeaponType InPrevType, EWeaponType InNewType);

private:
    class ACharacter* OwnerCharacter;
    class UCWeaponComponent* Weapon;

private:
    FRotator PrevRotation;
};
