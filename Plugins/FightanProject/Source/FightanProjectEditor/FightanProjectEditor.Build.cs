// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FightanProjectEditor : ModuleRules
{
    public FightanProjectEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
				// ... add public include paths required here ...
			}
            );


        PrivateIncludePaths.AddRange(
            new string[] {
				// ... add other private include paths required here ...
                "FightanProjectEditor/Private",
                "FightanProjectEditor/Private/AssetTools",
                "FightanProjectEditor/Private/Factories",
                "FightanProjectEditor/Private/Shared",
                "FightanProjectEditor/Private/Styles",
                "FightanProjectEditor/Private/Toolkits",
                "FightanProjectEditor/Private/Widgets",
            }
            );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "FightanProject",
                "SlateCore",
                "Projects"
				// ... add other public dependencies that you statically link with here ...
			}
            );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "InputCore",
                "UnrealEd",
                "LevelEditor",
                "Projects"
				// ... add private dependencies that you statically link with here ...	
			}
            );


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
				// ... add any modules that your module loads dynamically here ...
			}
            );
    }
}
