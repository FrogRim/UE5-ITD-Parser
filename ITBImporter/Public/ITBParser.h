#pragma once

#include "CoreMinimal.h"
#include "ITBParser.generated.h"

struct FITBVertex {
    FVector Position;
    FVector Normal;
};

struct FITBPolygon {
    TArray<FITBVertex> Vertices;
};

UCLASS()
class UITBParser : public UObject {
    GENERATED_BODY()

public:
    bool ParseFile(const FString& FilePath);

    const TArray<FITBPolygon>& GetPolygons() const { return Polygons; }

private:
    TArray<FITBPolygon> Polygons;

    void Tokenize(const FString& Data, TArray<FString>& Tokens);
    void ParseTokens(const TArray<FString>& Tokens);
    void ParseObject(const TArray<FString>& Tokens, int32& Index);
    void ParsePolygon(const TArray<FString>& Tokens, int32& Index);
    // 기타 필요한 파싱 함수들...
};
