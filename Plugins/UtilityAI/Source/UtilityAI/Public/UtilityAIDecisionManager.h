#pragma once

#include "CoreMinimal.h"
#include "UtilityAIDebugTypes.h"
#include "UObject/Object.h"
#include "UtilityAIDecisionManager.generated.h"

class UUtilityAIAction;
class UUtilityAIContext;

/**
 * Selects the action with the highest utility score.
 *
 * Evaluates configured actions and optionally records debug data.
 */
UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class UTILITYAI_API UUtilityAIDecisionManager : public UObject
{
    GENERATED_BODY()

public:

    /** Actions evaluated during decision making. */
    UPROPERTY(
        EditAnywhere,
        Instanced,
        BlueprintReadWrite,
        Category = "Utility AI"
    )
    TArray<TObjectPtr<UUtilityAIAction>> Actions;

    /**
     * Selects the action with the highest utility.
     *
     * @param Context Context containing values used by actions.
     * @return The selected action, or nullptr if none are valid.
     */
    UFUNCTION(BlueprintCallable, Category = "Utility AI")
    UUtilityAIAction* ChooseBestAction(
        const UUtilityAIContext* Context
    ) const;

    /**
     * Selects the best action and records debug data.
     *
     * Null actions are skipped. The first action with the highest utility
     * remains selected when multiple actions have equal scores. So the order
     * in which you add them to the component matter.
     * 
     * @param Context Context containing values used by actions.
     * @param OutDebugData Receives utility and consideration data for each action.
     * @return The selected action, or nullptr if none are valid.
     */
    UUtilityAIAction* ChooseBestActionWithDebug(
        const UUtilityAIContext* Context,
        TArray<FUtilityAIActionDebugData>& OutDebugData
    ) const;
};
