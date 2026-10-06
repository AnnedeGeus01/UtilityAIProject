#include "UtilityAIDebugWidget.h"

#include "Components/TextBlock.h"
#include "UtilityAIComponent.h"
#include "UtilityAIDebugTypes.h"
#include "UtilityAIAction.h"

void UUtilityAIDebugWidget::SetUtilityAIComponent(
    UUtilityAIComponent* InComponent
)
{
    UtilityAIComponent = InComponent;

    RefreshDebugText();
}

void UUtilityAIDebugWidget::NativeTick(
    const FGeometry& MyGeometry,
    float InDeltaTime
)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    RefreshDebugText();
}

void UUtilityAIDebugWidget::RefreshDebugText()
{
    if (!DebugText || !UtilityAIComponent)
    {
        return;
    }

    FString Output;

    Output += TEXT("UTILITY AI DEBUGGER\n");
    Output += TEXT("============================\n\n");

    UUtilityAIAction* CurrentAction =
        UtilityAIComponent->GetCurrentAction();

    if (CurrentAction)
    {
        Output += FString::Printf(
            TEXT("CURRENT ACTION: %s\n\n"),
            *CurrentAction->GetName()
        );
    }
    else
    {
        Output += TEXT("CURRENT ACTION: None\n\n");
    }

    Output += TEXT("ACTIONS\n");
    Output += TEXT("----------------------------\n");

    for (const FUtilityAIActionDebugData& ActionData :
        UtilityAIComponent->DebugData)
    {
        Output += FString::Printf(
            TEXT("%s    %.3f%s\n"),
            *ActionData.Name.ToString(),
            ActionData.Utility,
            ActionData.bSelected
            ? TEXT("  < SELECTED")
            : TEXT("")
        );

        for (const FUtilityAIConsiderationDebugData& Consideration :
            ActionData.Considerations)
        {
            Output += FString::Printf(
                TEXT("    %s: Input %.3f -> Score %.3f\n"),
                *Consideration.Name.ToString(),
                Consideration.InputValue,
                Consideration.Score
            );
        }

        Output += TEXT("\n");
    }

    DebugText->SetText(
        FText::FromString(Output)
    );
}
