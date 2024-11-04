# Unreal Engine5 ITB Parser

# Step 1. 설치 및 테스트 빌드

## 1. 설치 과정

### 1.1. Unreal Engine 5 오픈소스 다운로드

- **GitHub에서 Unreal Engine 5 소스코드**를 다운로드하였습니다. 포크한 후, 레포지토리를 로컬에 클론하였습니다.
- 다운로드 후, **Setup.bat** 파일을 실행하여 엔진 빌드에 필요한 모든 서드파티 라이브러리와 툴을 설치하였습니다.
- **Setup.bat** 실행 후, **GenerateProjectFiles.bat** 파일을 실행하여 `.sln` 파일을 생성하였습니다.
- 이후, **Build.bat** 파일을 실행하여 Unreal Engine의 전체 빌드를 완료하였습니다.

### 1.2. Visual Studio 2022 설정

- **Visual Studio 2022**를 설치하고 Unreal Engine 빌드를 위해 필요한 확장 및 도구를 설치했습니다:
    - **게임 개발용 C++** 워크로드
    - **Windows 10 SDK**
- **GenerateProjectFiles.bat** 파일을 실행하여 `.sln` 파일을 생성하였습니다.

### 1.3. 솔루션 파일 빌드

- Visual Studio 2022에서 `.sln` 파일을 열고, **Development Editor** 설정으로 빌드를 진행했습니다.
- 빌드 타겟은 **Win64**로 설정하였습니다.

## 2. 빌드 오류와 해결 과정

### 2.1. MSB3073 Code 6 오류

빌드 과정에서 **MSB3073 code 6** 오류가 발생하였습니다. 이는 주로 `build.bat` 파일 실행 시 발생한 문제로 확인되었습니다.

### 2.1.1. 관리자 권한 실행

- Visual Studio를 **관리자 권한으로 실행**하여 빌드를 재시도하였습니다.
- 권한 문제로 인해 `build.bat` 파일이 제대로 실행되지 않는 상황을 해결하기 위해서였습니다.

### 2.1.2. Visual Studio 개발자 명령 프롬프트에서 수동 실행

- **Visual Studio Developer Command Prompt**를 관리자 권한으로 실행하고, 해당 경로에서 `build.bat` 파일을 수동으로 실행했습니다.
- 이를 통해 보다 상세한 오류 메시지를 확인할 수 있었습니다.

### 2.1.3. 환경 변수 설정 확인

- `build.bat` 파일 실행 시 필요한 **환경 변수(PATH)** 설정을 확인하였습니다.
    - Visual Studio 컴파일러와 도구들이 제대로 경로에 설정되어 있는지 점검하였습니다.
    - Unreal Engine 빌드에 필요한 도구와 라이브러리가 정확히 설정되어 있는지 확인하였습니다.

### 2.2. 추가적인 문제 해결

### 2.2.1. 경로 길이 제한 문제

- Windows에서는 경로 길이에 제한이 있어, 너무 긴 경로로 인해 빌드가 실패할 수 있습니다. 소스코드의 경로를 최대한 짧게 설정하여 경로 길이 제한 문제를 방지하였습니다.

### 2.2.2. 필요한 SDK 및 도구 업데이트

- 일부 경우 최신 SDK 및 도구가 설치되어 있지 않아 빌드가 실패하였습니다. **Visual Studio Installer**를 사용하여 모든 필요한 구성 요소와 SDK를 최신 버전으로 업데이트하였습니다.

### 2.2.3. `.NET Framework` 설치

- 빌드 스크립트 실행 중 `.NET Framework` 관련 오류가 발생하여, **.NET Framework 4.8**을 설치하여 문제를 해결하였습니다.

## 3. 결론 및 개선 사항

- **오류 해결을 위한 권한 문제와 환경 변수 설정**이 주요 원인으로 확인되었습니다. 이를 통해 빌드 과정이 성공적으로 완료되었습니다.
- **경로 길이 제한**과 **SDK 및 도구 업데이트**의 중요성을 깨달았습니다. 향후 빌드 시 이러한 부분을 미리 점검하는 것이 중요합니다.
- 향후 설치 및 빌드 시에는 **권한 문제**를 사전에 방지하기 위해 Visual Studio를 항상 관리자 권한으로 실행하고, **환경 변수**를 명확히 설정하는 것이 중요하다는 점을 깨달았습니다.

## 4. 기타 참고 사항

- Unreal Engine 5 빌드 과정에서 사용하는 **경로**에는 특수 문자나 공백이 없는 것이 좋습니다. 이는 스크립트 실행 실패를 방지하는 데 도움이 됩니다.
- **Visual Studio 설치 시 모든 필수 구성 요소와 SDK**를 설치하는 것이 중요합니다. 이를 통해 이후 빌드 과정에서 발생할 수 있는 문제를 최소화할 수 있습니다.
- 앞으로 Unreal Engine 5 설치 및 빌드와 관련된 내용을 노션에 기록하고, **빌드 스크립트 수정 사항 및 오류 해결 과정**을 지속적으로 업데이트할 예정입니다.

