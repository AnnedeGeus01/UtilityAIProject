#include "UtilityAIDebugWidget.h"

#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Fonts/SlateFontInfo.h"

#include "UtilityAIComponent.h"
#include "UtilityAIAction.h"
#include "UtilityAIActionRow.h"
#include "UtilityAIConsiderationRow.h"
#include "UtilityAIDebugTypes.h"

/**
 * Assigns the component and performs an initial refresh.
 *
 * @param InComponent Utility AI component to monitor.
 */
void UUtilityAIDebugWidget::SetUtilityAIComponent(
    UUtilityAIComponent* InComponent)
{
    UtilityAIComponent = InComponent;
    RefreshDebugWidget();
}

/**
 * Refreshes the display every couple of seconds, defined
 * in the Utility AI component
 *
 * @param MyGeometry Geometry of the widget.
 * @param InDeltaTime Time elapsed since the previous frame.
 */
void UUtilityAIDebugWidget::NativeTick(
    const FGeometry& MyGeometry,
    float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (!UtilityAIComponent)
    {
        return;
    }

    RefreshTimer += InDeltaTime;

    const float RefreshInterval =
        UtilityAIComponent->GetDecisionInterval();

    if (RefreshInterval <= 0.0f || RefreshTimer >= RefreshInterval)
    {
        RefreshTimer = 0.0f;
        RefreshDebugWidget();
    }
}

/**
 * Updates action information and consideration debug rows.
 */
