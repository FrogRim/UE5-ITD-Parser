#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "ITBFactory.generated.h"

UCLASS()
class UITBFactory : public UFactory {
    GENERATED_BODY()

public:
    UITBFactory();

    virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName,
        EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn,
        bool& bOutOperationCanceled) override;
};
