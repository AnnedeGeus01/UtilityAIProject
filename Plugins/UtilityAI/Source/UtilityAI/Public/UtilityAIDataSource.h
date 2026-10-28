#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UtilityAIDataSource.generated.h"

class UUtilityAIContext;

/**
 * Base class for retrieving values used by Utility AI considerations.
 *
 * Derived classes define how values are retrieved from the AI context
 * or other sources.
 */
UCLASS(Blueprintable, Abstract, EditInlineNew)
class UTILITYAI_API UUtilityAIDataSource : public UObject
{
    GENERATED_BODY()

public:

    /**
     * Retrieves a value from the specified context.
     *
     * @param Context Context containing AI data.
     * @return Retrieved value.
     */
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Utility AI")
    float GetValue(const UUtilityAIContext* Context) const;

    /**
     * Default implementation of the value retrieval event.
     *
     * @param Context Context containing AI data.
     * @return 0.0 by default.
     */
    virtual float GetValue_Implementation(
        const UUtilityAIContext* Context
    ) const;
};
