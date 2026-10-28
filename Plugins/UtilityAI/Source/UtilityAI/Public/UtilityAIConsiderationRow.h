#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UtilityAIConsiderationRow.generated.h"

class UTextBlock;
class UProgressBar;

/**
 * Displays a consideration's name, score and progress bar.
 * Used for the Utility AI debug widget.
 */
UCLASS()
class UTILITYAI_API UUtilityAIConsiderationRow : public UUserWidget
{
    GENERATED_BODY()

public:

    /**
     * Updates the displayed consideration data.
     *
     * @param InName Name of the consideration.
     * @param InInputValue Raw input value. (Currently unused)
     * @param InScore Evaluated consideration score.
     */
    UFUNCTION(BlueprintCallable, Category = "Utility AI|Debug")
    void SetConsiderationData(
        FName InName,
        float InInputValue,
        float InScore
    );

protected:

    /** Displays the consideration name. */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> ConsiderationName;

    /** Displays the consideration score as a progress bar. */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UProgressBar> ConsiderationBar;

    /** Displays the score as a formatted number. */
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> ConsiderationScore;
};
