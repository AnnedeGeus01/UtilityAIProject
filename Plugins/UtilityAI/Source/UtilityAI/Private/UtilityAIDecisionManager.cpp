#include "UtilityAIDecisionManager.h"

#include "UtilityAIAction.h"
#include "UtilityAIContext.h"

/**
 * Selects the action with the highest utility score.
 *
 * @param Context Context containing values used by actions.
 * @return The selected action, or nullptr if no valid action exists.
 */
UUtilityAIAction* UUtilityAIDecisionManager::ChooseBestAction(
    const UUtilityAIContext* Context
) const
{
    TArray<FUtilityAIActionDebugData> DebugData;

    return ChooseBestActionWithDebug(Context, DebugData);
}

/**
 * Evaluates actions and records their utility data.
 *
 * Null actions are skipped. The first action with the highest utility
 * remains selected when multiple actions have equal scores.
 *
 * @param Context Context containing values used by actions.
 * @param OutDebugData Receives action and consideration debug data.
 * @return The action with the highest utility, or nullptr if none are valid.
 */
UUtilityAIAction* UUtilityAIDecisionManager::ChooseBestActionWithDebug(
    const UUtilityAIContext* Context,
    TArray<FUtilityAIActionDebugData>& OutDebugData
) const
{
    OutDebugData.Empty();

    UUtilityAIAction* BestAction = nullptr;
    float BestUtility = -1.0f;

    for (UUtilityAIAction* Action : Actions)
    {
        if (!Action)
        {
            continue;
        }

        // Prepare debug data for this action.
        FUtilityAIActionDebugData DebugData;
        DebugData.Name = Action->GetFName();
        DebugData.CombinationMethod = Action->CombinationMethod;

        // Calculate utility and collect consideration scores.
        const float Utility =
            Action->CalculateUtilityWithDebug(
                Context,
                DebugData.Considerations
            );

        DebugData.Utility = Utility;

        // Keep the action with the highest utility.
        if (Utility > BestUtility)
        {
            BestUtility = Utility;
            BestAction = Action;
        }

        OutDebugData.Add(DebugData);
    }

    // Mark the selected action in the debug data.
    for (FUtilityAIActionDebugData& DebugData : OutDebugData)
    {
        if (BestAction &&
            DebugData.Name == BestAction->GetFName())
        {
            DebugData.bSelected = true;
        }
    }

    return BestAction;
}
