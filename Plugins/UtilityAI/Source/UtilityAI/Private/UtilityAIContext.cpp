#include "UtilityAIContext.h"


float UUtilityAIContext::GetContextValue(FName Name) const
{
    for (const FUtilityAIContextValue& ContextValue : Values)
    {
        if (ContextValue.Name != Name)
        {
            continue;
        }

        if (ContextValue.Type == EUtilityAIValueType::Bool)
        {
            return ContextValue.BoolValue ? 1.0f : 0.0f;
        }

        return ContextValue.FloatValue;
    }

    return 0.0f;
}

void UUtilityAIContext::SetValue(FName Name, float Value)
{
    for (FUtilityAIContextValue& ContextValue : Values)
    {
        if (ContextValue.Name == Name)
        {
            ContextValue.Type = EUtilityAIValueType::Float;
            ContextValue.FloatValue = Value;
            return;
        }
    }

    FUtilityAIContextValue NewValue;
    NewValue.Name = Name;
    NewValue.Type = EUtilityAIValueType::Float;
    NewValue.FloatValue = Value;

    Values.Add(NewValue);
}
