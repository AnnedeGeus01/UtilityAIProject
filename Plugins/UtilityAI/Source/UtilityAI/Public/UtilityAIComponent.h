#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerManager.h"
#include "UtilityAIDebugTypes.h"
#include "UtilityAIComponent.generated.h"

class UUtilityAIContext;
class UUtilityAIDecisionManager;
class UUtilityAIAction;
class UUtilityAIDebugWidget;

/**
 * Defines how an actor property is copied into the AI context.
 */
USTRUCT(BlueprintType)
struct FUtilityAIValueBinding
{
    GENERATED_BODY()

    /** Name of the owner actor property to read. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI|Context")
    FName PropertyName;

    /** Whether the input value is normalized to the range 0 to 1. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI|Context")
    bool bNormalizeValue = true;

    /** Minimum input value used for normalization. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI|Context",
        meta = (EditCondition = "bNormalizeValue"))
    float InputMin = 0.0f;

    /** Maximum input value used for normalization. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI|Context",
        meta = (EditCondition = "bNormalizeValue"))
    float InputMax = 100.0f;
};

/**
 * Updates AI context values and runs utility-based action selection.
 *
 * Attach this component to an actor and configure its context,
 * decision manager, value bindings and optional debug widget.
 */
UCLASS(ClassGroup = (UtilityAI), Blueprintable,
    meta = (BlueprintSpawnableComponent))
    class UTILITYAI_API UUtilityAIComponent : public UActorComponent
{
    GENERATED_BODY()

public:

    /** Creates the component and its default subobjects. */
    UUtilityAIComponent();

protected:

    /** Initializes context updates, decision timing and debugging. */
    virtual void BeginPlay() override;

public:

    /** Stores values used by considerations. */
    UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Utility AI")
    TObjectPtr<UUtilityAIContext> Context;

    /** Selects the action with the highest utility. */
    UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Utility AI")
    TObjectPtr<UUtilityAIDecisionManager> DecisionManager;

    /** Time in seconds between decisions. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
    float DecisionInterval = 0.2f;

    /**
    * Returns the interval between AI decisions.
    *
    * @return Decision interval in seconds.
    */
    UFUNCTION(BlueprintPure, Category = "Utility AI")
    float GetDecisionInterval() const;

    /** Owner properties copied into the AI context. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI|Context")
    TArray<FUtilityAIValueBinding> ValueBindings;

    /**
     * Reads bound owner properties and updates context values.
     *
     * Numeric and boolean properties are supported.
     * Bound values can optionally be normalized from 0 to 1.
     */
    UFUNCTION(BlueprintCallable, Category = "Utility AI|Context")
    void UpdateContextFromBindings();

    /**
     * Updates context values, selects the best action and executes it.
     */
    UFUNCTION(BlueprintCallable, Category = "Utility AI")
    void MakeDecision();

    /**
     * Returns the currently selected action.
     *
     * @return Current action, or nullptr if none is selected.
     */
    UFUNCTION(BlueprintPure, Category = "Utility AI")
    UUtilityAIAction* GetCurrentAction() const;

    /** Widget class used to display AI debugging information. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI|Debug")
    TSubclassOf<UUtilityAIDebugWidget> DebugWidgetClass;

    /** Debug information for the evaluated actions. */
    UPROPERTY(BlueprintReadOnly, Category = "Utility AI|Debug")
    TArray<FUtilityAIActionDebugData> DebugData;

    /** Active debug widget instance. */
    UPROPERTY()
    TObjectPtr<UUtilityAIDebugWidget> DebugWidget;

private:

    /** Timer used to schedule decisions. */
    FTimerHandle DecisionTimerHandle;

    /** Action selected during the most recent decision. */
    UPROPERTY()
    TObjectPtr<UUtilityAIAction> CurrentAction;
};
