// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ITDImporter : ModuleRules
{
	public ITDImporter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				"ITDImporter/Public"
            }
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
                "ITDImporter/Private",
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
                "Core",
				"CoreUObject",
				"Engine",
				"UnrealEd", // 에디터 모듈인 경우 필요
				"AssetTools", // 에셋 관련 작업을 위한 모듈
				"Slate",
				"SlateCore",
				"EditorScriptingUtilities", // 필요에 따라 추가
                "EditorStyle", // 필요에 따라 추가
				"AssetRegistry",
				"StaticMeshDescription",
                "MeshDescription", // 이 모듈을 추가하세요
                
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Slate",
				"SlateCore",
                "Projects",
				"UnrealEd",
				"EditorFramework",
                "AssetTools", // 에셋 관련 작업을 위해 필요하다면 추가
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
