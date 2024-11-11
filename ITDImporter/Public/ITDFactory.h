#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "ITDFactory.generated.h"

UCLASS()
class ITDIMPORTER_API UITDFactory : public UFactory {
    GENERATED_BODY()

public:
    UITDFactory();

    virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
        const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;
};

