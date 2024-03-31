using UnrealBuildTool;
 
public class LohFunctionPluginMarching : ModuleRules
{
	public LohFunctionPluginMarching(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "GameplayTags" });
 
		PublicIncludePaths.AddRange(new string[] {"LohFunctionPluginMarching/Public"});
		PrivateIncludePaths.AddRange(new string[] {"LohFunctionPluginMarching/Private"});
	}
}