#pragma once

#include "CoreMinimal.h"
#include "PrimitiveTowerWidget.h"
#include "TowerWidget.generated.h"

class ATower;
class APrimitiveTower;
class UTargetingMode;
class UTextBlock;
class UButton;

UCLASS()
class THIEVESTOWERS_API UTowerWidget : public UPrimitiveTowerWidget
{
	GENERATED_BODY()
	
	int CurrentTargetingModeIndex = 0;
	TArray<TSubclassOf<UTargetingMode>> TargetingModes;

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentTargetingModeName;

	UPROPERTY(meta = (BindWidget))
	UButton* PreviousTargetingModeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* NextTargetingModeButton;

	UPROPERTY()
	ATower* Tower;

	virtual void NativeConstruct() override;
	
	virtual void SetTower(APrimitiveTower* InTower) override;

	UFUNCTION()
	void OnPreviousTargetingModeButtonClicked();

	UFUNCTION()
	void OnNextTargetingModeButtonClicked();
};
