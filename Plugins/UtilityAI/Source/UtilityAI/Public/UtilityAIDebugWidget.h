#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UtilityAIDebugWidget.generated.h"

class UUtilityAIComponent;
class UTextBlock;
class UVerticalBox;
class UUtilityAIActionRow;
class UUtilityAIConsiderationRow;
class UUtilityAIResponseCurve;
class UUtilityAIResponseCurveGraph;

/**
 * Displays runtime utility AI decisions and consideration scores.
 *
 * Refreshes action utilities, the selected action's considerations,
 * and the response curve for the selected consideration.
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
     * Updates the debug display at regular intervals.
     *
     * @param MyGeometry Geometry of the widget.
     * @param InDeltaTime Time elapsed since the previous frame.
     */
    virtual void NativeTick(
        const FGeometry& MyGeometry,
        float InDeltaTime
    ) override;

    /** Component supplying runtime utility AI debug data. */
    UPROPERTY(BlueprintReadOnly, Category = "Utility AI|Debug")
    TObjectPtr<UUtilityAIComponent> UtilityAIComponent;

    /** Displays the currently executing action. */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> CurrentActionText;

    /** Displays the action selected by the decision manager. */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> SelectedActionText;

    /** Displays the selected action's combination method. */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> CombinationMethodText;

    /** Contains the reusable action debug rows. */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UVerticalBox> ActionList;

    /** Contains the reusable consideration debug rows. */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UVerticalBox> ConsiderationList;

    /** Displays the selected consideration's response curve. */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UUtilityAIResponseCurveGraph> ResponseCurveGraph;

    /** Widget class used to create action debug rows. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI|Debug")
    TSubclassOf<UUtilityAIActionRow> ActionRowClass;

    /** Reusable action debug row instances. */
    UPROPERTY()
    TArray<TObjectPtr<UUtilityAIActionRow>> ActionRows;

    /** Widget class used to create consideration debug rows. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI|Debug")
    TSubclassOf<UUtilityAIConsiderationRow> ConsiderationRowClass;

    /** Reusable consideration debug row instances. */
    UPROPERTY()
    TArray<TObjectPtr<UUtilityAIConsiderationRow>> ConsiderationRows;

private:
    /** Updates all debug display elements. */
    void RefreshDebugWidget();

    /** Updates the graph using the current selection. */
    void UpdateResponseCurveGraph();

    /**
     * Clears the selected consideration and its graph.
     */
    void ClearConsiderationSelection();

    /**
     * Handles selection changes from consideration rows.
     *
     * @param Row Row whose selection changed.
     * @param bIsSelected Whether the row is selected.
     */
    void HandleConsiderationSelectionChanged(
        UUtilityAIConsiderationRow* Row,
        bool bIsSelected
    );

    /** Time accumulated between display refreshes. */
    float RefreshTimer = 0.0f;

    /** Currently selected consideration row. */
    UPROPERTY()
    TObjectPtr<UUtilityAIConsiderationRow> SelectedConsiderationRow;

    /** Response curve belonging to the selected consideration. */
    UPROPERTY()
    TObjectPtr<UUtilityAIResponseCurve> SelectedResponseCurve;

    /** Current input value of the selected consideration. */
    float SelectedConsiderationInput = 0.0f;

    /** Current evaluated score of the selected consideration. */
    float SelectedConsiderationScore = 0.0f;

    /** Name of the action containing the selected consideration. */
    FName SelectedConsiderationActionName = NAME_None;

    /** Name of the selected consideration. */
    FName SelectedConsiderationName = NAME_None;
};
