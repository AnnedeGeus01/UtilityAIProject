#include "UtilityAIResponseCurve.h"

float UUtilityAIResponseCurve::Evaluate(float Input) const
{
    return FMath::Clamp(
        Curve.GetRichCurveConst()->Eval(Input),
        0.0f,
        1.0f
    );
}