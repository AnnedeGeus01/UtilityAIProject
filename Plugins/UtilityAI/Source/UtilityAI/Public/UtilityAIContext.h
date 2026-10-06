#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UtilityAIContext.generated.h"

UENUM(BlueprintType)
enum class EUtilityAIValueType : uint8
{
    Float,
    Bool
};

USTRUCT(BlueprintType)
struct FUtilityAIContextValue
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
    FName Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
    EUtilityAIValueType Type = EUtilityAIValueType::Float;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
    float FloatValue = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
    bool BoolValue = false;
};

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class UTILITYAI_API UUtilityAIContext : public UObject
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
    TArray<FUtilityAIContextValue> Values;

    UFUNCTION(BlueprintCallable, Category = "Utility AI")
    float GetContextValue(FName Name) const;

    UFUNCTION(BlueprintCallable, Category = "Utility AI")
    void SetValue(FName Name, float Value);
};