#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ITDParser.generated.h"

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

UCLASS()
class ITDIMPORTER_API UITDParser : public UObject {
    GENERATED_BODY()

public:
    UITDParser();
    ~UITDParser();

    bool ParseFile(const FString& FilePath);
    const TArray<FITDPolygon>& GetPolygons() const { return Polygons; }

private:
    TArray<FITDPolygon> Polygons;
    void ParseLines(const TArray<FString>& Lines);
    void ParsePolygon(const TArray<FString>& Lines, int32& LineIndex);

};