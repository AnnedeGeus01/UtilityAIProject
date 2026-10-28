#include "UtilityAIResponseCurve.h"

/**
 * Evaluates the curve and clamps the result to the utility score range.
 *
 * @param Input Value passed to the curve.
 * @return Curve output clamped between 0.0 and 1.0.
 */
float UUtilityAIResponseCurve::Evaluate(float Input) const
{
    return FMath::Clamp(
        Curve.GetRichCurveConst()->Eval(Input),
        0.0f,
        1.0f
    );
}
