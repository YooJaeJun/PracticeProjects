#include "Weapons/CWeapon_AK47.h"
#include "Global.h"
#include "CMagazine.h"
#include "Character/CPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraShake.h"
#include "Widgets/CUserWidget_CrossHair.h"

ACWeapon_AK47::ACWeapon_AK47()
{
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/Ka47/SK_KA47.SK_KA47'");
	Mesh->SetSkeletalMesh(mesh);

	//AK
	{
		LeftHandSocketName = "Rifle_AK47_LeftHand";
	}

	// Equip
	{
		HolsterSocketName = "Rifle_AK47_Holster";
		CHelpers::GetAsset<UAnimMontage>(&EquipMontage, "AnimMontage'/Game/Character/Animations/Rifle_Equip_AK47_Montage.Rifle_Equip_AK47_Montage'");
		EquipMontage_PlayRate = 2.0f;
		RightHandSocketName = "Rifle_AK47_RightHand";
		LeftHandLocation = FVector(-35, 15.5f, 4);
	}

	//Aim
	{
		BaseData.bEnableCameraLag = true;
		BaseData.TargetArmLength = 200;
		BaseData.SocketOffset = FVector(0, 50, 15);
		BaseData.FieldOfView = 90;

		AimData.bEnableCameraLag = false;
		AimData.TargetArmLength = 30;
		AimData.SocketOffset = FVector(-55, 0, 10);
		AimData.FieldOfView = 55;
	}

	// Fire
	{
		RecoilAngle = 0.75f;
		CHelpers::GetClass<UMatineeCameraShake>(&CameraShakeClass, "Blueprint'/Game/Weapons/BP_CameraShake_AR4.BP_CameraShake_AR4_C'");
		AutoFireInterval = 0.1f;
		RecoilRate = 0.04f;
		SpreadSpeed = 2.0f;
		MaxSpreadAlignment = 2.0f;
	}

	//UI
	{
		CHelpers::GetClass<UCUserWidget_CrossHair>(&CrossHairClass, "WidgetBlueprint'/Game/Widgets/WB_CrossHair.WB_CrossHair_C'");
	}

	//Magazine
	{
		MaxMagazineCount = 30;
		CHelpers::GetAsset<UAnimMontage>(&ReloadMontage, "AnimMontage'/Game/Character/Animations/Rifle_Reload_Montage.Rifle_Reload_Montage'");
		ReloadMontage_PlayRate = 1.5f;
		MagazineBoneName = "b_gun_mag";
		CHelpers::GetClass<ACMagazine>(&MagazineClass, "Blueprint'/Game/Weapons/BP_CMagazine_AK47.BP_CMagazine_AK47_C'");
		MagazineSocketName = "Rifle_Magazine";
	}
}

void ACWeapon_AK47::Begin_Equip()
{
	if (LeftHandSocketName.IsValid())
		CHelpers::AttachTo(this, Owner->GetMesh(), LeftHandSocketName);
}

void ACWeapon_AK47::End_Equip()
{
	Super::Begin_Equip();
	Super::End_Equip();
}
