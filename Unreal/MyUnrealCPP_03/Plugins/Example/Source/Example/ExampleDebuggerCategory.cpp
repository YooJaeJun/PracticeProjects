#include "ExampleDebuggerCategory.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"

FExampleDebuggerCategory::FExampleDebuggerCategory()
{
}

FExampleDebuggerCategory::~FExampleDebuggerCategory()
{
}

TSharedRef<FGameplayDebuggerCategory> FExampleDebuggerCategory::MakeInstance()
{
	return MakeShareable(new FExampleDebuggerCategory());
}

void FExampleDebuggerCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	FGameplayDebuggerCategory::CollectData(OwnerPC, DebugActor);

	//GLog->Log(OwnerPC->GetPawn()->GetName());

	//if (!!DebugActor)
	//	GLog->Log(DebugActor->GetName());
}
