#pragma once

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"

class EXAMPLE_API FExampleDebuggerCategory
	: public FGameplayDebuggerCategory
{
public:
	FExampleDebuggerCategory();
	~FExampleDebuggerCategory();

public:
	static TSharedRef<FGameplayDebuggerCategory> MakeInstance();

public:
	void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;
};
