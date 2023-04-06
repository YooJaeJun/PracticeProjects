#include "Character/CAnimInstance_Arms.h"
#include "Global.h"
#include "CPlayer.h"

void UCAnimInstance_Arms::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACPlayer>(TryGetPawnOwner());
	CheckNull(OwnerCharacter);

	Weapon = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);
	CheckNull(Weapon);

	Weapon->OnWeaponTypeChanged.AddDynamic(this, &UCAnimInstance_Arms::OnWeaponTypeChanged);
}

void UCAnimInstance_Arms::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(OwnerCharacter);

	LeftHandTransform = Weapon->GetLeftHandTransform();
}

void UCAnimInstance_Arms::OnWeaponTypeChanged(EWeaponType InPrevType, EWeaponType InNewType)
{
	WeaponType = InNewType;
}
