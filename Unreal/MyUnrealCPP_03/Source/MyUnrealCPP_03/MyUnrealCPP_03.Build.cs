using UnrealBuildTool;

public class MyUnrealCPP_03 : ModuleRules
{
	public MyUnrealCPP_03(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(ModuleDirectory);   // public 외부에서 이 폴더 기준으로 접근

        PublicDependencyModuleNames.Add("Core");

        PrivateDependencyModuleNames.Add("CoreUObject");
        PrivateDependencyModuleNames.Add("Engine");
        PrivateDependencyModuleNames.Add("InputCore");
        PrivateDependencyModuleNames.Add("HeadMountedDisplay");
        PrivateDependencyModuleNames.Add("NavigationSystem");
        PrivateDependencyModuleNames.Add("AIModule");
    }
}
