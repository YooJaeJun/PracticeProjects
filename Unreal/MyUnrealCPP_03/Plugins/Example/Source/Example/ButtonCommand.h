#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class EXAMPLE_API FButtonCommand 
	: public TCommands<FButtonCommand>
{
public:
	FButtonCommand();
	~FButtonCommand();

public:
	void RegisterCommands() override;

public:
	TSharedPtr<FUICommandList> Command;

public:
	TSharedPtr<FUICommandInfo> LoadMesh;

private:
	void OnClicked_LoadMesh();
};