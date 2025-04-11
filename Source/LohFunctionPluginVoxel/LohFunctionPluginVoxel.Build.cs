using UnrealBuildTool;

public class LohFunctionPluginVoxel : ModuleRules
{
	public LohFunctionPluginVoxel(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "LohFunctionPlugin"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"GeometryFramework",
				"GeometryCore",
				"LohFunctionPlugin",
				"GameplayTags"
			}
		);
	}
}