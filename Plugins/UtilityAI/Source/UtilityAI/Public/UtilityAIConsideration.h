#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UtilityAIConsideration.generated.h"

class UUtilityAIContext;
class UUtilityAIDataSource;
class UUtilityAIResponseCurve;

/**
 * Evaluates a context value to produce a utility score.
 *
 * Uses a data source to retrieve input and an optional response curve
 * to convert that input into a score.
 */
UCLASS(Blueprintable, Abstract, EditInlineNew)
class UTILITYAI_API UUtilityAIConsideration : public UObject
{
    GENERATED_BODY()

public:

    /** Name used to identify this consideration. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
    FName Name;

    /** Source that provides the input value. */
    UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Utility AI")
    TObjectPtr<UUtilityAIDataSource> DataSource;

    /** Optional curve that converts the input into a utility score. */
    UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Utility AI")
    TObjectPtr<UUtilityAIResponseCurve> ResponseCurve;

    /**
     * Evaluates the consideration.
     *
     * @param Context Context containing values used by the data source.
     * @return Response score clamped to the range 0.0 to 1.0 when no curve exists,
     *         or the score returned by the response curve.
     */
    UFUNCTION(BlueprintCallable, Category = "Utility AI")
    virtual float Evaluate(const UUtilityAIContext* Context) const;
};
