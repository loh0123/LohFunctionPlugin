// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LohFunctionPluginVoxel : ModuleRules
{
	public LohFunctionPluginVoxel(ReadOnlyTargetRules Target) : base(Target)
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
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"GameplayTags",
				"Core",
                //"GameplayAbilities",
                "JsonUtilities",

				"PhysicsCore",
				"StaticMeshDescription",
				"DeveloperSettings",

                "CoreUObject",
				"Engine",
				"RenderCore",
				"RHI",

                "LohFunctionPlugin",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "GameplayTags",
                "CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"RHI",

                "LohFunctionPlugin",
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
