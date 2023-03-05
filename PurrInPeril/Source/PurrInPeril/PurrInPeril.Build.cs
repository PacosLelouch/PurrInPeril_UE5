// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PurrInPeril : ModuleRules
{
	public PurrInPeril(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"Slate", 
			"SlateCore", 
			"UMG", 
			"HeadMountedDisplay", 
			"EnhancedInput", 
			"Json", 
			"JsonUtilities",
			"AIModule", 
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PrivateIncludePaths.AddRange(new string[]
		{
			"PurrInPeril",
			"PurrInPeril/MainLevel", 
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
