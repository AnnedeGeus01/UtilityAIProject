#include "UtilityAIActionRow.h"

#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

/**
 * Updates the action name, utility display and selection marker.
 *
 * @param InActionName Name of the action.
 * @param InUtility Calculated utility score.
 * @param bInSelected Whether the action is selected.
 */
void UUtilityAIActionRow::SetActionData(
    const FString& InActionName,
    float InUtility,
    bool bInSelected)
{
    // Show a marker for the selected action.
    if (ActionMarker)
    {
        ActionMarker->SetText(
            bInSelected
            ? FText::FromString(TEXT("*"))
            : FText::GetEmpty()
        );
    }

    // Display the action name.
    if (ActionName)
    {
        ActionName->SetText(
            FText::FromString(InActionName)
        );
    }

    // Update the utility bar.
    if (UtilityBar)
    {
        UtilityBar->SetPercent(
            FMath::Clamp(InUtility, 0.0f, 1.0f)
        );
    }

    // Display utility to two decimal places.
    if (UtilityValue)
    {
        UtilityValue->SetText(
            FText::FromString(
                FString::Printf(
                    TEXT("%.2f"),
                    InUtility
                )
            )
        );
    }
}
