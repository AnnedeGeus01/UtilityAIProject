#include "UtilityAIConsideration.h"
#include "UtilityAIDataSource.h"
#include "UtilityAIResponseCurve.h"
#include "UtilityAIContext.h"

float UUtilityAIConsideration::Evaluate(const UUtilityAIContext* Context) const
{
    if (!DataSource)
    {
        return 0.0f;
    }

    const float InputValue = DataSource->GetValue(Context);

    if (!ResponseCurve)
    {
        return FMath::Clamp(InputValue, 0.0f, 1.0f);
    }

    const float Result = ResponseCurve->Evaluate(InputValue);

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("Consideration '%s': Input=%f Result=%f"),
        *Name.ToString(),
        InputValue,
        Result
    );

    return Result;
}