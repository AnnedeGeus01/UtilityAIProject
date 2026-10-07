#include "UtilityAIActionRow.h"

#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UUtilityAIActionRow::SetActionData(
    const FString& InActionName,
    float InUtility,
    bool bInSelected)
{
    if (ActionMarker)
    {
        if (bInSelected)
        {
            ActionMarker->SetText(
                FText::FromString(TEXT("*"))
            );
        }
        else
        {
            ActionMarker->SetText(
                FText::GetEmpty()
            );
        }
    }

    if (ActionName)
    {
        ActionName->SetText(
            FText::FromString(InActionName)
        );
    }

    if (UtilityBar)
    {
        UtilityBar->SetPercent(
            FMath::Clamp(InUtility, 0.0f, 1.0f)
        );
    }

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
