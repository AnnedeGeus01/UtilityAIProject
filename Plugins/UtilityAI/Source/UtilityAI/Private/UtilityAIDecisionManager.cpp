#include "UtilityAIDecisionManager.h"
#include "UtilityAIAction.h"
#include "UtilityAIContext.h"
#include "Engine/Engine.h" // for on screen debug messages, testing purposes

//UUtilityAIAction* UUtilityAIDecisionManager::ChooseBestAction(
//    const UUtilityAIContext* Context) const
//{
//    UUtilityAIAction* BestAction = nullptr;
//    float BestUtility = -1.0f;
//
//    /*GEngine->AddOnScreenDebugMessage(
//        -1,
//        5.0f,
//        FColor::Cyan,
//        FString::Printf(TEXT("ACTIONS COUNT: %d"), Actions.Num())
//    );*/
//
//    for (int32 Index = 0; Index < Actions.Num(); ++Index)
//    {
//        UUtilityAIAction* Action = Actions[Index];
//
//        if (!Action)
//        {
//            /*GEngine->AddOnScreenDebugMessage(
//                -1,
//                5.0f,
//                FColor::Red,
//                FString::Printf(TEXT("Action[%d] = NULL"), Index)
//            );*/
//
//            continue;
//        }
//
//        /*GEngine->AddOnScreenDebugMessage(
//            -1,
//            5.0f,
//            FColor::Green,
//            FString::Printf(
//                TEXT("Action[%d] = %s"),
//                Index,
//                *Action->GetName()
//            )
//        );*/
//
//        const float Utility = Action->CalculateUtility(Context);
//
//        /*GEngine->AddOnScreenDebugMessage(
//            -1,
//            5.0f,
//            FColor::Yellow,
//            FString::Printf(
//                TEXT("Utility: %s = %.3f"),
//                *Action->GetName(),
//                Utility
//            )
//        );*/
//
//        if (Utility > BestUtility)
//        {
//            BestUtility = Utility;
//            BestAction = Action;
//        }
//    }
//
//    return BestAction;
//}

UUtilityAIAction* UUtilityAIDecisionManager::ChooseBestAction(
    const UUtilityAIContext* Context
) const
{
    TArray<FUtilityAIActionDebugData> DebugData;

    return ChooseBestActionWithDebug(Context, DebugData);
}

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

        FUtilityAIActionDebugData DebugData;

        DebugData.Name = Action->GetFName();
        DebugData.CombinationMethod = Action->CombinationMethod;

        const float Utility =
            Action->CalculateUtilityWithDebug(
                Context,
                DebugData.Considerations
            );

        DebugData.Utility = Utility;

        if (Utility > BestUtility)
        {
            BestUtility = Utility;
            BestAction = Action;
        }

        OutDebugData.Add(DebugData);
    }

    // Mark the winning action.
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
