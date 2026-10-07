#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UtilityAIActionRow.generated.h"

class UTextBlock;
class UProgressBar;

UCLASS()
class UTILITYAI_API UUtilityAIActionRow : public UUserWidget
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category = "Utility AI|Debug")
    void SetActionData(
        const FString& InActionName,
        float InUtility,
        bool bInSelected
    );

protected:

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> ActionMarker;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> ActionName;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UProgressBar> UtilityBar;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> UtilityValue;
};
