#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FExampleModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedPtr<class FExampleConsoleCommand> ConsoleCommand;

private:
	TSharedPtr<FExtender> Extender;

private:
	void AddToolBar(class FToolBarBuilder& InBuilder);
};
