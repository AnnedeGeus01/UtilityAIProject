#include "UtilityAIConsiderationRow.h"

#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

/**
 * Binds the checkbox state change event.
 */
void UUtilityAIConsiderationRow::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (ConsiderationCheckBox)
    {
        ConsiderationCheckBox->OnCheckStateChanged.AddUniqueDynamic(
            this,
            &UUtilityAIConsiderationRow::HandleCheckStateChanged
        );
    }
}

/**
 * Updates the displayed consideration data.
 *
 * @param InName Name of the consideration.
 * @param InInputValue Raw input value.
 * @param InScore Evaluated consideration score.
 */
void UUtilityAIConsiderationRow::SetConsiderationData(
    FName InName,
    float InInputValue,
    float InScore
)
{
    const float Score = FMath::Clamp(InScore, 0.0f, 1.0f);

    if (ConsiderationName)
    {
        ConsiderationName->SetText(FText::FromName(InName));
    }

    if (ConsiderationBar)
    {
        ConsiderationBar->SetPercent(Score);
    }

    if (ConsiderationScore)
    {
        FNumberFormattingOptions FormatOptions;
        FormatOptions.SetMinimumFractionalDigits(2);
        FormatOptions.SetMaximumFractionalDigits(2);
        FormatOptions.SetMinimumIntegralDigits(1);

        ConsiderationScore->SetText(
            FText::AsNumber(Score, &FormatOptions)
        );
    }
}

/**
 * Sets the checkbox state without triggering selection callbacks.
 *
 * @param bIsSelected Whether this row should be selected.
 */
void UUtilityAIConsiderationRow::SetSelected(bool bIsSelected)
{
    if (!ConsiderationCheckBox)
    {
        return;
    }

    bUpdatingSelection = true;
    ConsiderationCheckBox->SetIsChecked(bIsSelected);
    bUpdatingSelection = false;
}

/**
 * Broadcasts user-driven checkbox selection changes.
 *
 * @param bIsChecked Whether the checkbox is checked.
 */
void UUtilityAIConsiderationRow::HandleCheckStateChanged(
    bool bIsChecked
)
{
    if (bUpdatingSelection)
    {
        return;
    }

    OnSelectionChanged.Broadcast(this, bIsChecked);
}
