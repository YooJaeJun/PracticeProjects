#include "Weapons/CWeapon_AR4.h"
#include "Global.h"
#include "CMagazine.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Camera/CameraShake.h"
#include "Widgets/CUserWidget_CrossHair.h"

ACWeapon_AR4::ACWeapon_AR4()
{
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/AR4/SK_AR4.SK_AR4'");
	Mesh->SetSkeletalMesh(mesh);

	// Equip
	{
		HolsterSocketName = "Rifle_AR4_Holster";
		CHelpers::GetAsset<UAnimMontage>(&EquipMontage, "AnimMontage'/Game/Character/Animations/Rifle_Equip_Montage.Rifle_Equip_Montage'");
		EquipMontage_PlayRate = 2;
		RightHandSocketName = "Rifle_AR4_RightHand";
		LeftHandLocation = FVector(-32.5f, 15.5f, 7);
	}

	//Aim
	{
		BaseData.bEnableCameraLag = true;
		BaseData.TargetArmLength = 200;
		BaseData.SocketOffset = FVector(0, 50, 15);
		BaseData.FieldOfView = 90;

		AimData.bEnableCameraLag = false;
		AimData.TargetArmLength = 80;
		AimData.SocketOffset = FVector(0, 55, 10);
		AimData.FieldOfView = 65;
	}

	// Fire
	{
		RecoilAngle = 0.75f;
		CHelpers::GetClass<UMatineeCameraShake>(&CameraShakeClass, "Blueprint'/Game/Weapons/BP_CameraShake_AR4.BP_CameraShake_AR4_C'");
		AutoFireInterval = 0.15f;
		RecoilRate = 0.05f;
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
		CHelpers::GetClass<ACMagazine>(&MagazineClass, "Blueprint'/Game/Weapons/BP_CMagazine_AR4.BP_CMagazine_AR4_C'");
		MagazineSocketName = "Rifle_Magazine";
	}
}
