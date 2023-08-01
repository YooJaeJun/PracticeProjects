#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Weapons/CWeaponStructures.h"
#include "CWeaponAsset.generated.h"

UCLASS()
class MYUNREALCPP_04_API UCWeaponAsset : public UDataAsset
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ACAttachment> AttachmentClass;

	UPROPERTY(EditAnywhere)
		FEquipmentData EquipmentData;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCEquipment> EquipmentClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCDoAction> DoActionClass;

	UPROPERTY(EditAnywhere)
		TArray<FDoActionData> DoActionDatas;

	UPROPERTY(EditAnywhere)
		TArray<FHitData> HitDatas;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCSubAction> SubActionClass;

public:
	UCWeaponAsset();

	void BeginPlay(class ACharacter* InOwner, class UCWeaponData** OutWeaponData);

#if WITH_EDITOR
	void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;
#endif //WITH_EDITOR
};