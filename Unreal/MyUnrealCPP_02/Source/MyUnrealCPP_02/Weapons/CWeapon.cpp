#include "Weapons/CWeapon.h"
#include "Global.h"
#include "CBullet.h"
#include "CMagazine.h"
#include "Character/CPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraShake.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Particles/ParticleSystem.h"
#include "Widgets/CUserWidget_CrossHair.h"

void FWeaponAimData::SetData(ACharacter* InOwner)
{
	USpringArmComponent* springArm = CHelpers::GetComponent<USpringArmComponent>(InOwner);
	springArm->TargetArmLength = TargetArmLength;
	springArm->SocketOffset = SocketOffset;
	springArm->bEnableCameraLag = bEnableCameraLag;
}

void FWeaponAimData::SetDataByNoneCurve(ACharacter* InOwner)
{
	USpringArmComponent* springArm = CHelpers::GetComponent<USpringArmComponent>(InOwner);
	springArm->TargetArmLength = TargetArmLength;
	springArm->SocketOffset = SocketOffset;
	springArm->bEnableCameraLag = bEnableCameraLag;

	UCameraComponent* camera = CHelpers::GetComponent<UCameraComponent>(InOwner);
	camera->FieldOfView = FieldOfView;
}

/**
 * @brief //////////////////////////////////////////////////////////////////////////
 */

ACWeapon::ACWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh", Root);

	CHelpers::CreateActorComponent<UTimelineComponent>(this, &Timeline, "Timeline");

	CHelpers::GetAsset<UCurveFloat>(&AimCurve, "CurveFloat'/Game/Weapons/Curve_Aim.Curve_Aim'");

	CHelpers::GetAsset<UMaterialInstanceConstant>(&HitDecal, "MaterialInstanceConstant'/Game/Materials/M_Decal_Inst.M_Decal_Inst'");
	CHelpers::GetAsset<UParticleSystem>(&HitParticle, "ParticleSystem'/Game/Effects/P_Impact_Default.P_Impact_Default'");

	CHelpers::GetAsset<UParticleSystem>(&FlashParticle, "ParticleSystem'/Game/Effects/P_Muzzleflash.P_Muzzleflash'");
	CHelpers::GetAsset<UParticleSystem>(&EjectParticle, "ParticleSystem'/Game/Effects/P_Eject_bullet.P_Eject_bullet'");
	CHelpers::GetAsset<USoundWave>(&FireSound, "SoundWave'/Game/Sounds/S_RifleShoot.S_RifleShoot'");
	CHelpers::GetClass<ACBullet>(&BulletClass, "Blueprint'/Game/Weapons/BP_CBullet.BP_CBullet_C'");
}

void ACWeapon::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACPlayer>(GetOwner());

	if (HolsterSocketName.IsValid())
		CHelpers::AttachTo(this, Owner->GetMesh(), HolsterSocketName);

	BaseData.SetDataByNoneCurve(Owner);

	if (!!AimCurve)
	{
		FOnTimelineFloat timeline;
		timeline.BindUFunction(this, "OnAiming");

		Timeline->AddInterpFloat(AimCurve, timeline);
		Timeline->SetLooping(false);
		Timeline->SetPlayRate(AimingSpeed);
	}

	if (!!CrossHairClass)
	{
		CrossHair = CreateWidget<UCUserWidget_CrossHair, APlayerController>(Owner->GetController<APlayerController>(), CrossHairClass);
		CrossHair->AddToViewport();
		CrossHair->SetVisibility(ESlateVisibility::Hidden);
		CrossHair->UpdateSpreadRange(CurrSpreadRadius, MaxSpreadAlignment);
	}

	CurrMagazineCount = MaxMagazineCount;
}

void ACWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LastAddSpreadTime >= 0.0f)
	{
		if (GetWorld()->GetTimeSeconds() - LastAddSpreadTime >= AutoFireInterval + 0.25f)
		{
			CurrSpreadRadius = 0.0f;
			LastAddSpreadTime = 0.0f;

			if (!!CrossHair)
				CrossHair->UpdateSpreadRange(CurrSpreadRadius, MaxSpreadAlignment);
		} //if
	}
}

