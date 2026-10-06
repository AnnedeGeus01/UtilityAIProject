#pragma once

#include "CoreMinimal.h"
#include "UtilityAIAction.h"
#include "UtilityAIDebugTypes.generated.h"

USTRUCT(BlueprintType)
struct FUtilityAIConsiderationDebugData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FName Name;

    UPROPERTY(BlueprintReadOnly)
    float InputValue = 0.0f;

    UPROPERTY(BlueprintReadOnly)
    float Score = 0.0f;
};

USTRUCT(BlueprintType)
struct FUtilityAIActionDebugData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FName Name;

    UPROPERTY(BlueprintReadOnly)
    float Utility = 0.0f;

    UPROPERTY(BlueprintReadOnly)
    bool bSelected = false;

    UPROPERTY(BlueprintReadOnly)
    EUtilityAICombinationMethod CombinationMethod =
        EUtilityAICombinationMethod::Multiply;

    UPROPERTY(BlueprintReadOnly)
    TArray<FUtilityAIConsiderationDebugData> Considerations;
};
