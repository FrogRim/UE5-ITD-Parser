#include "ITBImporter.h"
#include "ITBParser.h"
#include "MeshDescription.h"
#include "StaticMeshAttributes.h"
#include "Runtime/AssetRegistry/Public/AssetRegistry/AssetRegistryModule.h"
#include "Engine/StaticMesh.h"
#include "UObject/Package.h"
#include "Misc/PackageName.h"

UStaticMesh* UITBImporter::ImportITB(const FString& FilePath, const FString& MeshName, UObject* InParent, EObjectFlags Flags) {
    // ITBParser를 사용하여 파일 파싱
    UITBParser* Parser = NewObject<UITBParser>();
    if (!Parser->ParseFile(FilePath)) {
        UE_LOG(LogTemp, Error, TEXT("Failed to parse ITB file: %s"), *FilePath);
        return nullptr;
    }

    const TArray<FITBPolygon>& Polygons = Parser->GetPolygons();

    // MeshDescription 생성
    FMeshDescription MeshDescription;
    FStaticMeshAttributes Attributes(MeshDescription);
    Attributes.Register();

    // 버텍스 및 버텍스 인스턴스 생성
    TMap<FVector, FVertexID> VertexIDMap;

    for (const FITBPolygon& Poly : Polygons) {
        TArray<FVertexInstanceID> VertexInstanceIDs;
        for (const FITBVertex& Vert : Poly.Vertices) {
            FVertexID VertexID;
            if (VertexIDMap.Contains(Vert.Position)) {
                VertexID = VertexIDMap[Vert.Position];
            }
            else {
                VertexID = MeshDescription.CreateVertex();
                Attributes.GetVertexPositions()[VertexID] = FVector3f(Vert.Position);
                VertexIDMap.Add(Vert.Position, VertexID);
            }

            FVertexInstanceID VertexInstanceID = MeshDescription.CreateVertexInstance(VertexID);
            Attributes.GetVertexInstanceNormals()[VertexInstanceID] = FVector3f(Vert.Normal);

            VertexInstanceIDs.Add(VertexInstanceID);
        }

        // 폴리곤 생성
        if (VertexInstanceIDs.Num() >= 3) {
            MeshDescription.CreatePolygon(FPolygonGroupID(0), VertexInstanceIDs);
        }
    }

    // StaticMesh 생성
    UStaticMesh* StaticMesh = NewObject<UStaticMesh>(InParent, *MeshName, Flags);
    if (StaticMesh) {
        // BuildSettings 설정
        FStaticMeshSourceModel& SourceModel = StaticMesh->AddSourceModel();
        SourceModel.BuildSettings.bRecomputeNormals = false;
        SourceModel.BuildSettings.bRecomputeTangents = false;

        // LODGroup 설정 (필요한 경우)
        // StaticMesh->SetLODGroup(YourLODGroup);

        // MeshDescription 생성 및 설정
        FMeshDescription* MeshDesc = StaticMesh->CreateMeshDescription(0);
        if (MeshDesc) {
            *MeshDesc = MoveTemp(MeshDescription);
            StaticMesh->CommitMeshDescription(0);

            // StaticMesh 빌드
            StaticMesh->Build(false);
            StaticMesh->MarkPackageDirty();
        }
        else {
            UE_LOG(LogTemp, Error, TEXT("Failed to create MeshDescription for StaticMesh."));
            return nullptr;
        }
    }

    // 에셋 등록
    FAssetRegistryModule::AssetCreated(StaticMesh);

    return StaticMesh;
}
