#include "BehaviorTree/CBTTaskNode_Speed.h"
#include "Global.h"
#include "Characters/CEnemy_AI.h"
#include "Characters/CAIController.h"

UCBTTaskNode_Speed::UCBTTaskNode_Speed()
{
	NodeName = "Speed";
}

EBTNodeResult::Type UCBTTaskNode_Speed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* ai = Cast<ACEnemy_AI>(controller->GetPawn());
	UCMovementComponent* movement = CHelpers::GetComponent<UCMovementComponent>(ai);

	//태스크 공유 확인
	//FString str = FString::Printf(L"%s, %p", *ai->GetActorLabel(), this);
	//CLog::Log(str);

	movement->SetSpeed(Type);
	
	return EBTNodeResult::Succeeded;
}
