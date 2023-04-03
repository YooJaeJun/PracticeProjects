// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyUnrealCPP_03GameMode.h"
#include "MyUnrealCPP_03PlayerController.h"
#include "MyUnrealCPP_03Character.h"
#include "UObject/ConstructorHelpers.h"

AMyUnrealCPP_03GameMode::AMyUnrealCPP_03GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMyUnrealCPP_03PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}