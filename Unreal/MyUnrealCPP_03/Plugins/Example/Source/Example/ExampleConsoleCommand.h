#pragma once

#include "CoreMinimal.h"

class EXAMPLE_API FExampleConsoleCommand
{
public:
	FExampleConsoleCommand();
	~FExampleConsoleCommand();

private:
	struct IConsoleCommand* Command;
	struct IConsoleCommand* Command2;
	struct IConsoleCommand* Command3;

private:
	void ExecuteCommand();
	void ExecuteCommand3(const TArray<FString>& InArgs, UWorld* InWorld);
};
