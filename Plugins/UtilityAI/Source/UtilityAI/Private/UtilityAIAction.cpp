#include "UtilityAIAction.h"

#include "UtilityAIConsideration.h"
#include "UtilityAIContext.h"
#include "UtilityAIDataSource.h"
#include "UtilityAIDebugTypes.h"

/**
 * Default action execution implementation.
 *
 * Override this function to define action behaviour.
 */
void UUtilityAIAction::Execute_Implementation()
{
    // Intentionally empty.
}

/**
 * Calculates utility using the configured combination method.
 *
 * @param Context Context containing values used by considerations.
 * @return Combined utility score.
 */
float UUtilityAIAction::CalculateUtility(
    const UUtilityAIContext* Context
) const
{
    TArray<FUtilityAIConsiderationDebugData> DebugData;

    return CalculateUtilityWithDebug(Context, DebugData);
}

/**
 * Calculates utility and collects debug information.
 *
 * Null considerations are skipped. Multiplication starts at 1.0,
 * while averaging divides the total by the number of valid considerations.
 *
 * @param Context Context containing values used by considerations.
 * @param OutConsiderations Receives consideration names, inputs and scores.
 * @return Combined utility score, or 0.0 if no valid considerations exist.
 */
float UUtilityAIAction::CalculateUtilityWithDebug(
    const UUtilityAIContext* Context,
    TArray<FUtilityAIConsiderationDebugData>& OutConsiderations
) const
{
    OutConsiderations.Empty();

    if (Considerations.Num() == 0)
    {
        return 0.0f;
    }

    float TotalUtility = 0.0f;
    int32 ValidConsiderationCount = 0;

    if (CombinationMethod == EUtilityAICombinationMethod::Multiply)
    {
        TotalUtility = 1.0f;
    }

    for (const UUtilityAIConsideration* Consideration : Considerations)
    {
        if (!Consideration)
        {
            continue;
        }

        // Evaluate the consideration's response score.
        const float Score = Consideration->Evaluate(Context);

        // Read the raw input value for debugging.
        float InputValue = Score;

        if (Consideration->DataSource)
        {
            InputValue = Consideration->DataSource->GetValue(Context);
        }

        // Store the values displayed by the debug widget.
        FUtilityAIConsiderationDebugData DebugData;
        DebugData.Name = Consideration->Name;
        DebugData.InputValue = InputValue;
        DebugData.Score = Score;
        DebugData.ResponseCurve = Consideration->ResponseCurve;

        OutConsiderations.Add(DebugData);

        // Combine the score into the action utility.
        if (CombinationMethod == EUtilityAICombinationMethod::Multiply)
        {
            TotalUtility *= Score;
        }
        else if (CombinationMethod == EUtilityAICombinationMethod::Average)
        {
            TotalUtility += Score;
        }

        ++ValidConsiderationCount;
    }

    if (ValidConsiderationCount == 0)
    {
        return 0.0f;
    }

    // Divide the accumulated total for average mode.
    if (CombinationMethod == EUtilityAICombinationMethod::Average)
    {
        TotalUtility /= ValidConsiderationCount;
    }

    return TotalUtility;
}
