#pragma once

#include "CoreMinimal.h"
#include "UtilityAIDataSource.h"
#include "UtilityAIContextDataSource.generated.h"

/**
 * Reads a named value from the utility AI context.
 */
UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class UTILITYAI_API UUtilityAIContextDataSource : public UUtilityAIDataSource
{
    GENERATED_BODY()

public:

    /** Name of the context value to read. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
    FName ContextValueName;

    /**
     * Retrieves the configured value from the context.
     *
     * @param Context Context containing the stored values.
     * @return Retrieved value, or 0.0 if the context is null.
     */
    virtual float GetValue_Implementation(
        const UUtilityAIContext* Context
    ) const override;
};