bool ACWeapon::CanEquip()
{
	bool b = false;	// or 쓸 거라 최초 false
	b |= bEquipping;
	b |= bReload;
	b |= bFiring;

	return !b;
}

void ACWeapon::Equip()
{
	bEquipping = true;

	if (!!EquipMontage)
		Owner->PlayAnimMontage(EquipMontage, EquipMontage_PlayRate);
}

void ACWeapon::Begin_Equip()
{
	if (RightHandSocketName.IsValid())
		CHelpers::AttachTo(this, Owner->GetMesh(), RightHandSocketName);
}

void ACWeapon::End_Equip()
{
	bEquipping = false;

	if (!!CrossHair)
		CrossHair->SetVisibility(ESlateVisibility::Visible);
}

bool ACWeapon::CanUnequip()
{
	bool b = false;
	b |= bEquipping;
	b |= bReload;
	b |= bFiring;

	return !b;
}

void ACWeapon::Unequip()
{
	End_Aim();

	if (HolsterSocketName.IsValid())
		CHelpers::AttachTo(this, Owner->GetMesh(), HolsterSocketName);

	if (!!CrossHair)
		CrossHair->SetVisibility(ESlateVisibility::Hidden);
}

bool ACWeapon::CanAim()
{
	bool b = false;
	b |= bEquipping;
	b |= bReload;
	b |= bInAim;

	return !b;
}

void ACWeapon::Begin_Aim()
{
	bInAim = true;

	if (!!AimCurve)
	{
		Timeline->PlayFromStart();
		AimData.SetData(Owner);

		return;
	}

	AimData.SetDataByNoneCurve(Owner);
}

void ACWeapon::End_Aim()
{
	CheckFalse(bInAim);
	bInAim = false;

	if (!!AimCurve)
	{
		Timeline->ReverseFromEnd();
		BaseData.SetData(Owner);

		return;
	}

	BaseData.SetDataByNoneCurve(Owner);
}

void ACWeapon::OnAiming(float Output)
{
	UCameraComponent* camera = CHelpers::GetComponent<UCameraComponent>(Owner);
	camera->FieldOfView = FMath::Lerp(AimData.FieldOfView, BaseData.FieldOfView, Output);
}

bool ACWeapon::CanFire()
{
	bool b = false;
	b |= bEquipping;
	b |= bReload;
	b |= bFiring;

	return !b;
}

void ACWeapon::Begin_Fire()
{
	bFiring = true;

	if (bAutoFire)
	{
		GetWorld()->GetTimerManager().SetTimer(AutoFireHandle, this, &ACWeapon::OnFiring, AutoFireInterval, true, 0);

		return;
	}

	OnFiring();
}

void ACWeapon::End_Fire()
{
	CheckFalse(bFiring);

	if (GetWorld()->GetTimerManager().IsTimerActive(AutoFireHandle))
		GetWorld()->GetTimerManager().ClearTimer(AutoFireHandle);

	bFiring = false;
}

