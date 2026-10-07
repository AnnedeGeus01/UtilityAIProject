#include "UtilityAIComponent.h"
#include "UtilityAIContext.h"
#include "UtilityAIDecisionManager.h"
#include "UtilityAIAction.h"
#include "UtilityAIDebugWidget.h"

#include "Engine/World.h"
#include "Engine/Engine.h" // for on screen debug messages, testing purposes
#include "TimerManager.h"

UUtilityAIComponent::UUtilityAIComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    DecisionInterval = 0.2f;

    Context = CreateDefaultSubobject<UUtilityAIContext>(TEXT("UtilityAIContext"));
    DecisionManager = CreateDefaultSubobject<UUtilityAIDecisionManager>(TEXT("UtilityAIDecisionManager"));
}

void UUtilityAIComponent::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(
        LogTemp,
        Warning,
        TEXT("UtilityAIComponent BeginPlay: %s | Component=%p"),
        *GetOwner()->GetName(),
        this
    );

    if (DecisionManager)
    {
        for (int32 i = 0; i < DecisionManager->Actions.Num(); ++i)
        {
            UUtilityAIAction* Action = DecisionManager->Actions[i];
        }
    }

    if (DecisionInterval > 0.0f)
    {
        GetWorld()->GetTimerManager().SetTimer(
            DecisionTimerHandle,
            this,
            &UUtilityAIComponent::MakeDecision,
            DecisionInterval,
            true
        );
    }

    if (DebugWidgetClass && !DebugWidget)
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT("Creating Debug Widget: %s | Component=%p"),
            *GetOwner()->GetName(),
            this
        );

        DebugWidget = CreateWidget<UUtilityAIDebugWidget>(
            GetWorld(),
            DebugWidgetClass
        );

        if (DebugWidget)
        {
            DebugWidget->SetUtilityAIComponent(this);
            DebugWidget->AddToViewport();
        }
    }
}

void UUtilityAIComponent::MakeDecision()
{
    if (!Context || !DecisionManager)
    {
        return;
    }

    // CurrentAction = DecisionManager->ChooseBestAction(Context);
    CurrentAction =
        DecisionManager->ChooseBestActionWithDebug(
            Context,
            DebugData
        );

    /*GEngine->AddOnScreenDebugMessage(
        -1,
        2.0f,
        FColor::Green,
        TEXT("MakeDecision is running")
    );*/

    if (CurrentAction)
    {
        CurrentAction->Execute();

        /*GEngine->AddOnScreenDebugMessage(
            -1,
            2.0f,
            FColor::Red,
            TEXT("Executing action")
        );*/
    }
}

UUtilityAIAction* UUtilityAIComponent::GetCurrentAction() const
{
    return CurrentAction;
}