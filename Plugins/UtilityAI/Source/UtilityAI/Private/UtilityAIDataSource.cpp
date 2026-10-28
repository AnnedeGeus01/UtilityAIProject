#include "UtilityAIDataSource.h"

/**
 * Returns the default value when no implementation is provided.
 *
 * @param Context Context containing AI data.
 * @return 0.0.
 */
float UUtilityAIDataSource::GetValue_Implementation(
    const UUtilityAIContext* Context
) const
{
    return 0.0f;
}
