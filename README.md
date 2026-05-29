# UE5 ITD Parser Plugin

3D 프린팅용 ITD 파일을 Unreal Engine 5에서 읽기 위한 UFactory 기반 custom importer prototype입니다.

> Portfolio position: Unreal Engine tooling, file-format parsing, geometry pipeline analysis.

## Why This Problem

3D 프린팅/CAD 계열 데이터는 실시간 렌더링 엔진이 기대하는 mesh contract와 다르게 만들어질 수 있습니다. 특히 ITD 파일의 polygon/plane/vertex 구조는 Unreal Engine의 Static Mesh 변환 흐름과 바로 맞지 않을 수 있고, Non-Manifold geometry는 import 단계에서 시각적으로 깨지거나 충돌/렌더링 파이프라인에서 문제가 됩니다.

이 프로젝트의 핵심은 “파일을 읽었다”가 아니라, **외부 파일 포맷과 엔진 내부 asset contract 사이의 차이를 어떻게 줄일지 분석한 것**입니다.

## Method

```mermaid
flowchart LR
    A[ITD file] --> B[parser structures]
    B --> C[UFactory import entry]
    C --> D[mesh contract analysis]
    D --> E[Non-Manifold risk list]
    E --> F[repair vs preserve strategy]
```

## What I Built

- ITD file parsing을 위한 vertex/polygon data structures
- Unreal Engine 5 `UFactory` 기반 custom asset importer skeleton
- Static Mesh 변환 흐름 분석
- ITD geometry와 UE mesh requirements 간 불일치 정리
- Non-Manifold edge case와 처리 전략 문서화

## My Role

개인 프로젝트로 파일 포맷 분석, C++ 구조체 설계, UFactory importer 골격 구현, 엔진 import pipeline 학습과 문제 분석을 수행했습니다. 완성 제품보다 “엔진이 요구하는 데이터 계약과 외부 파일 포맷의 차이를 어떻게 줄일지”를 탐구한 프로젝트입니다.

## Engineering Decisions

| Decision | Alternatives Considered | Why | Tradeoff |
| --- | --- | --- | --- |
| UFactory extension point 사용 | 런타임 parser만 작성 | UE Editor import flow와 연결되는 실제 엔진 확장 지점을 학습할 수 있음 | Editor build/setup 의존성이 생김 |
| parser data structure를 먼저 분리 | 파일을 읽자마자 Static Mesh 생성 | 포맷 이해와 mesh 변환 문제를 분리해야 Non-Manifold 문제를 설명할 수 있음 | end-to-end demo 완성은 늦어짐 |
| Non-Manifold를 명시적 risk로 문서화 | importer 성공처럼 포장 | 실시간 엔진 contract와 3D printing geometry의 차이를 숨기지 않는 것이 더 신뢰도 높음 | 프로젝트가 prototype으로 보임 |
| repair vs preserve 전략을 남김 | 임의 자동 보정 | 데이터 손실 가능성이 있어 사용자가 선택해야 하는 영역이 있음 | UX/옵션 설계가 추가로 필요 |

## AI-Assisted Engineering Record

AI는 포맷/엔진 용어를 정리하고, Non-Manifold 처리 후보를 비교하는 데 사용했습니다. 제안된 “자동으로 mesh를 고친다”는 식의 단정은 받아들이지 않았고, edge split, face reconstruction, pre-import validation, preserve mode처럼 선택지와 tradeoff가 드러나는 방식으로 정리했습니다.

이 저장소에서 AI 사용은 구현 책임을 대체하지 않습니다. 공개적으로 주장하는 범위는 C++ importer skeleton, parser-oriented structs, UE mesh contract analysis, documented risk로 제한합니다.

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
5. Enable the plugin in Unreal Editor and test ITD import flow with a public-safe sample file.

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

## Known Limits

- This is a prototype/learning project, not a production-ready importer.
- Public README does not claim successful import of every ITD variant.
- Real screenshots or test assets should be added only when they are generated from public-safe sample files.
- Future proof should include editor build logs, sample ITD fixtures, and before/after mesh validation.