void ACWeapon::OnFiring()
{
	UCameraComponent* camera = CHelpers::GetComponent<UCameraComponent>(Owner);
	FVector direction = camera->GetForwardVector();
	FTransform transform = camera->GetComponentToWorld();

	FVector start = transform.GetLocation() + direction;

	direction = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(direction, RecoilAngle);
	FVector end = transform.GetLocation() + direction * HitDistance;

	// DrawDebugLine(GetWorld(), start, end, FColor::Red, true, 5);

	TArray<AActor*> ignores;
	FHitResult hitResult;

	UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, ETraceTypeQuery::TraceTypeQuery1, 
		false, ignores, EDrawDebugTrace::None, hitResult, true);

	if (hitResult.bBlockingHit)
	{
		if (!!HitDecal)
		{
			FRotator rotator = hitResult.ImpactNormal.Rotation();

			UDecalComponent* decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), HitDecal, 
				FVector(5), hitResult.Location, rotator, 10);
			decal->SetFadeScreenSize(0);
		}

		if (!!HitParticle)
		{
			FRotator rotator = UKismetMathLibrary::FindLookAtRotation(hitResult.Location, hitResult.TraceStart);

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, hitResult.Location, rotator);
		}
	}

	if (!!FlashParticle)
		UGameplayStatics::SpawnEmitterAttached(FlashParticle, Mesh, "Muzzle", 
			FVector::ZeroVector, FRotator::ZeroRotator,
			EAttachLocation::KeepRelativeOffset);

	if (!!EjectParticle)
		UGameplayStatics::SpawnEmitterAttached(EjectParticle, Mesh, "Eject", 
			FVector::ZeroVector, FRotator::ZeroRotator,
			EAttachLocation::KeepRelativeOffset);

	FVector muzzleLocation = Mesh->GetSocketLocation("Muzzle");

	if (!!FireSound)
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), FireSound, muzzleLocation);

	if (!!CameraShakeClass)
	{
		APlayerController* controller = Owner->GetController<APlayerController>();

		if (!!controller)
			controller->PlayerCameraManager->StartCameraShake(CameraShakeClass);
	}

	Owner->AddControllerPitchInput(-RecoilRate * UKismetMathLibrary::RandomFloatInRange(0.8f, 1.2f));

	if (CurrSpreadRadius <= 1.0f)
	{
		CurrSpreadRadius += SpreadSpeed * GetWorld()->GetDeltaSeconds();

		if (!!CrossHair)
			CrossHair->UpdateSpreadRange(CurrSpreadRadius, MaxSpreadAlignment);
	}
	LastAddSpreadTime = GetWorld()->GetTimeSeconds();

	if (!!BulletClass)
	{
		FVector location = Mesh->GetSocketLocation("Muzzle_Bullet");

		FActorSpawnParameters params;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ACBullet* bullet = GetWorld()->SpawnActor<ACBullet>(BulletClass, location, direction.Rotation(), params);

		if (!!bullet)
			bullet->Shoot(direction);
	}

	if (CurrMagazineCount >= 1)
		CurrMagazineCount--;
	else
	{
		if (CanReload())
			Reload();
	}
}

void ACWeapon::ToggleAutoFire()
{
	bAutoFire = !bAutoFire;
}

bool ACWeapon::CanReload()
{
	bool b = false;
	b |= bEquipping;
	b |= bReload;

	return !b;
}

void ACWeapon::Reload()
{
	bReload = true;

	End_Aim();
	End_Fire();

	if (!!ReloadMontage)
		Owner->PlayAnimMontage(ReloadMontage, ReloadMontage_PlayRate);
}

void ACWeapon::Eject_Magazine()
{
	if (MagazineBoneName.IsValid())
		Mesh->HideBoneByName(MagazineBoneName, EPhysBodyOp::PBO_None);

	CheckNull(MagazineClass);

	FTransform transform = Mesh->GetSocketTransform(MagazineBoneName);
	ACMagazine* magazine = GetWorld()->SpawnActorDeferred<ACMagazine>(MagazineClass, transform, nullptr,
		nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	magazine->SetEject();
	magazine->SetLifeSpan(5);
	magazine->FinishSpawning(transform);
}

void ACWeapon::Spawn_Magazine()
{
	CheckNull(MagazineClass);

	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Magazine = GetWorld()->SpawnActor<ACMagazine>(MagazineClass, params);
	CHelpers::AttachTo(Magazine, Owner->GetMesh(), MagazineSocketName);
}

void ACWeapon::Load_Magazine()
{
	CurrMagazineCount = MaxMagazineCount;

	if (MagazineBoneName.IsValid())
		Mesh->UnHideBoneByName(MagazineBoneName);

	if (!!Magazine)
		Magazine->Destroy();
}

void ACWeapon::End_Reload()
{
	bReload = false;
}
