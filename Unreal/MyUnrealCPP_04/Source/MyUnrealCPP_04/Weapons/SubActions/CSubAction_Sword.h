#pragma once
#include "CoreMinimal.h"
#include "Weapons/CSubAction.h"
#include "Weapons/CWeaponStructures.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CSubAction_Sword.generated.h"

UCLASS(Blueprintable)
class MYUNREALCPP_04_API UCSubAction_Sword : public UCSubAction
{
	GENERATED_BODY()

private:
    UPROPERTY(EditDefaultsOnly, Category = "Trace")
        float Distance = 1000;

    UPROPERTY(EditDefaultsOnly, Category = "Trace")
        float Speed = 200;

    UPROPERTY(EditDefaultsOnly, Category = "Trace")
        TEnumAsByte<EDrawDebugTrace::Type> DrawDebug;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Action")
        FDoActionData ActionData;

    UPROPERTY(EditDefaultsOnly, Category = "Action")
        FHitData HitData;

private:
    UPROPERTY(EditAnywhere, Category = "Add-On")
        TSubclassOf<class ACGhostTrail> GhostTrailClass;

public:
    void Pressed() override;
    void Begin_SubAction_Implementation() override;
    void End_SubAction_Implementation() override;
    void Tick_Implementation(float InDeltaTime) override;

private:
    UFUNCTION()
        void OnAttachmentBeginOverlap(class ACharacter* InAttacker, AActor* InAttackCuaser, class ACharacter* InOther);

private:
    bool bMoving;

    FVector Start;
    FVector End;

    TArray<class ACharacter*> Overlapped;
    TArray<class ACharacter*> Hitted;

private:
    class ACGhostTrail* GhostTrail;
};
