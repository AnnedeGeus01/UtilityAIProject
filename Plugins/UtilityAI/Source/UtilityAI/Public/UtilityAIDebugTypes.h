#pragma once

#include "CoreMinimal.h"
#include "UtilityAIAction.h"
#include "UtilityAIDebugTypes.generated.h"

/**
 * Stores debug information for a single consideration.
 */
USTRUCT(BlueprintType)
struct FUtilityAIConsiderationDebugData
{
    GENERATED_BODY()

    /** Name of the consideration. */
    UPROPERTY(BlueprintReadOnly)
    FName Name;

    /** Raw input value received by the consideration. */
    UPROPERTY(BlueprintReadOnly)
    float InputValue = 0.0f;

    /** Output score produced by the consideration. */
    UPROPERTY(BlueprintReadOnly)
    float Score = 0.0f;
};

/**
 * Stores debug information for an action and its considerations.
 */
USTRUCT(BlueprintType)
struct FUtilityAIActionDebugData
{
    GENERATED_BODY()

    /** Name of the action. */
    UPROPERTY(BlueprintReadOnly)
    FName Name;

    /** Combined utility score of the action. */
    UPROPERTY(BlueprintReadOnly)
    float Utility = 0.0f;

    /** Indicates whether the action was selected. */
    UPROPERTY(BlueprintReadOnly)
    bool bSelected = false;

    /** Method used to combine consideration scores. */
    UPROPERTY(BlueprintReadOnly)
    EUtilityAICombinationMethod CombinationMethod =
        EUtilityAICombinationMethod::Multiply;

    /** Debug data for the action's considerations. */
    UPROPERTY(BlueprintReadOnly)
    TArray<FUtilityAIConsiderationDebugData> Considerations;
};
