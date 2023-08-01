using UnrealBuildTool;

public class MyUnrealCPP_04 : ModuleRules
{
	public MyUnrealCPP_04(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(ModuleDirectory);
	
		PublicDependencyModuleNames.Add("Core");
		PublicDependencyModuleNames.Add("CoreUObject");
		PublicDependencyModuleNames.Add("Engine");
		PublicDependencyModuleNames.Add("InputCore");
		PublicDependencyModuleNames.Add("Niagara");
		PublicDependencyModuleNames.Add("AIModule");
		PublicDependencyModuleNames.Add("GameplayTasks");
        PublicDependencyModuleNames.Add("NavigationSystem");
	}
}