# Step 2. 소스 코드 수정 및 빌드

## **소스 코드 수정 및 빌드**

1. 원하는 부분의 소스 코드를 수정합니다. 주로 Engine 폴더 내의 파일들을 수정
2. 수정 후, GenerateProjectFiles.bat을 실행하여 프로젝트 파일을 다시 생성
3. UE5.sln 솔루션 파일을 Visual Studio에서 열고, "DevelopmentEditor + Win64 + UE5" 구성으로 빌드

## **변경사항 적용**(수정된 코드를 적용하려면)

1. 빌드가 완료되면 새로운 UnrealEditor.exe가 생성.
2. 이 새로운 에디터를 사용하여 프로젝트를 열면 수정된 코드가 적용.

## **주의사항**

- **버전 관리**: 수정사항을 Git 등의 버전 관리 시스템을 통해 관리하는 것이 좋습니다.
- **의존성 파일**: 코드 수정 후 의존성 파일에 변화가 있다면 Setup.bat을 다시 실행해야 할 수 있습니다[1](https://dlemrcnd.tistory.com/m/109).
- **플랫폼별 빌드**: 다른 플랫폼(예: Android)에 대한 변경사항을 적용하려면 해당 플랫폼용으로 추가 빌드가 필요할 수 있습니다
- **언리얼 테스트 어답터와 마켓플레이스에서 visual studio interaction tool을 설치해야한다**

# Step 3. 소스 코드 수정 및 빌드

**ITBImporter 플러그인 클래스 → 보다 유동적인 사용과 실전적용을 위해**

<aside>
💡

Unreal Engine 5 플러그인 개발을 위해 작성된 **ITBImporter** 플러그인의 세 가지 주요 클래스를 설명합니다: **ITBParser**, **ITBImporter**, **ITBImporterFactory**. 각 클래스는 서로 명확한 역할을 가지며, 파싱된 데이터를 Unreal Engine에서 사용 가능한 지오메트리로 변환하고 임포트하는 과정을 구성합니다.

</aside>

---

## **1. ITBParser**

**역할:** `.itb` 파일을 파싱하여 지오메트리 데이터를 추출하는 클래스입니다. 파일을 읽고, 텍스트를 파싱하며, 버텍스, 노멀, 폴리곤 정보를 추출하는 일을 합니다.

**주요 기능:**

- `.itb` 파일의 내용을 읽고 파싱합니다.
- 파일 내에서 객체, 버텍스, 폴리곤 등의 정보를 추출합니다.
- 파싱된 결과를 다른 클래스에서 사용할 수 있도록 제공하는 역할을 합니다.

**코드 주요 부분:**

- `ParseFile(const FString& FilePath)`: 파일을 읽고 파싱하는 메인 함수입니다.
- `Tokenize()` 및 `ParseTokens()`: 파일의 데이터를 토큰화하고 각 토큰을 파싱하여 의미 있는 정보로 변환합니다.
- `ParseObject()` 및 `ParsePolygon()`: 객체와 폴리곤 데이터를 파싱하여 필요한 정보를 추출합니다.

---

## **2. ITBImporter**

**역할:** `ITBParser`를 사용하여 파싱된 데이터를 바탕으로 Unreal Engine에서 사용할 수 있는 지오메트리를 생성합니다. `FMeshDescription`을 사용하여 `UStaticMesh`를 생성하며, StaticMesh 에셋을 Unreal Engine 에디터에 등록합니다.

**주요 기능:**

- **ITBParser**를 사용하여 `.itb` 파일을 파싱하고, 그 결과로부터 폴리곤과 버텍스 정보를 가져옵니다.
- `FMeshDescription`을 생성하고 버텍스, 버텍스 인스턴스, 폴리곤 등을 설정합니다.
- **StaticMesh**를 생성하고 MeshDescription을 적용하여 최종적으로 에셋으로 빌드하고 Unreal Engine 에디터에 등록합니다.

**코드 주요 부분:**

- `ImportITB(const FString& FilePath, const FString& MeshName, UObject* InParent, EObjectFlags Flags)`: `.itb` 파일을 파싱하고, 파싱된 데이터를 기반으로 StaticMesh를 생성하는 함수입니다.
- `FMeshDescription`과 `FStaticMeshAttributes`를 사용하여 버텍스 포지션 및 노멀을 설정합니다.
- `CreateMeshDescription()` 및 `CommitMeshDescription()`을 사용하여 StaticMesh에 MeshDescription을 적용하고 빌드합니다.

---

## **3. ITBImporterFactory**

**역할:** Unreal Engine의 **UFactory**를 상속하여 `.itb` 파일을 Unreal Engine 에디터에서 임포트할 수 있는 팩토리를 구현합니다. 에디터에서 파일을 임포트할 때 사용됩니다.

**주요 기능:**

- **UFactory**를 상속하여 Unreal Engine 에디터에서 `.itb` 파일을 임포트할 수 있도록 합니다.
- `FactoryCreateFile()` 메서드를 구현하여 **ITBImporter**를 사용해 `.itb` 파일을 파싱하고, StaticMesh를 생성하여 에디터에 등록합니다.
- **에셋 등록 및 로깅**: 성공 여부를 로깅하고 에셋을 등록하여 임포트된 결과를 에디터에서 사용할 수 있도록 합니다.

**코드 주요 부분:**

- `UITBImporterFactory()`: 팩토리 클래스의 생성자. 임포트 가능한 파일 형식 및 지원하는 클래스 설정을 담당합니다.
- `FactoryCreateFile()`: `.itb` 파일을 임포트하는 핵심 메서드로, **ITBImporter**를 호출하여 StaticMesh를 생성합니다.
- 임포트 후 성공 메시지 또는 에러 메시지를 출력하여 사용자에게 결과를 알립니다.

---

## **전체적인 흐름**

1. **ITBImporterFactory**
    - Unreal Engine의 `UFactory`를 상속하여 `.itb` 파일을 임포트할 수 있는 팩토리 클래스입니다.
    - 에디터에서 사용자가 `.itb` 파일을 임포트하면 `FactoryCreateFile()` 메서드가 호출됩니다.
    - 이 메서드에서 **ITBImporter**의 `ImportITB()` 함수를 호출하여 실제 임포트를 수행합니다.
2. **ITBImporter**
    - **ITBParser**를 사용하여 `.itb` 파일을 파싱합니다.
    - 파싱된 데이터를 기반으로 `FMeshDescription`을 생성하고, 버텍스와 폴리곤 정보를 설정합니다.
    - `CreateMeshDescription()`과 `CommitMeshDescription()`을 사용하여 `UStaticMesh`에 `MeshDescription`을 적용합니다.
    - StaticMesh를 빌드하고 에셋으로 등록합니다.
3. **ITBParser**
    - `.itb` 파일을 읽고 파싱하여 버텍스, 노멀, 폴리곤 데이터를 추출합니다.
    - 파싱된 데이터를 **ITBImporter**에서 사용할 수 있도록 제공합니다.

---

## 플로우차트

- **사용자**가 에디터에서 `.itb` 파일을 임포트합니다.
    - ↓
- **ITBImporterFactory**의 `FactoryCreateFile()` 메서드가 호출됩니다.
    - ↓
- **ITBImporterFactory**는 **ITBImporter**의 `ImportITB()` 함수를 호출합니다.
    - ↓
- **ITBImporter**는 **ITBParser**를 생성하고 `ParseFile()`을 호출하여 파일을 파싱합니다.
    - ↓
- **ITBParser**는 `.itb` 파일을 파싱하고 데이터를 추출합니다.
    - ↓
- **ITBImporter**는 파싱된 데이터를 사용하여 `FMeshDescription`을 생성하고 StaticMesh를 빌드합니다.
    - ↓
- **ITBImporter**는 생성된 StaticMesh를 반환하고, 에셋으로 등록합니다.
    - ↓
- **ITBImporterFactory**는 임포트된 StaticMesh를 에디터에 표시합니다.

---

## **노트 및 고려 사항**

- **에러 처리 및 로깅 강화**: 각 클래스에서 발생할 수 있는 오류에 대해 명확한 에러 메시지를 출력하도록 구현되어 있습니다.
- **메모리 관리**: Unreal Engine의 가비지 컬렉션 시스템을 고려하여 UObject 파생 클래스를 `NewObject<>()`를 사용하여 생성합니다.
- **코딩 컨벤션 준수**: Unreal Engine의 코딩 스타일을 따르도록 클래스명, 함수명, 변수명이 설정되어 있습니다.

이 세 가지 클래스를 이용해 ITBImporter 플러그인은 `.itb` 파일을 파싱하여 Unreal Engine 에셋으로 임포트하는 기능을 제공합니다. 이를 통해 `.itb` 형식의 모델 데이터를 UE5 환경에서 사용할 수 있습니다.

---

## 디렉토리 구조

```vbnet
YourProject/
├── ITB_Loader/                -> my project 
│   └── ITBImporter/
│       ├── ITBImporter.uplugin
│       ├── Source/
│       │   └── ITBImporter/
│       │       ├── ITBImporter.Build.cs
│       │       ├── Public/
│       │       │   ├── ITBImporterFactory.h
│       │       │   ├── ITBImporter.h
│       │       │   └── ITBParser.h
│       │       └── Private/
│       │           ├── ITBImporterFactory.cpp
│       │           ├── ITBImporter.cpp
│       │           └── ITBParser.cpp
│       └── Resources/
│           └── Icon,Resource etc..

```
