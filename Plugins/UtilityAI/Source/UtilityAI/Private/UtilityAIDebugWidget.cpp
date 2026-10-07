#include "UtilityAIDebugWidget.h"

#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Fonts/SlateFontInfo.h"

#include "UtilityAIComponent.h"
#include "UtilityAIAction.h"
#include "UtilityAIActionRow.h"
#include "UtilityAIDebugTypes.h"


void UUtilityAIDebugWidget::SetUtilityAIComponent(
    UUtilityAIComponent* InComponent)
{
    UtilityAIComponent = InComponent;

    RefreshDebugWidget();
}

void UUtilityAIDebugWidget::NativeTick(
    const FGeometry& MyGeometry,
    float InDeltaTime)
{
    Super::NativeTick(
        MyGeometry,
        InDeltaTime
    );

    RefreshTimer += InDeltaTime;

    if (RefreshTimer >= 0.2f)
    {
        RefreshTimer = 0.0f;

        RefreshDebugWidget();
    }
}

void UUtilityAIDebugWidget::RefreshDebugWidget()
{
    if (!UtilityAIComponent)
    {
        return;
    }


    // =========================================================
    // CURRENT ACTION
    // =========================================================

    if (CurrentActionText)
    {
        FSlateFontInfo FontInfo =
            CurrentActionText->GetFont();

        FontInfo.Size = 12.f;

        CurrentActionText->SetFont(
            FontInfo
        );

        UUtilityAIAction* CurrentAction =
            UtilityAIComponent->GetCurrentAction();

        if (CurrentAction)
        {
            FString ActionName =
                CurrentAction->GetName();

            // Remove Blueprint prefix.
            ActionName.RemoveFromStart(
                TEXT("BP_")
            );

            // Remove generated Unreal suffix.
            const int32 ClassSuffixIndex =
                ActionName.Find(
                    TEXT("_C_"),
                    ESearchCase::IgnoreCase,
                    ESearchDir::FromEnd
                );

            if (ClassSuffixIndex != INDEX_NONE)
            {
                ActionName =
                    ActionName.Left(
                        ClassSuffixIndex
                    );
            }

            CurrentActionText->SetText(
                FText::FromString(
                    FString::Printf(
                        TEXT("* %s"),
                        *ActionName
                    )
                )
            );
        }
        else
        {
            CurrentActionText->SetText(
                FText::FromString(
                    TEXT("None")
                )
            );
        }
    }


    // =========================================================
    // ACTION LIST
    // =========================================================

    const TArray<FUtilityAIActionDebugData>& DebugData =
        UtilityAIComponent->DebugData;

    const FUtilityAIActionDebugData* SelectedActionData =
        nullptr;


    // Find the selected action.
    for (const FUtilityAIActionDebugData& ActionData : DebugData)
    {
        if (ActionData.bSelected)
        {
            SelectedActionData =
                &ActionData;

            break;
        }
    }


    if (ActionList && ActionRowClass)
    {
        // ---------------------------------------------------------
        // Create rows only if we don't have enough.
        // ---------------------------------------------------------

        while (ActionRows.Num() < DebugData.Num())
        {
            UUtilityAIActionRow* ActionRow =
                CreateWidget<UUtilityAIActionRow>(
                    this,
                    ActionRowClass
                );

            if (!ActionRow)
            {
                break;
            }

            UVerticalBoxSlot* ActionRowSlot =
                ActionList->AddChildToVerticalBox(
                    ActionRow
                );

            if (ActionRowSlot)
            {
                ActionRowSlot->SetPadding(
                    FMargin(
                        0.0f,
                        2.0f
                    )
                );
            }

            ActionRows.Add(ActionRow);
        }


        // ---------------------------------------------------------
        // Update existing rows.
        // ---------------------------------------------------------

        for (int32 Index = 0; Index < ActionRows.Num(); ++Index)
        {
            if (!ActionRows[Index])
            {
                continue;
            }


            if (Index < DebugData.Num())
            {
                const FUtilityAIActionDebugData& ActionData =
                    DebugData[Index];

                FString ActionName =
                    ActionData.Name.ToString();

                // Remove Blueprint prefix.
                ActionName.RemoveFromStart(
                    TEXT("BP_")
                );

                // Remove generated Unreal suffix.
                const int32 ClassSuffixIndex =
                    ActionName.Find(
                        TEXT("_C_"),
                        ESearchCase::IgnoreCase,
                        ESearchDir::FromEnd
                    );

                if (ClassSuffixIndex != INDEX_NONE)
                {
                    ActionName =
                        ActionName.Left(
                            ClassSuffixIndex
                        );
                }


                ActionRows[Index]->SetActionData(
                    ActionName,
                    ActionData.Utility,
                    ActionData.bSelected
                );

                ActionRows[Index]->SetVisibility(
                    ESlateVisibility::Visible
                );
            }
            else
            {
                ActionRows[Index]->SetVisibility(
                    ESlateVisibility::Collapsed
                );
            }
        }
    }


    // =========================================================
    // SELECTED ACTION
    // =========================================================

    if (SelectedActionText)
    {
        FSlateFontInfo FontInfo =
            SelectedActionText->GetFont();

        FontInfo.Size = 12.f;

        SelectedActionText->SetFont(
            FontInfo
        );


        if (SelectedActionData)
        {
            FString SelectedName =
                SelectedActionData->Name.ToString();

            // Remove Blueprint prefix.
            SelectedName.RemoveFromStart(
                TEXT("BP_")
            );

            // Remove generated Unreal suffix.
            const int32 ClassSuffixIndex =
                SelectedName.Find(
                    TEXT("_C_"),
                    ESearchCase::IgnoreCase,
                    ESearchDir::FromEnd
                );

            if (ClassSuffixIndex != INDEX_NONE)
            {
                SelectedName =
                    SelectedName.Left(
                        ClassSuffixIndex
                    );
            }

            SelectedActionText->SetText(
                FText::FromString(
                    FString::Printf(
                        TEXT("SELECTED: %s"),
                        *SelectedName
                    )
                )
            );
        }
        else
        {
            SelectedActionText->SetText(
                FText::FromString(
                    TEXT("SELECTED: None")
                )
            );
        }
    }

    // =========================================================
    // CONSIDERATIONS
    // =========================================================

    if (ConsiderationList)
    {
        // Create the text block only once.
        if (!ConsiderationTextBlock)
        {
            ConsiderationTextBlock =
                NewObject<UTextBlock>(this);

            if (ConsiderationTextBlock)
            {
                FSlateFontInfo FontInfo =
                    ConsiderationTextBlock->GetFont();

                FontInfo.Size = 12.f;

                ConsiderationTextBlock->SetFont(
                    FontInfo
                );

                ConsiderationTextBlock->SetAutoWrapText(
                    true
                );

                ConsiderationTextBlock->SetJustification(
                    ETextJustify::Left
                );

                ConsiderationList->AddChildToVerticalBox(
                    ConsiderationTextBlock
                );
            }
        }


        if (ConsiderationTextBlock)
        {
            FString ConsiderationText;


            if (SelectedActionData)
            {
                for (
                    const FUtilityAIConsiderationDebugData&
                    Consideration :
                    SelectedActionData->Considerations)
                {
                    ConsiderationText +=
                        FString::Printf(
                            TEXT("%s\n  Input %.2f -> Score %.2f\n\n"),
                            *Consideration.Name.ToString(),
                            Consideration.InputValue,
                            Consideration.Score
                        );
                }
            }


            ConsiderationTextBlock->SetText(
                FText::FromString(
                    ConsiderationText
                )
            );
        }
    }


    // =========================================================
    // COMBINATION METHOD
    // =========================================================

    if (CombinationMethodText)
    {
        FSlateFontInfo FontInfo =
            CombinationMethodText->GetFont();

        FontInfo.Size = 12.f;

        CombinationMethodText->SetFont(
            FontInfo
        );


        if (SelectedActionData)
        {
            FString CombinationText;


            switch (
                SelectedActionData->CombinationMethod)
            {
            case EUtilityAICombinationMethod::Multiply:

                CombinationText =
                    TEXT("Combination: Multiply");

                break;


            case EUtilityAICombinationMethod::Average:

                CombinationText =
                    TEXT("Combination: Average");

                break;


            default:

                CombinationText =
                    TEXT("Combination: Unknown");

                break;
            }


            CombinationMethodText->SetText(
                FText::FromString(
                    CombinationText
                )
            );
        }
        else
        {
            CombinationMethodText->SetText(
                FText::FromString(
                    TEXT("Combination: None")
                )
            );
        }
    }
}
