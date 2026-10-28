#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UtilityAIAction.generated.h"

class UUtilityAIConsideration;
class UUtilityAIContext;
struct FUtilityAIConsiderationDebugData;

/**
 * Defines how consideration scores are combined into an action utility.
 */
UENUM(BlueprintType)
enum class EUtilityAICombinationMethod : uint8
{
    /** Multiplies all valid consideration scores. */
    Multiply UMETA(DisplayName = "Multiply"),

    /** Calculates the average of all valid consideration scores. */
    Average UMETA(DisplayName = "Average")
};

/**
 * Base class for utility AI actions.
 *
 * Actions calculate utility from their considerations and define
 * behaviour to execute when selected by the decision manager.
 */
UCLASS(Blueprintable, Abstract, EditInlineNew, DefaultToInstanced)
class UTILITYAI_API UUtilityAIAction : public UObject
{
    GENERATED_BODY()

public:

    /** Considerations used to calculate this action's utility. */
    UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category = "Utility AI")
    TArray<TObjectPtr<UUtilityAIConsideration>> Considerations;

    /** Method used to combine consideration scores. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
    EUtilityAICombinationMethod CombinationMethod =
        EUtilityAICombinationMethod::Multiply;

    /**
     * Executes the action.
     *
     * Override this event in Blueprint (or C++) to define behaviour.
     */
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Utility AI")
    void Execute();

    /** Default implementation of the action execution event. */
    virtual void Execute_Implementation();

    /**
     * Calculates the action's utility.
     *
     * @param Context Context containing values used by considerations.
     * @return Combined utility score.
     */
    UFUNCTION(BlueprintCallable, Category = "Utility AI")
    virtual float CalculateUtility(
        const UUtilityAIContext* Context
    ) const;

    /**
     * Calculates utility and records consideration debug data.
     *
     * @param Context Context containing values used by considerations.
     * @param OutConsiderations Receives each consideration's debug data.
     * @return Combined utility score.
     */
    float CalculateUtilityWithDebug(
        const UUtilityAIContext* Context,
        TArray<FUtilityAIConsiderationDebugData>& OutConsiderations
    ) const;
};
