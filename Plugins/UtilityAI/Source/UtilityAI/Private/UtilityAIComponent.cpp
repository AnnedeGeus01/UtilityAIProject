#include "UtilityAIComponent.h"

#include "UtilityAIContext.h"
#include "UtilityAIDecisionManager.h"
#include "UtilityAIAction.h"
#include "UtilityAIDebugWidget.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "UObject/UnrealType.h"

/**
 * Reads a numeric or boolean property from an object.
 *
 * @param Source Object containing the property.
 * @param PropertyName Name of the property to read.
 * @param OutValue Receives the converted value.
 * @return True if the property was read successfully.
 */
static bool ReadUtilityAIProperty(
    UObject* Source,
    FName PropertyName,
    float& OutValue)
{
    if (!Source || PropertyName.IsNone())
    {
        return false;
    }

    FProperty* Property = FindFProperty<FProperty>(
        Source->GetClass(),
        PropertyName
    );

    // Convert boolean properties to 0 or 1.
    if (const FBoolProperty* BoolProperty =
        CastField<FBoolProperty>(Property))
    {
        OutValue = BoolProperty->GetPropertyValue_InContainer(Source)
            ? 1.0f
            : 0.0f;

        return true;
    }

    const FNumericProperty* NumericProperty =
        CastField<FNumericProperty>(Property);

    if (!NumericProperty)
    {
        return false;
    }

    void* ValueAddress =
        NumericProperty->ContainerPtrToValuePtr<void>(Source);

    // Read floating point properties.
    if (NumericProperty->IsFloatingPoint())
    {
        OutValue = static_cast<float>(
            NumericProperty->GetFloatingPointPropertyValue(ValueAddress)
            );

        return true;
    }

    // Read supported integer property types.
    if (NumericProperty->IsInteger())
    {
        if (const FIntProperty* P =
            CastField<FIntProperty>(NumericProperty))
        {
            OutValue = static_cast<float>(
                P->GetPropertyValue_InContainer(Source));
            return true;
        }

        if (const FInt64Property* P =
            CastField<FInt64Property>(NumericProperty))
        {
            OutValue = static_cast<float>(
                P->GetPropertyValue_InContainer(Source));
            return true;
        }

        if (const FByteProperty* P =
            CastField<FByteProperty>(NumericProperty))
        {
            OutValue = static_cast<float>(
                P->GetPropertyValue_InContainer(Source));
            return true;
        }

        if (const FUInt32Property* P =
            CastField<FUInt32Property>(NumericProperty))
        {
            OutValue = static_cast<float>(
                P->GetPropertyValue_InContainer(Source));
            return true;
        }

        if (const FUInt64Property* P =
            CastField<FUInt64Property>(NumericProperty))
        {
            OutValue = static_cast<float>(
                P->GetPropertyValue_InContainer(Source));
            return true;
        }
    }

    return false;
}

/** Creates the component and its default subobjects. */
UUtilityAIComponent::UUtilityAIComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    DecisionInterval = 0.2f;

    Context = CreateDefaultSubobject<UUtilityAIContext>(
        TEXT("UtilityAIContext")
    );

    DecisionManager = CreateDefaultSubobject<UUtilityAIDecisionManager>(
        TEXT("UtilityAIDecisionManager")
    );
}

/**
 * Initializes context values, the decision timer and the debug widget.
 */
void UUtilityAIComponent::BeginPlay()
{
    Super::BeginPlay();

    UpdateContextFromBindings();

    // Schedule repeated decisions when the interval is positive.
    if (DecisionInterval > 0.0f && GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(
            DecisionTimerHandle,
            this,
            &UUtilityAIComponent::MakeDecision,
            DecisionInterval,
            true
        );
    }

    // Create the debug widget for the first player controller.
    if (DebugWidgetClass && GetWorld())
    {
        APlayerController* PlayerController =
            GetWorld()->GetFirstPlayerController();

        if (PlayerController)
        {
            DebugWidget = CreateWidget<UUtilityAIDebugWidget>(
                PlayerController,
                DebugWidgetClass
            );

            if (DebugWidget)
            {
                DebugWidget->SetUtilityAIComponent(this);
                DebugWidget->AddToViewport();
            }
        }
    }
}

/**
 * Returns the interval between AI decisions.
 *
 * @return Decision interval in seconds.
 */
float UUtilityAIComponent::GetDecisionInterval() const
{
    return DecisionInterval;
}

/**
 * Copies bound owner properties into the AI context.
 *
 * Values are optionally normalized and clamped 0 to 1.
 */
void UUtilityAIComponent::UpdateContextFromBindings()
{
    if (!Context)
    {
        return;
    }

    UObject* Source = GetOwner();

    if (!Source)
    {
        return;
    }

    for (const FUtilityAIValueBinding& Binding : ValueBindings)
    {
        if (Binding.PropertyName.IsNone())
        {
            continue;
        }

        float Value = 0.0f;

        if (!ReadUtilityAIProperty(
            Source,
            Binding.PropertyName,
            Value))
        {
            continue;
        }

        // Normalize the value when requested.
        if (Binding.bNormalizeValue)
        {
            if (Binding.InputMax <= Binding.InputMin)
            {
                Value = 0.0f;
            }
            else
            {
                Value = FMath::Clamp(
                    (Value - Binding.InputMin) /
                    (Binding.InputMax - Binding.InputMin),
                    0.0f,
                    1.0f
                );
            }
        }

        Context->SetValue(Binding.PropertyName, Value);
    }
}

/**
 * Updates context values, selects the best action and executes it.
 */
void UUtilityAIComponent::MakeDecision()
{
    if (!Context || !DecisionManager)
    {
        return;
    }

    UpdateContextFromBindings();

    CurrentAction =
        DecisionManager->ChooseBestActionWithDebug(
            Context,
            DebugData
        );

    if (CurrentAction)
    {
        CurrentAction->Execute();
    }
}

/**
 * Returns the currently selected action.
 *
 * @return Current action, or nullptr if none is selected.
 */
UUtilityAIAction* UUtilityAIComponent::GetCurrentAction() const
{
    return CurrentAction;
}
