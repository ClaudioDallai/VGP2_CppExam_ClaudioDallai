// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CppExamClaudioDallai : ModuleRules
{
	public CppExamClaudioDallai(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
