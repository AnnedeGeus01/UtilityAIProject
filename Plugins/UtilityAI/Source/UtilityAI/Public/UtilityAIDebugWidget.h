#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UtilityAIDebugWidget.generated.h"

class UUtilityAIComponent;
class UTextBlock;
class UVerticalBox;
class UUtilityAIActionRow;

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

    // DEBUG WIDGET REFERENCES

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> CurrentActionText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> SelectedActionText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> CombinationMethodText;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UVerticalBox> ActionList;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UVerticalBox> ConsiderationList;

    UPROPERTY()
    TObjectPtr<UTextBlock> ConsiderationTextBlock;

    // ACTION ROW

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI|Debug")
    TSubclassOf<UUtilityAIActionRow> ActionRowClass;

    // CACHED ACTION ROWS

    UPROPERTY()
    TArray<TObjectPtr<UUtilityAIActionRow>> ActionRows;

private:

    void RefreshDebugWidget();

    float RefreshTimer = 0.0f;
};
