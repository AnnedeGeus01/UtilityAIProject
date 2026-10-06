#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Curves/CurveFloat.h"
#include "UtilityAIResponseCurve.generated.h"

UCLASS(Blueprintable, EditInlineNew)
class UTILITYAI_API UUtilityAIResponseCurve : public UObject
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
    FRuntimeFloatCurve Curve;

    UFUNCTION(BlueprintCallable, Category = "Utility AI")
    virtual float Evaluate(float Input) const;
};