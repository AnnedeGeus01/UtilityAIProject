#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UtilityAIConsiderationRow.generated.h"

class UTextBlock;
class UProgressBar;
class UCheckBox;
class UUtilityAIConsiderationRow;

/**
 * Broadcasts when a consideration row is selected or deselected.
 *
 * @param Row Row whose selection changed.
 * @param bIsSelected Whether the row is selected.
 */
DECLARE_MULTICAST_DELEGATE_TwoParams(
    FOnUtilityAIConsiderationSelectionChanged,
    UUtilityAIConsiderationRow*,
    bool
);

/**
 * Displays a consideration's name, score and progress bar.
 * Used for the Utility AI debug widget.
 * Allows the user to select a consideration for curve debugging.
 */
UCLASS()
class UTILITYAI_API UUtilityAIConsiderationRow : public UUserWidget
{
    GENERATED_BODY()

public:

    /** Fired when the user changes this row's selection state. */
    FOnUtilityAIConsiderationSelectionChanged OnSelectionChanged;

    /**
     * Updates the displayed consideration data.
     *
     * @param InName Name of the consideration.
     * @param InInputValue Raw input value.
     * @param InScore Evaluated consideration score.
     */
    UFUNCTION(BlueprintCallable, Category = "Utility AI|Debug")
    void SetConsiderationData(
        FName InName,
        float InInputValue,
        float InScore
    );

    /**
     * Sets the row's selection state without broadcasting a selection event.
     *
     * @param bIsSelected Whether the row should be selected.
     */
    void SetSelected(bool bIsSelected);

protected:

    /** Binds the checkbox event after widget initialization. */
    virtual void NativeOnInitialized() override;

    /** Handles user changes to the checkbox. */
    UFUNCTION()
    void HandleCheckStateChanged(bool bIsChecked);

    /** Checkbox used to select this consideration's response curve. */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCheckBox> ConsiderationCheckBox;

    /** Displays the consideration name. */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> ConsiderationName;

    /** Displays the consideration score as a progress bar. */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UProgressBar> ConsiderationBar;

    /** Displays the score as a formatted number. */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> ConsiderationScore;

    /** Prevents programmatic checkbox changes from triggering callbacks. */
    bool bUpdatingSelection = false;
};
