#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UtilityAIContext.generated.h"

/**
 * Defines the data type stored in a context value.
 */
UENUM(BlueprintType)
enum class EUtilityAIValueType : uint8
{
    /** Stores a numeric value. */
    Float,

    /** Stores a boolean value. */
    Bool
};

/**
 * Stores a named value used by the utility AI system.
 */
USTRUCT(BlueprintType)
struct FUtilityAIContextValue
{
    GENERATED_BODY()

public:

    /** Name used to identify the context value. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
    FName Name;

    /** Type of value stored. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
    EUtilityAIValueType Type = EUtilityAIValueType::Float;

    /** Numeric value when the type is Float. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
    float FloatValue = 0.0f;

    /** Boolean value when the type is Bool. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
    bool BoolValue = false;
};

/**
 * Stores named values used to evaluate utility AI actions.
 *
 * Values can be read by considerations and updated at runtime.
 */
UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class UTILITYAI_API UUtilityAIContext : public UObject
{
    GENERATED_BODY()

public:

    /** Runtime collection of named context values. 
    * Intentionally not exposed to the editor or Blueprint,array just
    * stores values at runtime for GetContextValue() and SetValue().
    */
    TArray<FUtilityAIContextValue> Values;

    /**
     * Retrieves a context value as a float.
     *
     * Boolean values are converted to 1.0 or 0.0.
     *
     * @param Name Name of the value to retrieve.
     * @return Stored value, or 0.0 if the name is not found.
     */
    UFUNCTION(BlueprintCallable, Category = "Utility AI")
    float GetContextValue(FName Name) const;

    /**
     * Adds or updates a numeric context value.
     *
     * @param Name Name of the value to set.
     * @param Value Numeric value to store.
     */
    UFUNCTION(BlueprintCallable, Category = "Utility AI")
    void SetValue(FName Name, float Value);
};
