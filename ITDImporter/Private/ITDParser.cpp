#include "ITDImporter/Public/ITDParser.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

UITDParser::UITDParser() {
    UE_LOG(LogTemp, Warning, TEXT("UITDParser Constructor called"));
}

UITDParser::~UITDParser() {
    UE_LOG(LogTemp, Warning, TEXT("UITDParser Destructor called"));
}

bool UITDParser::ParseFile(const FString& FilePath) {
    FString FileContent;
    if (!FFileHelper::LoadFileToString(FileContent, *FilePath)) {
        UE_LOG(LogTemp, Error, TEXT("Failed to load file: %s"), *FilePath);
        return false;
    }

    TArray<FString> Lines;
    FileContent.ParseIntoArrayLines(Lines);

    ParseLines(Lines);

    return true;
}

// Lines 배열을 사용하여 Polygons 데이터 구성
void UITDParser::ParseLines(const TArray<FString>& Lines) {
    int32 LineIndex = 0;
    while (LineIndex < Lines.Num()) {
        FString Line = Lines[LineIndex].TrimStartAndEnd();

        if (Line.StartsWith(TEXT("[POLYGON"))) {
            ParsePolygon(Lines, LineIndex);
            UE_LOG(LogTemp, Warning, TEXT("**********************StartPasing Polygon******************"));
        }
        else {
            LineIndex++;
        }
    }
}

