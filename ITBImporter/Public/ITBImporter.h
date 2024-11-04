#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ITBImporter.generated.h"

UCLASS()
class UITBImporter : public UObject {
    GENERATED_BODY()

public:
    UStaticMesh* ImportITB(const FString& FilePath, const FString& MeshName, UObject* InParent, EObjectFlags Flags);
};
