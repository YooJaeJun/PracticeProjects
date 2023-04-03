using UnrealBuildTool;

public class Example : ModuleRules
{
	public Example(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(ModuleDirectory);

		PublicDependencyModuleNames.Add("Core");

		PrivateDependencyModuleNames.Add("CoreUObject");
		PrivateDependencyModuleNames.Add("Engine");
		PrivateDependencyModuleNames.Add("Slate");
		PrivateDependencyModuleNames.Add("SlateCore");
		PrivateDependencyModuleNames.Add("GameplayDebugger");
	}
}
