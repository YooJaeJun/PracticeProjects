#include "ExampleConsoleCommand.h"
#include "HAL/IConsoleManager.h"
#include "Misc/MessageDialog.h"
#include "GameFramework/Character.h"

FExampleConsoleCommand::FExampleConsoleCommand()
{
	FConsoleCommandDelegate command = FConsoleCommandDelegate::CreateRaw(this,
		&FExampleConsoleCommand::ExecuteCommand);

	Command = IConsoleManager::Get().RegisterConsoleCommand(L"ViewMessageDialog",
		L"Move actor to position(FVector)", command);


	FConsoleCommandWithArgsDelegate command2;
	command2.BindLambda([&](const TArray<FString>& InArgs) 
	{
		FString content;
		for (FString str : InArgs)
			content += ", " + str;

		FMessageDialog::Debugf(FText::FromString(content));
	});

	Command2 = IConsoleManager::Get().RegisterConsoleCommand(L"ViewMessageArgs",
		L"Move actor to position(FVector)", command2);


	FConsoleCommandWithWorldAndArgsDelegate command3;
	command3.BindRaw(this, &FExampleConsoleCommand::ExecuteCommand3);

	Command3 = IConsoleManager::Get().RegisterConsoleCommand(L"MoveToPlayer",
		L"Move player to position(FVector)", command3);
}

FExampleConsoleCommand::~FExampleConsoleCommand()
{
	if (!!Command)
		IConsoleManager::Get().UnregisterConsoleObject(Command);

	if (!!Command2)
		IConsoleManager::Get().UnregisterConsoleObject(Command2);

	if (!!Command3)
		IConsoleManager::Get().UnregisterConsoleObject(Command3);
}

void FExampleConsoleCommand::ExecuteCommand()
{
	FText title = FText::FromString("warning");
	FText context = FText::FromString("Don't moving, Need to position input");

	FMessageDialog::Debugf(context, &title);
}

void FExampleConsoleCommand::ExecuteCommand3(const TArray<FString>& InArgs, UWorld* InWorld)
{
	//100,200,300
	if (InArgs.Num() != 1)
	{
		GLog->Log("FVector for required input");

		return;
	}

	TArray<FString> strs;
	InArgs[0].ParseIntoArray(strs, L",");

	FVector position;
	position.X = FCString::Atof(*strs[0]);
	position.Y = FCString::Atof(*strs[1]);
	position.Z = FCString::Atof(*strs[2]);

	if (FApp::IsGame())
	{
		APlayerController* controller = InWorld->GetFirstPlayerController<APlayerController>();
		ACharacter* character = controller->GetPawn<ACharacter>();

		character->SetActorLocation(position);

		return;
	}

	for (AActor* actor : InWorld->GetCurrentLevel()->Actors)
	{
		if (!!actor && actor->GetName().Contains("PlayerStart"))
			actor->SetActorLocation(position);
	}
}
