#include "ExampleModule.h"
#include "ExampleDebuggerCategory.h"
#include "ExampleConsoleCommand.h"
#include "StaticMesh_Detail.h"

#include "CStaticMesh.h"

#include "GameplayDebugger.h"

#define LOCTEXT_NAMESPACE "FExampleModule"
	
IMPLEMENT_MODULE(FExampleModule, Example)

void FExampleModule::StartupModule()
{
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
		// Shareable: �Ѵٻ�������
		// Shared: ���� �����Ͱ� �ִ� ��Ȳ���� shared������ ���� ��
		// SharedRef: shared ���۷��� ���� ��
		ConsoleCommand = MakeShareable(new FExampleConsoleCommand());
	}

	// Propertiy Editor - StaticMeshActor
	{
		FOnGetDetailCustomizationInstance instance;
		instance.BindStatic(&FStaticMesh_Detail::MakeInstance);

		FPropertyEditorModule& prop = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		prop.RegisterCustomClassLayout(ACStaticMesh::StaticClass()->GetFName(), instance);
	}
}

void FExampleModule::ShutdownModule()
{
	if (IGameplayDebugger::IsAvailable())
		IGameplayDebugger::Get().UnregisterCategory("Example");

	if (ConsoleCommand.IsValid())
		ConsoleCommand.Reset();
}

#undef LOCTEXT_NAMESPACE