#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Curves/CurveFloat.h"
#include "UtilityAIResponseCurve.generated.h"

/**
 * Evaluates an input using a configurable float response curve.
 *
 * The resulting score is clamped between 0.0 and 1.0.
 */
UCLASS(Blueprintable, EditInlineNew)
class UTILITYAI_API UUtilityAIResponseCurve : public UObject
{
    GENERATED_BODY()

public:

    /** Float curve defining the response to an input value. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
    FRuntimeFloatCurve Curve;

    /**
     * Evaluates the response curve for an input.
     *
     * @param Input Value passed to the curve.
     * @return Evaluated score clamped between 0.0 and 1.0.
     */
    UFUNCTION(BlueprintCallable, Category = "Utility AI")
    virtual float Evaluate(float Input) const;
};
