using UnrealBuildTool;

public class UzumakiFighter : ModuleRules
{
    public UzumakiFighter(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "NetCore"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "GameplayTags",
            "DeveloperSettings",
            "EnhancedInput"
        });
    }
}
