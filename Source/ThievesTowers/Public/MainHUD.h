#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUD.generated.h"

class AMapManager;
class UCardHandWidget;
class USizeBox;
class UTextBlock;
class UButton;

UCLASS()
class THIEVESTOWERS_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY()
	AMapManager* MapManager;

protected:

	////////// Top Bar //////////
	UPROPERTY(meta = (BindWidget))
	UButton* OptionsButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HeroNameField;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RoundField;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LifeField;

	////////// Left Bar //////////
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GoldField;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ManaField;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DrawField;

	////////// Right Bar //////////
	UPROPERTY(meta = (BindWidget))
	UButton* WaveButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DiscardField;

	////////// Other //////////
	UPROPERTY(meta = (BindWidget))
	UButton* PlayButton;

	UPROPERTY(meta = (BindWidget))
	UCardHandWidget* CardHand;

	UPROPERTY(meta = (BindWidget))
	USizeBox* CardSelectionBackground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainHUD - Attributes")
	UWidgetAnimation* CardSelectionBackgroundFadeOut;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MainHUD - Attributes")
	float CardSelectionBackgroundFadeOutSpeed = 0.5f;

	////////// Functions //////////
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void OnDeckValidated();

	UFUNCTION()
	virtual void OnWaveButtonClicked();

	UFUNCTION()
	virtual void OnOptionsButtonClicked();

	UFUNCTION()
	virtual void OnPlayButtonClicked();

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI")
	FText GetRoundText() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI")
	FText GetLifeText() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI")
	FText GetGoldText() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI")
	FText GetManaText() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI")
	FText GetDrawText() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UI")
	FText GetDiscardText() const;
};
