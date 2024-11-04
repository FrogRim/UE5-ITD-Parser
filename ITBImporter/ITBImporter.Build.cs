// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ITBImporter : ModuleRules
{
	public ITBImporter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				"ITBImporter/Public"
            }
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
				"ITBImporter/Private"
            }
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
                "Core",
				"CoreUObject",
				"Engine",
				"AssetRegistry",
				"UnrealEd", // 에디터 모듈
				"MeshDescription",
				"StaticMeshDescription",
				"Slate",
				"SlateCore",
				"EditorFramework"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "Projects",
				"InputCore",
				"EditorStyle",
				"Json",
				"JsonUtilities"
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
