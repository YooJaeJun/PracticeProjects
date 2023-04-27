#include "ExampleModule.h"
#include "ExampleStyle.h"
#include "ExampleDebuggerCategory.h"
#include "ExampleConsoleCommand.h"
#include "StaticMesh_Detail.h"
#include "ButtonCommand.h"

#include "CStaticMesh.h"

#include "GameplayDebugger.h"
#include "LevelEditor.h"

#define LOCTEXT_NAMESPACE "FExampleModule"
	
IMPLEMENT_MODULE(FExampleModule, Example)

void FExampleModule::StartupModule()
{
	FExampleStyle::Get();

	// Debugger
	{
		IGameplayDebugger::FOnGetCategory category;
		category.BindStatic(&FExampleDebuggerCategory::MakeInstance);

		IGameplayDebugger::Get().RegisterCategory("Example", category,
			EGameplayDebuggerCategoryState::EnabledInGameAndSimulate, 5);
		IGameplayDebugger::Get().NotifyCategoriesChanged();
	}

	// Console Command
	{
		// Shareable: 둘다생성가능
		// Shared: 기존 포인터가 있는 상황에서 shared포인터 생성 시
		// SharedRef: shared 레퍼런스 생성 시
		ConsoleCommand = MakeShareable(new FExampleConsoleCommand());
	}

	// Propertiy Editor - StaticMeshActor
	{
		FOnGetDetailCustomizationInstance instance;
		instance.BindStatic(&FStaticMesh_Detail::MakeInstance);

		FPropertyEditorModule& prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		prop.RegisterCustomClassLayout(ACStaticMesh::StaticClass()->GetFName(), instance);
	}

	// ToolBar
	{
		FButtonCommand::Register();

		Extender = MakeShareable(new FExtender());

		FToolBarExtensionDelegate toolBar;
		toolBar.BindRaw(this, &FExampleModule::AddToolBar);

		Extender->AddToolBarExtension("Compile", EExtensionHook::Before, FButtonCommand::Get().Command, toolBar);

		FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);
	}

	FExampleStyle::Shutdown();
}

void FExampleModule::ShutdownModule()
{
	if (IGameplayDebugger::IsAvailable())
		IGameplayDebugger::Get().UnregisterCategory("Example");

	if (ConsoleCommand.IsValid())
		ConsoleCommand.Reset();
}

void FExampleModule::AddToolBar(FToolBarBuilder& InBuilder)
{
	FString name = TEXT("메시");

	InBuilder.AddSeparator();
	InBuilder.AddToolBarButton
	(
		FButtonCommand::Get().LoadMesh,
		"LoadMesh",
		FText::FromString(name),
		FText::FromString("Load Mesh Data"),
		FExampleStyle::Get()->ToolBar_LoadMesh_Icon
	);
}

#undef LOCTEXT_NAMESPACE