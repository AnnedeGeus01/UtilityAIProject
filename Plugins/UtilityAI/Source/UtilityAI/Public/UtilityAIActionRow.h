#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UtilityAIActionRow.generated.h"

class UTextBlock;
class UProgressBar;

/**
 * Displays an action's name, utility score and selection state.
 * Used for the Utility AI debug widget.
 */
UCLASS()
class UTILITYAI_API UUtilityAIActionRow : public UUserWidget
{
    GENERATED_BODY()

public:

    /**
     * Updates the action row's displayed data.
     *
     * @param InActionName Name of the action.
     * @param InUtility Calculated utility score.
     * @param bInSelected Whether the action is selected.
     */
    UFUNCTION(BlueprintCallable, Category = "Utility AI|Debug")
    void SetActionData(
        const FString& InActionName,
        float InUtility,
        bool bInSelected
    );

protected:

    /** Displays a marker when the action is selected. */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> ActionMarker;

    /** Displays the action name. */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> ActionName;

    /** Displays the action's utility as a progress bar. */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UProgressBar> UtilityBar;

    /** Displays the utility score to two decimal places. */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> UtilityValue;
};
