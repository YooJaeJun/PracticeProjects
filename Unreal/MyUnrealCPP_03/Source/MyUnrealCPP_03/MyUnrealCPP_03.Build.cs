// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyUnrealCPP_03 : ModuleRules
{
	public MyUnrealCPP_03(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule" });
    }
}
