#pragma once

#include "CoreMinimal.h"
#include "UtilityAIDebugTypes.h"
#include "Components/ActorComponent.h"
#include "UtilityAIComponent.generated.h"

class UUtilityAIContext;
class UUtilityAIDecisionManager;
class UUtilityAIAction;
class UUtilityAIDebugWidget;

UCLASS(ClassGroup = (UtilityAI), Blueprintable, meta = (BlueprintSpawnableComponent))
class UTILITYAI_API UUtilityAIComponent : public UActorComponent
{
    GENERATED_BODY()

public:

    UUtilityAIComponent();

protected:

    virtual void BeginPlay() override;

public:

    UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Utility AI")
    TObjectPtr<UUtilityAIContext> Context;

    UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Utility AI")
    TObjectPtr<UUtilityAIDecisionManager> DecisionManager;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
    float DecisionInterval = 0.2f;

    UFUNCTION(BlueprintCallable, Category = "Utility AI")
    void MakeDecision();

    UFUNCTION(BlueprintPure, Category = "Utility AI")
    UUtilityAIAction* GetCurrentAction() const;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI|Debug")
    TSubclassOf<UUtilityAIDebugWidget> DebugWidgetClass;

    UPROPERTY(BlueprintReadOnly, Category = "Utility AI|Debug")
    TArray<FUtilityAIActionDebugData> DebugData;

    UPROPERTY()
    TObjectPtr<UUtilityAIDebugWidget> DebugWidget;

private:

    FTimerHandle DecisionTimerHandle;

    UPROPERTY()
    TObjectPtr<UUtilityAIAction> CurrentAction;
};