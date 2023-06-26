#include "Weapons/SubActions/CSubAction_Fist.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CMovementComponent.h"
#include "Weapons/CAttachment.h"
#include "Weapons/CDoAction.h"
#include "Weapons/AddOns/CGhostTrail.h"

void UCSubAction_Fist::Pressed()
{
	CheckFalse(State->IsIdleMode());
	CheckTrue(State->IsSubActionMode());

	Super::Pressed();

	State->SetActionMode();
	State->OnSubActionMode();

	GhostTrail = CHelpers::Play_GhostTrail(GhostTrailClass, Owner);

	ActionData.DoAction(Owner);
}

void UCSubAction_Fist::Begin_SubAction_Implementation()
{
	Super::Begin_SubAction_Implementation();

	Attachment->OnAttachmentEndCollision.Remove(DoAction, "OnAttachmentEndCollision");
	Attachment->OnAttachmentBeginOverlap.Remove(DoAction, "OnAttachmentBeginOverlap");

	Attachment->OnAttachmentEndCollision.AddDynamic(this, &UCSubAction_Fist::OnAttachmentEndCollision);
	Attachment->OnAttachmentBeginOverlap.AddDynamic(this, &UCSubAction_Fist::OnAttachmentBeginOverlap);
}

void UCSubAction_Fist::End_SubAction_Implementation()
{
	Super::End_SubAction_Implementation();

	Attachment->OnAttachmentEndCollision.Remove(this, "OnAttachmentEndCollision");
	Attachment->OnAttachmentBeginOverlap.Remove(this, "OnAttachmentBeginOverlap");

	Attachment->OnAttachmentEndCollision.AddDynamic(DoAction, &UCDoAction::OnAttachmentEndCollision);
	Attachment->OnAttachmentBeginOverlap.AddDynamic(DoAction, &UCDoAction::OnAttachmentBeginOverlap);


	State->SetIdleMode();
	State->OffSubActionMode();

	Movement->Move();
	Movement->DisableFixedCamera();

	GhostTrail->Destroy();

	HitIndex = 0;
}

void UCSubAction_Fist::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOther)
{
	CheckNull(InOther);

	for (ACharacter* character : Hitted)
		CheckTrue(character == InOther);

	Hitted.AddUnique(InOther);

	CheckTrue(HitIndex >= HitDatas.Num());
	HitDatas[HitIndex].SendDamage(Owner, InAttackCauser, InOther);
}

void UCSubAction_Fist::OnAttachmentEndCollision()
{
	Hitted.Empty();

	HitIndex++;
}