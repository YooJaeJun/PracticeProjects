#pragma once

#include "CoreMinimal.h"
#include "Weapons/CWeapon.h"
#include "CWeapon_AK47.generated.h"

UCLASS()
class MYUNREALCPP_02_API ACWeapon_AK47 : public ACWeapon
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Equip")
		FName LeftHandSocketName;

private:
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* Sight;

public:
	ACWeapon_AK47();

public:
	void Begin_Equip() override;
	void End_Equip() override;

	void Begin_Aim() override;
	void End_Aim() override;
};
