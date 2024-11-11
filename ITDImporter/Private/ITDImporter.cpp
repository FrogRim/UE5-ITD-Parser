#include "ITDImporter/Public/ITDImporter.h"
#include "ITDImporter/Public/ITDParser.h"
#include "MeshDescription.h"
#include "StaticMeshAttributes.h"
#include "Runtime/AssetRegistry/Public/AssetRegistry/AssetRegistryModule.h"
#include "Engine/StaticMesh.h"
#include "UObject/Package.h"
#include "Misc/PackageName.h"
#include "StaticMeshOperations.h"
#include "StaticMeshAttributes.h"


UStaticMesh* UITDImporter::ImportITD(const FString& FilePath, const FString& MeshName, UObject* InParent, EObjectFlags Flags) {
    // ITDParser를 사용하여 파일 파싱
    UITDParser* Parser = NewObject<UITDParser>(InParent);
    if (!Parser) {
        UE_LOG(LogTemp, Error, TEXT("Failed to create ITDParser object"));
        return nullptr;
    }

    // ITD 파일 파싱
    if (!Parser->ParseFile(FilePath)) {
        UE_LOG(LogTemp, Error, TEXT("Failed to parse ITD file: %s"), *FilePath);
        return nullptr;
    }

    // StaticMesh 생성
    UStaticMesh* StaticMesh = NewObject<UStaticMesh>(InParent, *MeshName, Flags);
    if (!StaticMesh) {
        UE_LOG(LogTemp, Error, TEXT("Failed to create StaticMesh object"));
        Parser->RemoveFromRoot(); // StaticMesh 생성 실패 시 해제
        return nullptr;
    }

    // StaticMesh 설정
    FStaticMeshSourceModel& SourceModel = StaticMesh->AddSourceModel();
    SourceModel.BuildSettings.bRecomputeNormals = false;
    SourceModel.BuildSettings.bRecomputeTangents = false;

    // MeshDescription 생성 및 설정
    FMeshDescription* MeshDesc = StaticMesh->CreateMeshDescription(0);
    if (!MeshDesc) {
        UE_LOG(LogTemp, Error, TEXT("Failed to create MeshDescription for StaticMesh."));
        Parser->RemoveFromRoot(); // MeshDescription 생성 실패 시 해제
        return nullptr;
    }

    // MeshDescription 초기화
    *MeshDesc = FMeshDescription();

    // 어트리뷰트 등록 및 초기화
    FStaticMeshAttributes MeshAttributes(*MeshDesc);
    MeshAttributes.Register();

    // 어트리뷰트 참조 생성 (버텍스, 버텍스 인스턴스, 폴리곤 그룹)
    TVertexAttributesRef<FVector3f> VertexPositions = MeshAttributes.GetVertexPositions();
    TVertexInstanceAttributesRef<FVector3f> Normals = MeshAttributes.GetVertexInstanceNormals();
    TVertexInstanceAttributesRef<FVector2f> UVs = MeshAttributes.GetVertexInstanceUVs();
    TPolygonGroupAttributesRef<FName> PolygonGroupNames = MeshAttributes.GetPolygonGroupMaterialSlotNames();

    // 폴리곤 그룹 생성
    FPolygonGroupID PolygonGroupID = MeshDesc->CreatePolygonGroup();
    PolygonGroupNames[PolygonGroupID] = FName("Default");

    // 버텍스 위치와 ID 매핑 -> 버텍스 중복 생성 방지 및 재사용
    TMap<FVector, FVertexID> VertexPositionToIDMap;

    // 폴리곤별로 메시 생성
    for (const FITDPolygon& PolygonData : Parser->GetPolygons()) 
    {

        TArray<FVertexInstanceID> VertexInstanceIDs;
        UE_LOG(LogTemp, Warning, TEXT("1. polygon vertice num: %d"), PolygonData.Vertices.Num());

        for (const FITDVertex& VertexData : PolygonData.Vertices) 
        {

            // 버텍스 생성
            FVertexID VertexID;

            if (VertexPositionToIDMap.Contains(VertexData.Position))
            {
                // 이미 생성된 버텍스 재사용
                VertexID = VertexPositionToIDMap[VertexData.Position];
            }
            else
            {
                // 버텍스 생성
                VertexID = MeshDesc->CreateVertex();
                VertexPositions[VertexID] = FVector3f(VertexData.Position);
                VertexPositionToIDMap.Add(VertexData.Position, VertexID);
            }

            // 버텍스 인스턴스 생성
            FVertexInstanceID VertexInstanceID = MeshDesc->CreateVertexInstance(VertexID);

            // 노멀 설정
            if (VertexData.bHasNormal) 
            {
                Normals[VertexInstanceID] = FVector3f(VertexData.Normal);
            }
            else 
            {
                Normals[VertexInstanceID] = FVector3f::ZeroVector; // 기본값 설정
            }

            // UV 설정
            UVs.Set(VertexInstanceID, 0, FVector2f(0.0f, 0.0f));

            VertexInstanceIDs.Add(VertexInstanceID);
        }

        UE_LOG(LogTemp, Warning, TEXT("vertex instance num by polygon : %d"), VertexInstanceIDs.Num());
        if (VertexInstanceIDs.Num() >=3)
        {
	    // 폴리곤 생성
	    MeshDesc->CreatePolygon(PolygonGroupID, VertexInstanceIDs);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Polygon have 3 vertices"));
         
        }
        
    }

    // 노멀과 탄젠트 계산
    FStaticMeshOperations::ComputeTangentsAndNormals(
        *MeshDesc,
	EComputeNTBsFlags::Normals | EComputeNTBsFlags::Tangents
    );
    

    // 메시 데이터의 유효성 수동 검사
    if (MeshDesc->Vertices().Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("MeshDescription have not vertex"));
        return nullptr;
    }

    if (MeshDesc->Polygons().Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("MeshDescription에 have not polygon"));
        return nullptr;
    }

    StaticMesh->CommitMeshDescription(0);

    // StaticMesh 빌드
    StaticMesh->Build(false);
    StaticMesh->MarkPackageDirty();

    // 에셋 등록
    FAssetRegistryModule::AssetCreated(StaticMesh);

    Parser = nullptr;

    return StaticMesh;
}

//IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, ITDImporter, "ITDImporter");
IMPLEMENT_MODULE(FDefaultModuleImpl, ITDImporter);