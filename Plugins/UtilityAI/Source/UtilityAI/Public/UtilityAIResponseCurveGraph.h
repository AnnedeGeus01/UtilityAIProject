#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UtilityAIResponseCurveGraph.generated.h"

class UUtilityAIResponseCurve;

/**
 * Draws a response curve and marks the current input and score.
 * Used for the Utility AI debug widget.
 */
UCLASS()
class UTILITYAI_API UUtilityAIResponseCurveGraph : public UUserWidget
{
    GENERATED_BODY()

public:

    /**
     * Sets the curve and current evaluation to display.
     *
     * @param InCurve Response curve to draw.
     * @param InInputValue Current normalized input value.
     * @param InScore Current evaluated score.
     * @param InConsiderationName Name displayed for the consideration.
     */
    UFUNCTION(BlueprintCallable, Category = "Utility AI|Debug")
    void SetGraphData(
        UUtilityAIResponseCurve* InCurve,
        float InInputValue,
        float InScore,
        FName InConsiderationName
    );

    /** Clears the curve and hides its current-value marker. */
    UFUNCTION(BlueprintCallable, Category = "Utility AI|Debug")
    void ClearGraph();

protected:

    /**
     * Draws the axes, sampled response curve and current-value marker.
     *
     * @param Args Slate paint arguments.
     * @param AllottedGeometry Geometry allocated to this widget.
     * @param MyCullingRect Culling rectangle for the widget.
     * @param OutDrawElements Slate draw element list.
     * @param LayerId Current paint layer.
     * @param InWidgetStyle Current widget style.
     * @param bParentEnabled Whether the parent is enabled.
     * @return Highest layer used by this widget.
     */
    virtual int32 NativePaint(
        const FPaintArgs& Args,
        const FGeometry& AllottedGeometry,
        const FSlateRect& MyCullingRect,
        FSlateWindowElementList& OutDrawElements,
        int32 LayerId,
        const FWidgetStyle& InWidgetStyle,
        bool bParentEnabled
    ) const override;

private:

    /** Response curve currently displayed. */
    UPROPERTY()
    TObjectPtr<UUtilityAIResponseCurve> ResponseCurve;

    /** Current input passed to the response curve. */
    float InputValue = 0.0f;

    /** Current score returned by the response curve. */
    float Score = 0.0f;

    /** Name of the displayed consideration. */
    FName ConsiderationName = NAME_None;

    /** Whether the graph has data to display. */
    bool bHasGraphData = false;
};
