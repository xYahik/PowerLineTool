// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PowerLineTool : ModuleRules
{
	public PowerLineTool(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG" });

		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(new string[]
			{
				"Blutility",
				"EditorScriptingUtilities",
				"UMGEditor",
				"EditorFramework",
				"UnrealEd",
				"LevelEditor"
			});
		}
    }
}
