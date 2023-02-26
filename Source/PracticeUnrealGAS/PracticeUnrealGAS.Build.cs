// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PracticeUnrealGAS : ModuleRules
{
	public PracticeUnrealGAS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"HeadMountedDisplay",
			"EnhancedInput",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
		});
	}
}
