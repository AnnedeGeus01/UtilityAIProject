#include "UtilityAIAction.h"
#include "UtilityAIConsideration.h"
#include "UtilityAIContext.h"
#include "UtilityAIDataSource.h"
#include "UtilityAIDebugTypes.h"

void UUtilityAIAction::Execute_Implementation()
{
    // Action implementation will come later, probably in the editor
}

//float UUtilityAIAction::CalculateUtility(
//    const UUtilityAIContext* Context
//) const
//{
//    if (Considerations.Num() == 0)
//    {
//        return 0.0f;
//    }
//
//    float TotalUtility = 0.0f;
//
//    if (CombinationMethod == EUtilityAICombinationMethod::Multiply)
//    {
//        TotalUtility = 1.0f;
//
//        for (const UUtilityAIConsideration* Consideration : Considerations)
//        {
//            if (Consideration)
//            {
//                TotalUtility *= Consideration->Evaluate(Context);
//            }
//        }
//    }
//    else if (CombinationMethod == EUtilityAICombinationMethod::Average)
//    {
//        int32 ValidConsiderationCount = 0;
//
//        for (const UUtilityAIConsideration* Consideration : Considerations)
//        {
//            if (Consideration)
//            {
//                TotalUtility += Consideration->Evaluate(Context);
//                ++ValidConsiderationCount;
//            }
//        }
//
//        if (ValidConsiderationCount > 0)
//        {
//            TotalUtility /= ValidConsiderationCount;
//        }
//    }
//
//    return TotalUtility;
//}


float UUtilityAIAction::CalculateUtility(
    const UUtilityAIContext* Context
) const
{
    TArray<FUtilityAIConsiderationDebugData> DebugData;

    return CalculateUtilityWithDebug(Context, DebugData);
}


// Does the same as before, commented out one, just recording for the debugger
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

        // the existing calculation.
        const float Score = Consideration->Evaluate(Context);

        // need the raw input for the debugger.
        float InputValue = Score;

        if (Consideration->DataSource)
        {
            InputValue =
                Consideration->DataSource->GetValue(Context);
        }

        FUtilityAIConsiderationDebugData DebugData;

        DebugData.Name = Consideration->Name;
        DebugData.InputValue = InputValue;
        DebugData.Score = Score;

        OutConsiderations.Add(DebugData);

        if (CombinationMethod == EUtilityAICombinationMethod::Multiply)
        {
            TotalUtility *= Score;
        }
        else if (CombinationMethod == EUtilityAICombinationMethod::Average)
        {
            TotalUtility += Score;
        }

        ValidConsiderationCount++;
    }

    if (ValidConsiderationCount == 0)
    {
        return 0.0f;
    }

    if (CombinationMethod == EUtilityAICombinationMethod::Average)
    {
        TotalUtility /= ValidConsiderationCount;
    }

    return TotalUtility;
}

