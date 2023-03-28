#include "CAnimNotify_Reload.h"
#include "Global.h"
#include "Weapons/CWeaponComponent.h"

FString UCAnimNotify_Reload::GetNotifyName_Implementation() const
{
	return "Reload";
}

void UCAnimNotify_Reload::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	UCWeaponComponent* weapon = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weapon);

	switch (ActionType)
	{
		case EReloadActionType::Eject: weapon->Eject_Magazine(); break;
		case EReloadActionType::Spawn: weapon->Spawn_Magazine(); break;
		case EReloadActionType::Load: weapon->Load_Magazine(); break;
		case EReloadActionType::End: weapon->End_Reload(); break;
	}
}