#include "UtilityAIContextDataSource.h"
#include "UtilityAIContext.h"

/**
 * Reads the configured value from the context.
 *
 * @param Context Context containing the stored values.
 * @return Context value, or 0.0 if the context is null.
 */
float UUtilityAIContextDataSource::GetValue_Implementation(
    const UUtilityAIContext* Context
) const
{
    if (!Context)
    {
        return 0.0f;
    }

    return Context->GetContextValue(ContextValueName);
}
