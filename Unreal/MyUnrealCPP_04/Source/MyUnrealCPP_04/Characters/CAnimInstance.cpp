#include "Characters/CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapons/CSubAction.h"
#include "Parkour/CParkourComponent.h"
#include "Components/CFeetComponent.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(OwnerCharacter);

	Weapon = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);
	if (!!Weapon)
		Weapon->OnWeaponTypeChange.AddDynamic(this, &UCAnimInstance::OnWeaponTypeChanged);
}

void UCAnimInstance::OnWeaponTypeChanged(EWeaponType InPrevType, EWeaponType InNewType)
{
	WeaponType = InNewType;
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(OwnerCharacter);

	Speed = OwnerCharacter->GetVelocity().Size2D();

	FRotator rotator = OwnerCharacter->GetVelocity().ToOrientationRotator();
	FRotator rotator2 = OwnerCharacter->GetControlRotation();
	FRotator delta = UKismetMathLibrary::NormalizedDeltaRotator(rotator, rotator2);
	PrevRotation = UKismetMathLibrary::RInterpTo(PrevRotation, delta, DeltaSeconds, 25);
	Direction = PrevRotation.Yaw;

	Pitch = UKismetMathLibrary::FInterpTo(Pitch, OwnerCharacter->GetBaseAimRotation().Pitch, DeltaSeconds, 25);
	bFalling = OwnerCharacter->GetCharacterMovement()->IsFalling();


	CheckNull(Weapon);
	CheckFalse(Weapon->IsUnarmedMode());

	CheckNull(Weapon);

	if (!!Weapon->GetSubAction())
	{
		bBow_Aiming = true;
		bBow_Aiming &= WeaponType == EWeaponType::Bow;
		bBow_Aiming &= Weapon->GetSubAction()->GetInAction();
	}


	UCParkourComponent* parkour = CHelpers::GetComponent<UCParkourComponent>(OwnerCharacter);
	UCFeetComponent* feet = CHelpers::GetComponent<UCFeetComponent>(OwnerCharacter);

	bFeet = false;

	if (!!parkour && !!feet)
	{
		bFeet = parkour->IsExecuting() == false;
		FeetData = feet->GetData();
	}
	else if (!!feet)
	{
		bFeet = true;
		FeetData = feet->GetData();
	}
}