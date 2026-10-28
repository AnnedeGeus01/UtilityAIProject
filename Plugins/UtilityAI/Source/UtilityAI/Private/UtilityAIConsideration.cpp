#include "UtilityAIConsideration.h"

#include "UtilityAIDataSource.h"
#include "UtilityAIResponseCurve.h"
#include "UtilityAIContext.h"

/**
 * Evaluates the input using the configured response curve.
 *
 * @param Context Context containing values used by the data source.
 * @return The resulting utility score.
 */
float UUtilityAIConsideration::Evaluate(
    const UUtilityAIContext* Context
) const
{
    if (!DataSource)
    {
        return 0.0f;
    }

    // Retrieve the input value.
    const float InputValue = DataSource->GetValue(Context);

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("Consideration %s: Input = %f"),
        *Name.ToString(),
        InputValue
    );

    // Clamp the input when no response curve is configured.
    if (!ResponseCurve)
    {
        return FMath::Clamp(InputValue, 0.0f, 1.0f);
    }

    // Convert the input into a response score.
    const float Result = ResponseCurve->Evaluate(InputValue);

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("Consideration %s: Score = %f"),
        *Name.ToString(),
        Result
    );

    return Result;
}
