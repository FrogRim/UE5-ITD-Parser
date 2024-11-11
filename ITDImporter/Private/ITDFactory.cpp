#include "ITDImporter/Public/ITDFactory.h"
#include "ITDImporter/Public/ITDImporter.h"
#include "Engine/StaticMesh.h"
#include "EditorFramework/AssetImportData.h"


UITDFactory::UITDFactory() {
    bEditorImport = true;
    bText = true;
    Formats.Add(TEXT("itd;ITD Model"));
    SupportedClass = UStaticMesh::StaticClass();
}

UObject* UITDFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName,
    EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn,
    bool& bOutOperationCanceled) {
    // ITDImporter를 사용하여 파일 임포트
    UITDImporter* Importer = NewObject<UITDImporter>();
    UStaticMesh* StaticMesh = Importer->ImportITD(Filename, InName.ToString(), InParent, Flags);

    if (StaticMesh) {
        // 임포트 데이터 설정
        StaticMesh->AssetImportData->Update(Filename);

        // 임포트 성공 메시지
        Warn->Logf(ELogVerbosity::Display, TEXT("Successfully imported ITD file: %s"), *Filename);

        return StaticMesh;
    }
    else {
        // 임포트 실패 메시지
        Warn->Logf(ELogVerbosity::Error, TEXT("Failed to import ITD file: %s"), *Filename);
        return nullptr;
    }
}