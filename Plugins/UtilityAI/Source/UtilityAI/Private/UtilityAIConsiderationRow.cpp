#include "UtilityAIConsiderationRow.h"

#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

/**
 * Updates the consideration row widgets.
 *
 * @param InName Name of the consideration.
 * @param InInputValue Raw input value. (Currently unused)
 * @param InScore Evaluated consideration score.
 */
void UUtilityAIConsiderationRow::SetConsiderationData(
    FName InName,
    float InInputValue,
    float InScore
)
{
    // Keep the score within the valid range.
    const float Score = FMath::Clamp(InScore, 0.0f, 1.0f);

    // Update the consideration name.
    if (ConsiderationName)
    {
        ConsiderationName->SetText(FText::FromName(InName));
    }

    // Update the progress bar using the score.
    if (ConsiderationBar)
    {
        ConsiderationBar->SetPercent(Score);
    }

    // Display the score with two decimal places.
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
