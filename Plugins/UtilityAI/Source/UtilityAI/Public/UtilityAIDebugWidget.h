#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UtilityAIDebugWidget.generated.h"

class UUtilityAIComponent;
class UTextBlock;
class UVerticalBox;
class UUtilityAIActionRow;
class UUtilityAIConsiderationRow;

/**
 * Displays runtime utility AI decisions and consideration scores.
 *
 * Refreshes the current action, action utilities, selected action
 * considerations, and combination method.
 */
UCLASS()
class UTILITYAI_API UUtilityAIDebugWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    /**
     * Assigns the component to monitor and refreshes the display.
     *
     * @param InComponent Utility AI component to debug.
     */
    UFUNCTION(BlueprintCallable, Category = "Utility AI|Debug")
    void SetUtilityAIComponent(UUtilityAIComponent* InComponent);

protected:

    /**
     * Updates the debug display at regular intervals. Same as 
     * the descision interval set in the Utiliti AI Component.
     *
     * @param MyGeometry Geometry of the widget.
     * @param InDeltaTime Time elapsed since the previous frame.
     */
    virtual void NativeTick(
        const FGeometry& MyGeometry,
        float InDeltaTime
    ) override;

    /** Utility AI component being monitored. */
    UPROPERTY(BlueprintReadOnly, Category = "Utility AI|Debug")
    TObjectPtr<UUtilityAIComponent> UtilityAIComponent;

    /** Displays the currently executing action. */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> CurrentActionText;

    /** Displays the selected action name. */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> SelectedActionText;

    /** Displays the selected action's combination method. */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> CombinationMethodText;

    /** Contains rows for all available actions. */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UVerticalBox> ActionList;

    /** Contains rows for the selected action's considerations. */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UVerticalBox> ConsiderationList;

    /** Widget class used to create action rows. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI|Debug")
    TSubclassOf<UUtilityAIActionRow> ActionRowClass;

    /** Reusable action row widgets. */
    UPROPERTY()
    TArray<TObjectPtr<UUtilityAIActionRow>> ActionRows;

    /** Widget class used to create consideration rows. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI|Debug")
    TSubclassOf<UUtilityAIConsiderationRow> ConsiderationRowClass;

    /** Reusable consideration row widgets. */
    UPROPERTY()
    TArray<TObjectPtr<UUtilityAIConsiderationRow>> ConsiderationRows;

private:

    /** Updates all debug display elements. */
    void RefreshDebugWidget();

    /** Time accumulated between display refreshes. */
    float RefreshTimer = 0.0f;
};
