#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UtilityAIAction.generated.h"

class UUtilityAIConsideration;
class UUtilityAIContext;
struct FUtilityAIConsiderationDebugData;

UENUM(BlueprintType)
enum class EUtilityAICombinationMethod : uint8
{
    Multiply UMETA(DisplayName = "Multiply"),
    Average  UMETA(DisplayName = "Average")
};

UCLASS(Blueprintable, Abstract, EditInlineNew, DefaultToInstanced)
class UTILITYAI_API UUtilityAIAction : public UObject
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category = "Utility AI")
    TArray<TObjectPtr<UUtilityAIConsideration>> Considerations;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
    EUtilityAICombinationMethod CombinationMethod = EUtilityAICombinationMethod::Multiply;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Utility AI")
    void Execute();

    virtual void Execute_Implementation();

    UFUNCTION(BlueprintCallable, Category = "Utility AI")
    virtual float CalculateUtility(const UUtilityAIContext* Context) const;

    float CalculateUtilityWithDebug(
        const UUtilityAIContext* Context,
        TArray<FUtilityAIConsiderationDebugData>& OutConsiderations
    ) const;
};