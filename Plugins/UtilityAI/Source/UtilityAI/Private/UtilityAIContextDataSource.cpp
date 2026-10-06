#include "UtilityAIContextDataSource.h"
#include "UtilityAIContext.h"
#include "UtilityAIComponent.h"

float UUtilityAIContextDataSource::GetValue_Implementation(
    const UUtilityAIContext* Context
) const
{
    if (!Context)
    {
        return 0.0f;
    }

    const float Value = Context->GetContextValue(ContextValueName);

    /*UE_LOG(
        LogTemp,
        Warning,
        TEXT("UtilityAI ContextDataSource: %s = %f"),
        *ContextValueName.ToString(),
        Value
    );*/

    return Value;
}
