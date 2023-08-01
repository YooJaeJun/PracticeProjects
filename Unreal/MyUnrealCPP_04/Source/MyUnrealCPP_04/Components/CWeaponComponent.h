#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CWeaponComponent.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Fist, Sword, Hammer, Warp, Around, Bow, Max,
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponTypeChanged, EWeaponType, InPrevType, EWeaponType, InNewType);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYUNREALCPP_04_API UCWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "DataAsset")
		class UCWeaponAsset* DataAssets[static_cast<uint8>(EWeaponType::Max)];

public:
	FORCEINLINE EWeaponType GetWeaponType() { return Type; }

public:
	FORCEINLINE bool IsUnarmedMode() { return Type == EWeaponType::Max; }
	FORCEINLINE bool IsFistMode() { return Type == EWeaponType::Fist; }
	FORCEINLINE bool IsSwordMode() { return Type == EWeaponType::Sword; }
	FORCEINLINE bool IsHammerMode() { return Type == EWeaponType::Hammer; }
	FORCEINLINE bool IsWarpMode() { return Type == EWeaponType::Warp; }
	FORCEINLINE bool IsAroundMode() { return Type == EWeaponType::Around; }
	FORCEINLINE bool IsBowMode() { return Type == EWeaponType::Bow; }

public:	
	UCWeaponComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool IsIdleMode();

public:
	class ACAttachment* GetAttachment();
	class UCEquipment* GetEquipment();
	class UCDoAction* GetDoAction();
	class UCSubAction* GetSubAction();

public:
	void SetUnarmedMode();
	void SetFistMode();
	void SetSwordMode();
	void SetHammerMode();
	void SetWarpMode();
	void SetAroundMode();
	void SetBowMode();

	void DoAction();

	void SubAction_Pressed();
	void SubAction_Released();

private:
	void SetMode(EWeaponType InType);
	void ChangeType(EWeaponType InType);

public:
	FWeaponTypeChanged OnWeaponTypeChange;

private:
	class ACharacter* OwnerCharacter;

	EWeaponType Type = EWeaponType::Max;

private:
	UPROPERTY()
		class UCWeaponData* Datas[(int32)EWeaponType::Max];
};
