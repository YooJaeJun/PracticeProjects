#include "Weapons/CWeapon_AR4.h"
#include "Global.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraShake.h"

ACWeapon_AR4::ACWeapon_AR4()
{
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/AR4/SK_AR4.SK_AR4'");
	Mesh->SetSkeletalMesh(mesh);

	// Equip
	{
		HolsterSocketName = "Rifle_AR4_Holster";
		CHelpers::GetAsset<UAnimMontage>(&EquipMontage, "AnimMontage'/Game/Character/Animations/Rifle_Equip_Montage.Rifle_Equip_Montage'");
		EquipMontage_PlayRate = 2.0f;
		RightHandSocketName = "Rifle_AR4_RightHand";
		LeftHandLocation = FVector(-32.5f, 15.5f, 7);
	}

	//Aim
	{
		BaseData.TargetArmLength = 200;
		BaseData.SocketOffset = FVector(0, 50, 15);
		BaseData.FieldOfView = 90;

		AimData.TargetArmLength = 80;
		AimData.SocketOffset = FVector(0, 55, 10);
		AimData.FieldOfView = 65;
	}

	// Fire
	{
		RecoilAngle = 0.75f;
		CHelpers::GetClass<UMatineeCameraShake>(&CameraShakeClass, "Blueprint'/Game/Weapons/BP_CameraShake_AR4.BP_CameraShake_AR4_C'");
	}
}
