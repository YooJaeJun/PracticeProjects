#include "ExampleModule.h"
#include "ExampleDebuggerCategory.h"

#include "GameplayDebugger.h"

#define LOCTEXT_NAMESPACE "FExampleModule"
	
IMPLEMENT_MODULE(FExampleModule, Example)

void FExampleModule::StartupModule()
{
	IGameplayDebugger::FOnGetCategory category;
	category.BindStatic(&FExampleDebuggerCategory::MakeInstance);

	IGameplayDebugger::Get().RegisterCategory("Example", category, 
		EGameplayDebuggerCategoryState::EnabledInGameAndSimulate, 5);
	IGameplayDebugger::Get().NotifyCategoriesChanged();
}

void FExampleModule::ShutdownModule()
{
	if (IGameplayDebugger::IsAvailable())
		IGameplayDebugger::Get().UnregisterCategory("Example");
}

#undef LOCTEXT_NAMESPACE