void UITDParser::ParsePolygon(const TArray<FString>& Lines, int32& LineIndex) {
    // POLYGON 라인 파싱
    FString Line = Lines[LineIndex].TrimStartAndEnd();

    FITDPolygon NewPolygon;

    // 버텍스 수 및 PLANE 파싱
    // 예: "POLYGON [PLANE 0 0 1 -0.006485] 3"
    TArray<FString> Tokens;
    Line.ParseIntoArrayWS(Tokens);

    int32 VertexCount = 0;

    int32 PlaneStartIndex = Line.Find(TEXT("[PLANE"));
    if (PlaneStartIndex != INDEX_NONE)
    {
        int32 PlaneEndIndex = Line.Find(TEXT("]"), ESearchCase::IgnoreCase, ESearchDir::FromStart, PlaneStartIndex);
        if (PlaneEndIndex != INDEX_NONE)
        {
	    // PLANE 파싱
            FString PlaneData = Line.Mid(PlaneStartIndex + 1, PlaneEndIndex - PlaneStartIndex - 1);
            PlaneData.RemoveFromStart(TEXT("PLANE "));
            TArray<FString> PlaneComponents;
            PlaneData.ParseIntoArrayWS(PlaneComponents);;

	    // 평면 데이터 파싱
            if (PlaneComponents.Num() == 4) {
                NewPolygon.PlaneNormal.X = FCString::Atod(*PlaneComponents[0]);
                NewPolygon.PlaneNormal.Y = FCString::Atod(*PlaneComponents[1]);
                NewPolygon.PlaneNormal.Z = FCString::Atod(*PlaneComponents[2]);
                NewPolygon.PlaneDistance = FCString::Atod(*PlaneComponents[3]);
                NewPolygon.bHasPlane = true;

                
            }
	    // 평면 데이터가 4개가 아닌 경우 경고 출력
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Invalid plane data: %s"), *PlaneData);
            }
        }
	// 평면 데이터의 끝을 찾지 못한 경우 경고 출력
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to find end of plane data: %s"), *Line);
            NewPolygon.bHasPlane = false;
        }
    }

    // 버텍스 수 파싱 (마지막 토큰)
    if (Tokens.Num() >= 2) {
        FString LastToken = Tokens.Last();
        VertexCount = FCString::Atoi(*LastToken);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to parse vertex count: %s"), *Line);
        return;
    }

    LineIndex++; // 다음 라인으로 이동

    // 버텍스 파싱
    for (int32 i = 0; i < VertexCount; ++i) {
        if (LineIndex >= Lines.Num()) {
            UE_LOG(LogTemp, Warning, TEXT("Expected more lines for vertices, but reached end of file."));
            break;
        }

        Line = Lines[LineIndex].TrimStartAndEnd();
        

        FITDVertex NewVertex;

        if (Line.StartsWith(TEXT("[[NORMAL"))) {
            // 노멀과 위치 좌표 파싱
            // 예: "[[NORMAL nx ny nz] x y z]"
            UE_LOG(LogTemp, Log, TEXT("Vertex with normal detected."));
            FString Content = Line.Mid(2, Line.Len() - 3); // 처음의 "[["와 끝의 "]" 제거
            TArray<FString> VertexTokens;
            Content.ParseIntoArrayWS(VertexTokens);

            if (VertexTokens.Num() >= 7 && VertexTokens[0] == TEXT("NORMAL")) {
                // 노멀 파싱
                NewVertex.Normal.X = FCString::Atod(*VertexTokens[1]);
                NewVertex.Normal.Y = FCString::Atod(*VertexTokens[2]);
                NewVertex.Normal.Z = FCString::Atod(*VertexTokens[3]);
                NewVertex.bHasNormal = true;

                // 위치 좌표 파싱
                NewVertex.Position.X = FCString::Atod(*VertexTokens[4]);
                NewVertex.Position.Y = FCString::Atod(*VertexTokens[5]);
                NewVertex.Position.Z = FCString::Atod(*VertexTokens[6]);
            }
            else {
                UE_LOG(LogTemp, Warning, TEXT("Invalid vertex format with NORMAL: %s"), *Line);
            }
        }
        else if (Line.StartsWith(TEXT("[")) && Line.EndsWith(TEXT("]"))) {
            // 위치 좌표만 있는 경우
            FString Content = Line.Mid(2, Line.Len() - 4); // "["와 "]" 제거
            TArray<FString> VertexTokens;
            Content.ParseIntoArrayWS(VertexTokens);

            if (VertexTokens.Num() >= 3) {
                // 위치 좌표 파싱
                NewVertex.Position.X = FCString::Atod(*VertexTokens[0]);
                NewVertex.Position.Y = FCString::Atod(*VertexTokens[1]);
                NewVertex.Position.Z = FCString::Atod(*VertexTokens[2]);
            }
            else {
                UE_LOG(LogTemp, Warning, TEXT("Invalid vertex format: %s"), *Line);
            }
        }
        else {
            UE_LOG(LogTemp, Warning, TEXT("Unknown vertex format: %s"), *Line);
            LineIndex++;
            i--; // 버텍스 수를 맞추기 위해 인덱스 감소
            continue;
        }
        // 파싱된 버텍스 정보 출력
        UE_LOG(LogTemp, Warning, TEXT("Parsed Vertex Position: (%f, %f, %f)"), NewVertex.Position.X, NewVertex.Position.Y, NewVertex.Position.Z);
        if (NewVertex.bHasNormal) {
            UE_LOG(LogTemp, Warning, TEXT("Parsed Vertex Normal: (%f, %f, %f)"), NewVertex.Normal.X, NewVertex.Normal.Y, NewVertex.Normal.Z);
        }

        NewPolygon.Vertices.Add(NewVertex);
        UE_LOG(LogTemp, Warning, TEXT("Parsed Vertex: Position=(%f, %f, %f), HasNormal=%d"), NewVertex.Position.X, NewVertex.Position.Y, NewVertex.Position.Z, NewVertex.bHasNormal);
        LineIndex++;
    }

    // 폴리곤 추가
    if (NewPolygon.Vertices.Num() > 0) {
        Polygons.Add(NewPolygon);
        UE_LOG(LogTemp, Warning, TEXT("Added Polygon with %d vertices"), NewPolygon.Vertices.Num());
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Polygon has no vertices and will not be added."));
    }

    // POLYGON 블록의 끝까지 이동 (예: "]")
    while (LineIndex < Lines.Num()) {
        Line = Lines[LineIndex].TrimStartAndEnd();
        if (Line == TEXT("]")) {
            LineIndex++; // "]" 스킵
            break;
        }
        else {
            LineIndex++;
        }
    }
}
