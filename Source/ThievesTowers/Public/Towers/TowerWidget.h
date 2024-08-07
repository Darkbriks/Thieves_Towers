#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerWidget.generated.h"

class ATower;
class APrimitiveTower;
class UTargetingMode;
class UTextBlock;
class UButton;

UCLASS()
class THIEVESTOWERS_API UTowerWidget : public UUserWidget
{
	GENERATED_BODY()
	
	int CurrentTargetingModeIndex = 0;
	TArray<TSubclassOf<UTargetingMode>> TargetingModes;

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TowerName;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentTargetingModeName;

	UPROPERTY(meta = (BindWidget))
	UButton* PreviousTargetingModeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* NextTargetingModeButton;

	UPROPERTY()
	APrimitiveTower* PrimitiveTower;

	UPROPERTY()
	ATower* Tower;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnPreviousTargetingModeButtonClicked();

	UFUNCTION()
	void OnNextTargetingModeButtonClicked();

public:
	APrimitiveTower* GetTower() const { return PrimitiveTower; }
	virtual void SetTower(APrimitiveTower* InTower);
};
