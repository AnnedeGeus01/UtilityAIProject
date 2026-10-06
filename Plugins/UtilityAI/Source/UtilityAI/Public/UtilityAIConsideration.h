#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UtilityAIConsideration.generated.h"

class UUtilityAIContext;
class UUtilityAIDataSource;
class UUtilityAIResponseCurve;

UCLASS(Blueprintable, Abstract, EditInlineNew)
class UTILITYAI_API UUtilityAIConsideration : public UObject
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
    FName Name;

    UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Utility AI")
    TObjectPtr<UUtilityAIDataSource> DataSource;

    UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Utility AI")
    TObjectPtr<UUtilityAIResponseCurve> ResponseCurve;

    UFUNCTION(BlueprintCallable, Category = "Utility AI")
    virtual float Evaluate(const UUtilityAIContext* Context) const;
};