void UUtilityAIDebugWidget::RefreshDebugWidget()
{
    if (!UtilityAIComponent)
    {
        return;
    }

    // Update the currently executing action.
    if (CurrentActionText)
    {
        FSlateFontInfo FontInfo = CurrentActionText->GetFont();
        FontInfo.Size = 12.f;
        CurrentActionText->SetFont(FontInfo);

        UUtilityAIAction* CurrentAction =
            UtilityAIComponent->GetCurrentAction();

        if (CurrentAction)
        {
            FString ActionName = CurrentAction->GetName();

            ActionName.RemoveFromStart(TEXT("BP_"));

            const int32 ClassSuffixIndex = ActionName.Find(
                TEXT("_C_"),
                ESearchCase::IgnoreCase,
                ESearchDir::FromEnd
            );

            if (ClassSuffixIndex != INDEX_NONE)
            {
                ActionName = ActionName.Left(ClassSuffixIndex);
            }

            CurrentActionText->SetText(
                FText::FromString(
                    FString::Printf(TEXT("* %s"), *ActionName)
                )
            );
        }
        else
        {
            CurrentActionText->SetText(FText::FromString(TEXT("None")));
        }
    }

    // Find the selected action in the debug data.
    const TArray<FUtilityAIActionDebugData>& DebugData =
        UtilityAIComponent->DebugData;

    const FUtilityAIActionDebugData* SelectedActionData = nullptr;

    for (const FUtilityAIActionDebugData& ActionData : DebugData)
    {
        if (ActionData.bSelected)
        {
            SelectedActionData = &ActionData;
            break;
        }
    }

    // Create and update reusable action rows.
    if (ActionList && ActionRowClass)
    {
        while (ActionRows.Num() < DebugData.Num())
        {
            UUtilityAIActionRow* ActionRow =
                CreateWidget<UUtilityAIActionRow>(this, ActionRowClass);

            if (!ActionRow)
            {
                break;
            }

            UVerticalBoxSlot* ActionRowSlot =
                ActionList->AddChildToVerticalBox(ActionRow);

            if (ActionRowSlot)
            {
                ActionRowSlot->SetPadding(FMargin(0.0f, 2.0f));
            }

            ActionRows.Add(ActionRow);
        }

        for (int32 Index = 0; Index < ActionRows.Num(); ++Index)
        {
            UUtilityAIActionRow* Row = ActionRows[Index];

            if (!Row)
            {
                continue;
            }

            if (Index < DebugData.Num())
            {
                const FUtilityAIActionDebugData& ActionData =
                    DebugData[Index];

                FString ActionName = ActionData.Name.ToString();
                ActionName.RemoveFromStart(TEXT("BP_"));

                const int32 ClassSuffixIndex = ActionName.Find(
                    TEXT("_C_"),
                    ESearchCase::IgnoreCase,
                    ESearchDir::FromEnd
                );

                if (ClassSuffixIndex != INDEX_NONE)
                {
                    ActionName = ActionName.Left(ClassSuffixIndex);
                }

                Row->SetActionData(
                    ActionName,
                    ActionData.Utility,
                    ActionData.bSelected
                );

                Row->SetVisibility(ESlateVisibility::Visible);
            }
            else
            {
                Row->SetVisibility(ESlateVisibility::Collapsed);
            }
        }
    }

    // Update the selected action label.
    if (SelectedActionText)
    {
        FSlateFontInfo FontInfo = SelectedActionText->GetFont();
        FontInfo.Size = 12.f;
        SelectedActionText->SetFont(FontInfo);

        if (SelectedActionData)
        {
            FString SelectedName = SelectedActionData->Name.ToString();
            SelectedName.RemoveFromStart(TEXT("BP_"));

            const int32 ClassSuffixIndex = SelectedName.Find(
                TEXT("_C_"),
                ESearchCase::IgnoreCase,
                ESearchDir::FromEnd
            );

            if (ClassSuffixIndex != INDEX_NONE)
            {
                SelectedName = SelectedName.Left(ClassSuffixIndex);
            }

            SelectedActionText->SetText(
                FText::FromString(
                    FString::Printf(TEXT("SELECTED: %s"), *SelectedName)
                )
            );
        }
        else
        {
            SelectedActionText->SetText(
                FText::FromString(TEXT("SELECTED: None"))
            );
        }
    }

    // Create and update reusable consideration rows.
    if (ConsiderationList && ConsiderationRowClass)
    {
        const int32 NumConsiderations = SelectedActionData
            ? SelectedActionData->Considerations.Num()
            : 0;

        while (ConsiderationRows.Num() < NumConsiderations)
        {
            UUtilityAIConsiderationRow* Row =
                CreateWidget<UUtilityAIConsiderationRow>(
                    this,
                    ConsiderationRowClass
                );

            if (!Row)
            {
                UE_LOG(
                    LogTemp,
                    Warning,
                    TEXT("Failed to create Utility AI Consideration Row.")
                );
                break;
            }

            UVerticalBoxSlot* RowSlot =
                ConsiderationList->AddChildToVerticalBox(Row);

            if (RowSlot)
            {
                RowSlot->SetPadding(FMargin(0.0f, 2.0f));
            }

            ConsiderationRows.Add(Row);
        }

        for (int32 Index = 0; Index < ConsiderationRows.Num(); ++Index)
        {
            UUtilityAIConsiderationRow* Row = ConsiderationRows[Index];

            if (!Row)
            {
                continue;
            }

            if (SelectedActionData &&
                Index < SelectedActionData->Considerations.Num())
            {
                const FUtilityAIConsiderationDebugData& Consideration =
                    SelectedActionData->Considerations[Index];

                Row->SetConsiderationData(
                    Consideration.Name,
                    Consideration.InputValue,
                    Consideration.Score
                );

                Row->SetVisibility(ESlateVisibility::Visible);
                Row->SetRenderOpacity(1.0f);
            }
            else
            {
                Row->SetVisibility(ESlateVisibility::Collapsed);
            }
        }
    }
    else
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT("Consideration list or row class is not assigned.")
        );
    }

    // Display the selected action's combination method.
    if (CombinationMethodText)
    {
        FSlateFontInfo FontInfo = CombinationMethodText->GetFont();
        FontInfo.Size = 12.f;
        CombinationMethodText->SetFont(FontInfo);

        if (SelectedActionData)
        {
            FString CombinationText;

            switch (SelectedActionData->CombinationMethod)
            {
            case EUtilityAICombinationMethod::Multiply:
                CombinationText = TEXT("Combination: Multiply");
                break;

            case EUtilityAICombinationMethod::Average:
                CombinationText = TEXT("Combination: Average");
                break;

            default:
                CombinationText = TEXT("Combination: Unknown");
                break;
            }

            CombinationMethodText->SetText(
                FText::FromString(CombinationText)
            );
        }
        else
        {
            CombinationMethodText->SetText(
                FText::FromString(TEXT("Combination: None"))
            );
        }
    }
}
