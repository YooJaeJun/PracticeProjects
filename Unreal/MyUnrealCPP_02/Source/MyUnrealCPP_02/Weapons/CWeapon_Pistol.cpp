#include "Weapons/CWeapon_Pistol.h"
#include "Global.h"
#include "CMagazine.h"
#include "CWeaponComponent.h"
#include "Character/CPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Camera/CameraShake.h"
#include "Widgets/CUserWidget_CrossHair.h"

ACWeapon_Pistol::ACWeapon_Pistol()
{
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/MilitaryWeapSilver/Weapons/Pistols_A.Pistols_A'");
	Mesh->SetSkeletalMesh(mesh);

	// Equip
	{
		HolsterSocketName = NAME_None;
		CHelpers::GetAsset<UAnimMontage>(&EquipMontage, "AnimMontage'/Game/Character/Animations/Pistol_Equip_Montage.Pistol_Equip_Montage'");
		EquipMontage_PlayRate = 2;
		RightHandSocketName = "Pistol_RightHand";
		LeftHandLocation = FVector(0, 12.5f, 0);
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
		RecoilAngle = 1.5f;
		CHelpers::GetClass<UMatineeCameraShake>(&CameraShakeClass, "Blueprint'/Game/Weapons/BP_CameraShake_Pistol.BP_CameraShake_Pistol_C'");
		AutoFireInterval = 0.3f;
		RecoilRate = 0.05f;
		SpreadSpeed = 6;
		MaxSpreadAlignment = 4;
	}

	//UI
	{
		CHelpers::GetClass<UCUserWidget_CrossHair>(&CrossHairClass, "WidgetBlueprint'/Game/Widgets/WB_CrossHair.WB_CrossHair_C'");
	}

	//Magazine
	{
		MaxMagazineCount = 5;
		CHelpers::GetAsset<UAnimMontage>(&ReloadMontage, "AnimMontage'/Game/Character/Animations/Pistol_Reload_Montage.Pistol_Reload_Montage'");
		ReloadMontage_PlayRate = 1.5f;
		MagazineBoneName = NAME_None;
		CHelpers::GetClass<ACMagazine>(&MagazineClass, "Blueprint'/Game/Weapons/BP_CMagazine_Pistol.BP_CMagazine_Pistol_C'");
		MagazineSocketName = "Pistol_Magazine";
	}

	//Arms
	{
		ArmsMeshTransform.SetLocation(FVector(0, 5.1f, -156.6));
		ArmsMeshTransform.SetRotation(FQuat(FRotator(0, -4.8f, 0)));

		ArmsLeftHandTransform.SetLocation(FVector(0, 10, 0));
		ArmsLeftHandTransform.SetRotation(FQuat(FRotator(0, 180, 180)));
	}
}

void ACWeapon_Pistol::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetVisibility(false);
}

void ACWeapon_Pistol::Begin_Equip()
{
	Super::Begin_Equip();

	Mesh->SetVisibility(true);
	Owner->GetArms()->SetRelativeTransform(ArmsMeshTransform);
}

void ACWeapon_Pistol::Begin_Aim()
{
	Super::Begin_Aim();

	if (!!CrossHair)
		CrossHair->SetVisibility(ESlateVisibility::Hidden);

	Owner->GetMesh()->SetVisibility(false);
	Owner->GetBackpack()->SetVisibility(false);
	Owner->GetArms()->SetVisibility(true);

	CHelpers::AttachTo(this, Owner->GetArms(), RightHandSocketName);

	CHelpers::GetComponent<UCWeaponComponent>(Owner)->OnWeaponAim_Arms_Begin.Broadcast(this);
}

void ACWeapon_Pistol::End_Aim()
{
	Super::End_Aim();

	if (!!CrossHair)
		CrossHair->SetVisibility(ESlateVisibility::Visible);

	Owner->GetMesh()->SetVisibility(true);
	Owner->GetBackpack()->SetVisibility(true);
	Owner->GetArms()->SetVisibility(false);

	CHelpers::AttachTo(this, Owner->GetMesh(), RightHandSocketName);

	CHelpers::GetComponent<UCWeaponComponent>(Owner)->OnWeaponAim_Arms_End.Broadcast();
}
