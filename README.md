# UE5 ITD Parser Plugin

3D 프린팅용 ITD 파일을 Unreal Engine 5에서 읽기 위한 UFactory 기반 커스텀 임포터 플러그인 프로젝트입니다.

> Portfolio position: Unreal Engine tooling, file-format parsing, geometry pipeline analysis.

## Problem

3D 프린팅/CAD 계열 데이터는 게임 엔진의 실시간 렌더링 파이프라인과 요구사항이 다릅니다. 특히 ITD 파일의 일부 구조는 Unreal Engine의 Static Mesh 변환 흐름과 충돌할 수 있고, Non-Manifold geometry 문제를 사전에 분석해야 합니다.

## What I Built

- ITD file parsing을 위한 vertex/polygon data structures
- Unreal Engine 5 `UFactory` 기반 custom asset importer skeleton
- Static Mesh 변환 흐름 분석
- ITD geometry와 UE mesh requirements 간 불일치 정리
- Non-Manifold edge case와 처리 전략 문서화

## My Role

개인 프로젝트로 파일 포맷 분석, C++ 구조체 설계, UFactory importer 골격 구현, 엔진 임포트 파이프라인 학습과 문제 분석을 수행했습니다. 완성 제품보다 “엔진이 요구하는 데이터 계약과 외부 파일 포맷의 차이를 어떻게 줄일지”를 탐구한 프로젝트입니다.

## Stack

| Area | Stack |
| --- | --- |
| Engine | Unreal Engine 5.2 / 5.3 |
| Language | C++ |
| Engine extension | UFactory, UCLASS, USTRUCT |
| Geometry | Static Mesh pipeline, file format parsing, Non-Manifold analysis |
| IDE | Visual Studio 2022 |

## Core Structure

```cpp
USTRUCT()
struct FITDVertex {
    GENERATED_BODY()
    FVector Position;
    FVector Normal;
    bool bHasNormal = false;
};

USTRUCT()
struct FITDPolygon {
    GENERATED_BODY()
    TArray<FITDVertex> Vertices;
    FVector PlaneNormal;
    float PlaneDistance;
    bool bHasPlane = false;
};
```

```cpp
UCLASS()
class ITDIMPORTER_API UITDFactory : public UFactory {
    GENERATED_BODY()
public:
    virtual UObject* FactoryCreateFile(
        UClass* InClass,
        UObject* InParent,
        FName InName,
        EObjectFlags Flags,
        const FString& Filename,
        const TCHAR* Parms,
        FFeedbackContext* Warn,
        bool& bOutOperationCanceled
    ) override;
};
```

## Run / Build

1. Create or open a UE5 C++ project.
2. Place this plugin under the project `Plugins/` directory.
3. Regenerate Visual Studio project files.
4. Build the editor target in Visual Studio 2022.
5. Enable the plugin in Unreal Editor and test ITD import flow.

## Validation Evidence

| Area | Evidence |
| --- | --- |
| Import extension point | `UFactory` custom importer skeleton implemented |
| Data modeling | ITD vertex/polygon structures defined for parser output |
| Engine contract analysis | Static Mesh conversion requirements reviewed |
| Geometry risk | Non-Manifold mismatch documented as a structural blocker |
| Scope clarity | Prototype/tooling project, not a production-ready importer |

## Non-Manifold Finding

ITD data can contain geometry that does not satisfy the manifold assumptions preferred by realtime rendering pipelines. The project documents possible mitigation paths: edge splitting, face reconstruction, pre-import validation, and user-selectable repair vs preserve options.

## Status

Prototype / learning project. The repository is useful as evidence of Unreal Engine extension work, C++ plugin structure, and geometry-pipeline problem analysis.
