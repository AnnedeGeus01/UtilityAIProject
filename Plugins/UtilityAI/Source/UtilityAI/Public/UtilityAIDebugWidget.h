#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UtilityAIDebugWidget.generated.h"

class UUtilityAIComponent;
class UTextBlock;

UCLASS()
class UTILITYAI_API UUtilityAIDebugWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category = "Utility AI|Debug")
    void SetUtilityAIComponent(UUtilityAIComponent* InComponent);

protected:

    virtual void NativeTick(
        const FGeometry& MyGeometry,
        float InDeltaTime
    ) override;

    UPROPERTY(BlueprintReadOnly, Category = "Utility AI|Debug")
    TObjectPtr<UUtilityAIComponent> UtilityAIComponent;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> DebugText;

private:

    void RefreshDebugText();
};