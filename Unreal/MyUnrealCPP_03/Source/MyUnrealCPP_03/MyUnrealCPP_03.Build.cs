using UnrealBuildTool;

public class MyUnrealCPP_03 : ModuleRules
{
	public MyUnrealCPP_03(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(ModuleDirectory);   // public �ܺο��� �� ���� �������� ����

        PublicDependencyModuleNames.Add("Core");

        PrivateDependencyModuleNames.Add("CoreUObject");
        PrivateDependencyModuleNames.Add("Engine");
        PrivateDependencyModuleNames.Add("InputCore");

        PrivateDependencyModuleNames.Add("HeadMountedDisplay");

        PrivateDependencyModuleNames.Add("Niagara");

        PrivateDependencyModuleNames.Add("AIModule");
        PrivateDependencyModuleNames.Add("GameplayTasks");
        PrivateDependencyModuleNames.Add("NavigationSystem");

        PrivateDependencyModuleNames.Add("SkeletonEditor");
        PrivateDependencyModuleNames.Add("ProceduralMeshComponent");
    }
}
