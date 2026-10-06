#pragma once

#include "CoreMinimal.h"
#include "UtilityAIDataSource.h"
#include "UtilityAIContextDataSource.generated.h"

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class UTILITYAI_API UUtilityAIContextDataSource : public UUtilityAIDataSource
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
    FName ContextValueName;

    virtual float GetValue_Implementation(
        const UUtilityAIContext* Context
    ) const override;
};
