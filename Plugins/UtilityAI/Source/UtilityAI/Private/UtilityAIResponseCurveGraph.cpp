#include "UtilityAIResponseCurveGraph.h"

#include "UtilityAIResponseCurve.h"

#include "Rendering/DrawElements.h"
#include "Styling/CoreStyle.h"

/**
 * Sets the curve and current evaluation to display.
 *
 * @param InCurve Response curve to draw.
 * @param InInputValue Current normalized input value.
 * @param InScore Current evaluated score.
 * @param InConsiderationName Name displayed for the consideration.
 */
void UUtilityAIResponseCurveGraph::SetGraphData(
    UUtilityAIResponseCurve* InCurve,
    float InInputValue,
    float InScore,
    FName InConsiderationName
)
{
    ResponseCurve = InCurve;
    InputValue = FMath::Clamp(InInputValue, 0.0f, 1.0f);
    Score = FMath::Clamp(InScore, 0.0f, 1.0f);
    ConsiderationName = InConsiderationName;
    bHasGraphData = ResponseCurve != nullptr;

    Invalidate(EInvalidateWidgetReason::Paint);
}

/**
 * Clears the displayed curve and current-value marker.
 */
void UUtilityAIResponseCurveGraph::ClearGraph()
{
    ResponseCurve = nullptr;
    InputValue = 0.0f;
    Score = 0.0f;
    ConsiderationName = NAME_None;
    bHasGraphData = false;

    Invalidate(EInvalidateWidgetReason::Paint);
}

/**
 * Draws the graph axes, response curve and current-value marker.
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
int32 UUtilityAIResponseCurveGraph::NativePaint(
    const FPaintArgs& Args,
    const FGeometry& AllottedGeometry,
    const FSlateRect& MyCullingRect,
    FSlateWindowElementList& OutDrawElements,
    int32 LayerId,
    const FWidgetStyle& InWidgetStyle,
    bool bParentEnabled
) const
{
    const int32 BaseLayer = Super::NativePaint(
        Args,
        AllottedGeometry,
        MyCullingRect,
        OutDrawElements,
        LayerId,
        InWidgetStyle,
        bParentEnabled
    );

    const FVector2D Size = AllottedGeometry.GetLocalSize();
    const float GraphPadding = 16.0f;

    const FVector2D GraphMin(GraphPadding, GraphPadding);
    const FVector2D GraphMax(
        FMath::Max(GraphPadding + 1.0f, Size.X - GraphPadding),
        FMath::Max(GraphPadding + 1.0f, Size.Y - GraphPadding)
    );

    const float GraphWidth = GraphMax.X - GraphMin.X;
    const float GraphHeight = GraphMax.Y - GraphMin.Y;

    if (GraphWidth <= 1.0f || GraphHeight <= 1.0f)
    {
        return BaseLayer;
    }

    auto ToGraphPosition = [&](float X, float Y)
        {
            return FVector2D(
                GraphMin.X + X * GraphWidth,
                GraphMax.Y - Y * GraphHeight
            );
        };

    auto DrawLine = [&](
        const FVector2D& Start,
        const FVector2D& End,
        const FLinearColor& Color,
        float Thickness,
        int32 DrawLayer
        )
        {
            TArray<FVector2D> Points;
            Points.Add(Start);
            Points.Add(End);

            FSlateDrawElement::MakeLines(
                OutDrawElements,
                DrawLayer,
                AllottedGeometry.ToPaintGeometry(),
                Points,
                ESlateDrawEffect::None,
                Color,
                true,
                Thickness
            );
        };

    // Draw the graph grid.
    for (int32 Step = 0; Step <= 4; ++Step)
    {
        const float Value = Step / 4.0f;

        DrawLine(
            ToGraphPosition(Value, 0.0f),
            ToGraphPosition(Value, 1.0f),
            FLinearColor(0.18f, 0.18f, 0.18f, 1.0f),
            1.0f,
            BaseLayer + 1
        );

        DrawLine(
            ToGraphPosition(0.0f, Value),
            ToGraphPosition(1.0f, Value),
            FLinearColor(0.18f, 0.18f, 0.18f, 1.0f),
            1.0f,
            BaseLayer + 1
        );
    }

    // Draw the graph axes.
    DrawLine(
        ToGraphPosition(0.0f, 0.0f),
        ToGraphPosition(1.0f, 0.0f),
        FLinearColor::White,
        1.5f,
        BaseLayer + 2
    );

    DrawLine(
        ToGraphPosition(0.0f, 0.0f),
        ToGraphPosition(0.0f, 1.0f),
        FLinearColor::White,
        1.5f,
        BaseLayer + 2
    );

    if (!bHasGraphData || !ResponseCurve)
    {
        return BaseLayer + 2;
    }

    // Sample and draw the response curve.
    TArray<FVector2D> CurvePoints;
    CurvePoints.Reserve(101);

    for (int32 Index = 0; Index <= 100; ++Index)
    {
        const float X = Index / 100.0f;
        const float Y = ResponseCurve->Evaluate(X);

        CurvePoints.Add(ToGraphPosition(X, Y));
    }

    FSlateDrawElement::MakeLines(
        OutDrawElements,
        BaseLayer + 3,
        AllottedGeometry.ToPaintGeometry(),
        CurvePoints,
        ESlateDrawEffect::None,
        FLinearColor(0.1f, 0.65f, 1.0f, 1.0f),
        true,
        2.5f
    );

    // Draw a vertical guide at the current input.
    const FVector2D MarkerPosition = ToGraphPosition(
        InputValue,
        Score
    );

    DrawLine(
        ToGraphPosition(InputValue, 0.0f),
        MarkerPosition,
        FLinearColor(1.0f, 0.7f, 0.1f, 0.8f),
        1.5f,
        BaseLayer + 4
    );

    // Draw the current-value marker.
    TArray<FVector2D> MarkerPoints;
    constexpr int32 MarkerSegments = 20;
    constexpr float MarkerRadius = 5.0f;

    for (int32 Index = 0; Index <= MarkerSegments; ++Index)
    {
        const float Angle =
            2.0f * PI * Index / MarkerSegments;

        MarkerPoints.Add(
            MarkerPosition + FVector2D(
                FMath::Cos(Angle) * MarkerRadius,
                FMath::Sin(Angle) * MarkerRadius
            )
        );
    }

    FSlateDrawElement::MakeLines(
        OutDrawElements,
        BaseLayer + 5,
        AllottedGeometry.ToPaintGeometry(),
        MarkerPoints,
        ESlateDrawEffect::None,
        FLinearColor(1.0f, 0.7f, 0.1f, 1.0f),
        true,
        2.0f
    );

    return BaseLayer + 5;
}
