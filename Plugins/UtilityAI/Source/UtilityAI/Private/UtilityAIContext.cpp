#include "UtilityAIContext.h"

/**
 * Retrieves a named value from the context.
 *
 * @param Name Name of the value to retrieve.
 * @return Stored value, or 0.0 if the name is not found.
 */
float UUtilityAIContext::GetContextValue(FName Name) const
{
    for (const FUtilityAIContextValue& ContextValue : Values)
    {
        if (ContextValue.Name != Name)
        {
            continue;
        }

        // Convert boolean values to numeric scores.
        if (ContextValue.Type == EUtilityAIValueType::Bool)
        {
            return ContextValue.BoolValue ? 1.0f : 0.0f;
        }

        return ContextValue.FloatValue;
    }

    return 0.0f;
}

/**
 * Adds a numeric value or updates an existing entry.
 *
 * Existing entries are changed to Float type.
 *
 * @param Name Name of the value to set.
 * @param Value Numeric value to store.
 */
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

    // Create an entry when the name does not exist.
    FUtilityAIContextValue NewValue;
    NewValue.Name = Name;
    NewValue.Type = EUtilityAIValueType::Float;
    NewValue.FloatValue = Value;

    Values.Add(NewValue);
}
