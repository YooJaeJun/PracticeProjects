#include "CAnimNotify_EndState.h"
#include "Global.h"
#include "Characters/ICharacter.h"

FString UCAnimNotify_EndState::GetNotifyName_Implementation() const
{
	return "EndState";
}

void UCAnimNotify_EndState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp);
	CheckNull(MeshComp->GetOwner());

	IICharacter* character = Cast<IICharacter>(MeshComp->GetOwner());
	CheckNull(character);

	switch (StateType)
	{
	case EStateType::BackStep:
		character->End_BackStep();
		character->End_Hitted();
		character->End_Dead();
		break;
	}
}