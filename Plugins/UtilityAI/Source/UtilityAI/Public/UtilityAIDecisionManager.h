#pragma once

#include "CoreMinimal.h"
#include "UtilityAIDebugTypes.h"
#include "UObject/Object.h"
#include "UtilityAIDecisionManager.generated.h"

class UUtilityAIAction;
class UUtilityAIContext;

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class UTILITYAI_API UUtilityAIDecisionManager : public UObject
{
    GENERATED_BODY()

public:

    UPROPERTY(
        EditAnywhere,
        Instanced,
        BlueprintReadWrite,
        Category = "Utility AI"
    )
    TArray<TObjectPtr<UUtilityAIAction>> Actions;

    UFUNCTION(BlueprintCallable, Category = "Utility AI")
    UUtilityAIAction* ChooseBestAction(
        const UUtilityAIContext* Context
    ) const;

    UUtilityAIAction* ChooseBestActionWithDebug(
        const UUtilityAIContext* Context,
        TArray<FUtilityAIActionDebugData>& OutDebugData
    ) const;
};
