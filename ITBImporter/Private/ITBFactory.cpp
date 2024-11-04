#include "ITBFactory.h"
#include "ITBImporter.h"
#include "Engine/StaticMesh.h"
#include "EditorFramework/AssetImportData.h"

UITBFactory::UITBFactory() {
    bEditorImport = true;
    bText = true;
    Formats.Add(TEXT("itb;ITB Model"));
    SupportedClass = UStaticMesh::StaticClass();
}

UObject* UITBFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName,
    EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn,
    bool& bOutOperationCanceled) {
    // ITBImporter를 사용하여 파일 임포트
    UITBImporter* Importer = NewObject<UITBImporter>();
    UStaticMesh* StaticMesh = Importer->ImportITB(Filename, InName.ToString(), InParent, Flags);

    if (StaticMesh) {
        // 임포트 데이터 설정
        StaticMesh->AssetImportData->Update(Filename);

        // 임포트 성공 메시지
        Warn->Logf(ELogVerbosity::Display, TEXT("Successfully imported ITB file: %s"), *Filename);

        return StaticMesh;
    }
    else {
        // 임포트 실패 메시지
        Warn->Logf(ELogVerbosity::Error, TEXT("Failed to import ITB file: %s"), *Filename);
        return nullptr;
    }
}
