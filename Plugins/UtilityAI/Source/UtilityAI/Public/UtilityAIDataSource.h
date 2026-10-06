#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UtilityAIDataSource.generated.h"

class UUtilityAIContext;

UCLASS(Blueprintable, Abstract, EditInlineNew)
class UTILITYAI_API UUtilityAIDataSource : public UObject
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Utility AI")
    float GetValue(const UUtilityAIContext* Context) const;

    virtual float GetValue_Implementation(
        const UUtilityAIContext* Context
    ) const;
};
