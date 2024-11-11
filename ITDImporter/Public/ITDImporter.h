#pragma once

#include "Modules/ModuleManager.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ITDImporter.generated.h"


UCLASS()
class UITDImporter : public UObject {
    GENERATED_BODY()

public:
    UStaticMesh* ImportITD(const FString& FilePath, const FString& MeshName, UObject* InParent, EObjectFlags Flags);
};